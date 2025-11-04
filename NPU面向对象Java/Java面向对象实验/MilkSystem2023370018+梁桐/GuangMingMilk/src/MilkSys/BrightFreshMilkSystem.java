/**
 * @LiangTong 2023370018
 * @JDK1.8
 */
package MilkSys;
import java.util.*;
import java.text.*;

// BrightFreshMilkSystem 类
public class BrightFreshMilkSystem {
    public ProductCatalog catalog = new ProductCatalog();
    private Order currentOrder = new Order();
    private StoreSales storeSales = new StoreSales();

    public void displayCatalog() {
        for (Product product : catalog.getProducts()) {
            System.out.println("Code: " + product.getCode() + ", Description: " + product.getDescription() + ", Production Date: " + product.getProductionDate());
        }
    }

    public void displayProduct(String code) {
        Product product = catalog.getProduct(code);
        if (product != null) {
            System.out.println("Code: " + product.getCode() + ", Description: " + product.getDescription() + ", Production Date: " + product.getProductionDate());
        } else {
            System.out.println("Product not found.");
        }
    }

    public void displayOrder() {
        for (SaleItem item : currentOrder.getItems()) {
            System.out.println("Quantity: " + item.getQuantity() + ", Code: " + item.getProduct().getCode() + ", Price: " + item.getProduct().getPrice());
        }
        System.out.println("Order total: " + currentOrder.getTotalCost());
    }

    public void addProduct(String code, int quantity) {
        Product product = catalog.getProduct(code);
        if (product != null) {
            SaleItem item = currentOrder.getSaleItem(product);
            if (item != null) {
                item.setQuantity(item.getQuantity() + quantity);
            } else {
                currentOrder.addSaleItem(new SaleItem(product, quantity));
            }
        } else {
            System.out.println("Product not found.");
        }
    }

    public void removeProduct(String code) {
        Product product = catalog.getProduct(code);
        if (product != null) {
            SaleItem item = currentOrder.getSaleItem(product);
            if (item != null) {
                currentOrder.removeSaleItem(item);
            }
        } else {
            System.out.println("Product not found.");
        }
    }

    public void addOrder() {
        storeSales.addOrder(currentOrder);
        currentOrder = new Order();
    }

    public void displaySales() {
        for (Order order : storeSales.getOrders()) {
            System.out.println("Order Total: " + order.getTotalCost());
        }
    }
}
