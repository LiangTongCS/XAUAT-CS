package milksystem;
import java.util.ArrayList;
import java.util.Date;

// 主类 BrightFreshMilkSystem
public class BrightFreshMilkSystem {
    private ProductCatalog productCatalog; // 产品目录
    private Order currentOrder; // 当前订单
    private StoreSales storeSales; // 商店销售记录

    public BrightFreshMilkSystem() {
        this.productCatalog = new ProductCatalog();
        this.currentOrder = new Order();
        this.storeSales = new StoreSales();
    }

    // 显示产品目录
    public void displayCatalog() {
        productCatalog.displayProducts();
    }

    // 根据产品代码显示产品信息
    public void displayProduct(String code) {
        Product product = productCatalog.getProduct(code);
        if (product != null) {
            System.out.println("产品代码：" + product.getCode());
            System.out.println("产品描述：" + product.getDescription());
            System.out.println("生产日期：" + product.getProductionDate());
        } else {
            System.out.println("找不到该产品！");
        }
    }

    // 显示当前订单
    public void displayOrder() {
        currentOrder.displaySaleItems();
        System.out.println("订单总额：" + currentOrder.getTotalCost());
    }

    // 添加产品到当前订单
    public void addProduct(String code, int quantity) {
        Product product = productCatalog.getProduct(code);
        if (product != null) {
            currentOrder.addSaleItem(new SaleItem(product, quantity));
        } else {
            System.out.println("找不到该产品！");
        }
    }

    // 从当前订单中移除产品
    public void removeProduct(String code) {
        Product product = productCatalog.getProduct(code);
        if (product != null) {
            currentOrder.removeSaleItem(product);
        } else {
            System.out.println("找不到该产品！");
        }
    }

    // 将当前订单添加到商店销售记录，并清空当前订单
    public void addOrder() {
        storeSales.addOrder(currentOrder);
        currentOrder = new Order();
    }

    // 显示商店的销售记录
    public void displaySales() {
        storeSales.displayOrders();
    }
}

