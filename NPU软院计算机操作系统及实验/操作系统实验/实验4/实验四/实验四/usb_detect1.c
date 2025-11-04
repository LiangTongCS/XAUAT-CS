/*
 * USB Detect driver
 *
 * This driver is based on the 2.6.3 version of drivers/usb/usb-skeleton.c
 */

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
#include <linux/uaccess.h>
#include <linux/usb.h>
#include <linux/mutex.h>


/* Define these values to match your devices */
#define USB_DETECT_VENDOR_ID	0x058f
#define USB_DETECT_PRODUCT_ID	0x6387

/* table of devices that work with this driver */
static const struct usb_device_id usbdetect_table[] = {
	{ USB_DEVICE(USB_DETECT_VENDOR_ID, USB_DETECT_PRODUCT_ID) },
	{ }					/* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, usbdetect_table);


/* Get a minor range for your devices from the usb maintainer */
#define USB_DETECT_MINOR_BASE	192

#define WRITES_IN_FLIGHT	8
/* arbitrarily chosen */

/* Structure to hold all of our device specific stuff */
struct usb_detect {
	struct usb_device	*udev;			/* the usb device for this device */
	struct usb_interface	*interface;		/* the interface for this device */
	struct semaphore	limit_sem;		/* limiting the number of writes in progress */
	struct usb_anchor	submitted;		/* in case we need to retract our submissions */
	struct urb		*bulk_in_urb;		/* the urb to read data with */
	unsigned char           *bulk_in_buffer;	/* the buffer to receive data */
	size_t			bulk_in_size;		/* the size of the receive buffer */
	size_t			bulk_in_filled;		/* number of bytes in the buffer */
	size_t			bulk_in_copied;		/* already copied to user space */
	__u8			bulk_in_endpointAddr;	/* the address of the bulk in endpoint */
	__u8			bulk_out_endpointAddr;	/* the address of the bulk out endpoint */
	int			errors;			/* the last request tanked */
	bool			ongoing_read;		/* a read is going on */
	spinlock_t		err_lock;		/* lock for errors */
	struct kref		kref;
	struct mutex		io_mutex;		/* synchronize I/O with disconnect */
	unsigned long		disconnected:1;
	wait_queue_head_t	bulk_in_wait;		/* to wait for an ongoing read */
};
#define to_detect_dev(d) container_of(d, struct usb_detect, kref)

static struct usb_driver usbdetect_driver;

static void usbdetect_delete(struct kref *kref)
{
	struct usb_detect *dev = to_detect_dev(kref);

	usb_free_urb(dev->bulk_in_urb);
	usb_put_intf(dev->interface);
	usb_put_dev(dev->udev);
	kfree(dev->bulk_in_buffer);
	kfree(dev);
}

static const struct file_operations usbdetect_fops = {};

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device registered with the driver core
 */
static struct usb_class_driver usbdetect_class = {
	.name =		"usbdetect%d",
	.fops =		&usbdetect_fops,
	.minor_base =	USB_DETECT_MINOR_BASE,
};

static int usbdetect_probe(struct usb_interface *interface,
		      const struct usb_device_id *id)
{
	struct usb_detect *dev;
	struct usb_endpoint_descriptor *bulk_in, *bulk_out;
	int retval;

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	kref_init(&dev->kref);
	sema_init(&dev->limit_sem, WRITES_IN_FLIGHT);
	mutex_init(&dev->io_mutex);
	spin_lock_init(&dev->err_lock);
	init_usb_anchor(&dev->submitted);
	init_waitqueue_head(&dev->bulk_in_wait);

	dev->udev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = usb_get_intf(interface);

	/* set up the endpoint information */
	/* use only the first bulk-in and bulk-out endpoints */
	retval = usb_find_common_endpoints(interface->cur_altsetting,
			&bulk_in, &bulk_out, NULL, NULL);
	if (retval) {
		dev_err(&interface->dev,
			"Could not find both bulk-in and bulk-out endpoints\n");
		goto error;
	}

	dev->bulk_in_size = usb_endpoint_maxp(bulk_in);
	dev->bulk_in_endpointAddr = bulk_in->bEndpointAddress;
	dev->bulk_in_buffer = kmalloc(dev->bulk_in_size, GFP_KERNEL);
	if (!dev->bulk_in_buffer) {
		retval = -ENOMEM;
		goto error;
	}
	dev->bulk_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->bulk_in_urb) {
		retval = -ENOMEM;
		goto error;
	}

	dev->bulk_out_endpointAddr = bulk_out->bEndpointAddress;

	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);

	/* we can register the device now, as it is ready */
	retval = usb_register_dev(interface, &usbdetect_class);
	if (retval) {
		/* something prevented us from registering this driver */
		dev_err(&interface->dev,
			"Not able to get a minor for this device.\n");
		usb_set_intfdata(interface, NULL);
		goto error;
	}

	/* let the user know what node this device is now attached to */
	dev_info(&interface->dev,
		 "USB detect device now attached to USBdetect-%d\n",
		 interface->minor);

	/* Print Vendor ID, Product ID, Manufacturer, and Product */
	dev_info(&interface->dev,
		 "Vendor ID: 0x%04X, Product ID: 0x%04X\n",
		 le16_to_cpu(dev->udev->descriptor.idVendor),
		 le16_to_cpu(dev->udev->descriptor.idProduct));
	dev_info(&interface->dev,
		 "Manufacturer: %s, Product: %s\n",
		 dev->udev->manufacturer, dev->udev->product);

	return 0;

error:
	/* this frees allocated memory */
	kref_put(&dev->kref, usbdetect_delete);

	return retval;
}

static void usbdetect_disconnect(struct usb_interface *interface)
{
	struct usb_detect *dev;

	dev = usb_get_intfdata(interface);

	dev_info(&interface->dev,
		 "USB detect device removed from USBdetect-%d\n",
		 interface->minor);

	dev_info(&interface->dev,
		 "Vendor ID: 0x%04X, Product ID: 0x%04X\n",
		 le16_to_cpu(dev->udev->descriptor.idVendor),
		 le16_to_cpu(dev->udev->descriptor.idProduct));

	/* Clean up */
	usb_set_intfdata(interface, NULL);
	usb_deregister_dev(interface, &usbdetect_class);

	mutex_lock(&dev->io_mutex);
	dev->disconnected = 1;
	mutex_unlock(&dev->io_mutex);

	usb_kill_anchored_urbs(&dev->submitted);
	kref_put(&dev->kref, usbdetect_delete);
}


static struct usb_driver usbdetect_driver = {
	.name =		"usbdetect",    //        
	.probe =	usbdetect_probe,
	.disconnect =	usbdetect_disconnect,
	.id_table =	usbdetect_table,
	.supports_autosuspend = 1,
};

MODULE_LICENSE("GPL v2");

static int __init usb_detect_init(void)
{
	int result;
	printk("Start usb_detect module...\n");
	/* register this driver with the USB subsystem */
	result = usb_register(&usbdetect_driver);
	if (result < 0) {
		printk("usb_register failed. Error number %d\n", result);
		return -1;
	}
	return 0;
}

static void __exit usb_detect_exit(void)
{
	printk("Exit usb_detect module...\n");
	/* deregister this driver with the USB subsystem */
	usb_deregister(&usbdetect_driver);
}

module_init(usb_detect_init);
module_exit(usb_detect_exit);
