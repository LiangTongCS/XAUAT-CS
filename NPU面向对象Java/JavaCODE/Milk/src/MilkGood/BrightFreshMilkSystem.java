package MilkGood;
import java.util.ArrayList;

public class BrightFreshMilkSystem {
    private ProductCatalog productCatalog;
    private StoreSales storeSales;
    private Order currentOrder;

    public BrightFreshMilkSystem() {
        productCatalog = new ProductCatalog();
        storeSales = new StoreSales();
        currentOrder = new Order();
    }

    // 显示产品目录
    public void displayCatalog() {
        ArrayList<Product> products = productCatalog.getProducts();
        for (Product product : products) {
            System.out.println("Code: " + product.getCode());
            System.out.println("Description: " + product.getDescription());
            System.out.println("Production Date: " + product.getProductionDate());
            System.out.println("-----------------------------------");
        }
    }

    // 根据产品编码显示产品信息
    public void displayProduct(String code) {
        Product product = productCatalog.getProduct(code);
        if (product != null) {
            System.out.println("Code: " + product.getCode());
            System.out.println("Description: " + product.getDescription());
            System.out.println("Price: " + product.getPrice());
            // 显示其他属性
        } else {
            System.out.println("Product not found.");
        }
    }

    // 显示当前订单
    public void displayOrder() {
        System.out.println("Quantity\tCode\tDescription\tPrice");
        ArrayList<SaleItem> items = currentOrder.getItems();
        for (SaleItem item : items) {
            System.out.println(item.getQuantity() + "\t" + item.getProduct().getCode() + "\t" + item.getProduct().getDescription() + "\t" + item.getProduct().getPrice());
        }
        System.out.println("Order Total: " + currentOrder.getTotalCost());
    }

    // 添加产品到当前订单
    public void addProduct(Product product, int quantity) {
        currentOrder.addSaleItem(new SaleItem(product, quantity));
    }

    // 从当前订单中移除产品
    public void removeProduct(Product product) {
        currentOrder.removeSaleItem(product);
    }

    // 将当前订单添加到销售列表并清空当前订单
    public void addOrder() {
        storeSales.addOrder(currentOrder);
        currentOrder = new Order();
    }

    // 显示销售列表
    public void displaySales() {
        ArrayList<Order> orders = storeSales.getOrders();
        for (Order order : orders) {
            displayOrder(order);
            System.out.println("-----------------------------------");
        }
    }

    // 显示单个订单
    public void displayOrder(Order order) {
        System.out.println("Order ID: " + order.getOrderID());
        System.out.println("Order Date: " + order.getOrderDate());
        System.out.println("Quantity\tCode\tDescription\tPrice");
        ArrayList<SaleItem> items = order.getItems();
        for (SaleItem item : items) {
            System.out.println(item.getQuantity() + "\t" + item.getProduct().getCode() + "\t" + item.getProduct().getDescription() + "\t" + item.getProduct().getPrice());
        }
        System.out.println("Order Total: " + order.getTotalCost());
    }
}
