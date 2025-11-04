package milksystem;
import java.util.ArrayList;
import java.util.Date;

// 销售项类 SaleItem
public class SaleItem {
    private Product product; // 产品
    private int quantity; // 数量

    public SaleItem(Product product, int quantity) {
        this.product = product;
        this.quantity = quantity;
    }

    // 获取产品
    public Product getProduct() {
        return product;
    }

    // 获取数量
    public int getQuantity() {
        return quantity;
    }

    // 设置数量
    public void setQuantity(int newQuantity) {
        this.quantity = newQuantity;
    }

    // 获取销售项总价值
    public double getValue() {
        return product.getPrice() * quantity;
    }
}
