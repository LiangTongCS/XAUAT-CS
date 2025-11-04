package MilkGood;
import java.util.ArrayList;
import java.util.Date;

// 产品目录类，包含多个产品
public class ProductCatalog {
    private ArrayList<Product> products;

    public ProductCatalog() {
        products = new ArrayList<>();
    }

    public void addProduct(Product product) {
        products.add(product);
    }

    public void removeProduct(Product product) {
        products.remove(product);
    }

    public Product getProduct(String code) {
        for (Product product : products) {
            if (product.getCode().equals(code)) {
                return product;
            }
        }
        return null; // 如果找不到产品
    }

    public int getNumberOfProducts() {
        return products.size();
    }
}
