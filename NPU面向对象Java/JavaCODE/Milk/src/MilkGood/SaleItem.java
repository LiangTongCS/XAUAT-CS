package MilkGood;

// 销售项类，表示订单中的每个产品及其数量
public class SaleItem {
    private int quantity;
    private Product product;

    public SaleItem(Product product, int quantity) {
        this.product = product;
        this.quantity = quantity;
    }

    public Product getProduct() {
        return product;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    public double getValue() {
        return product.getPrice() * quantity;
    }
}

