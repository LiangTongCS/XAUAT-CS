package milksystem;
import java.util.ArrayList;
import java.util.Date;

// 产品目录类 ProductCatalog
public class ProductCatalog {
    private ArrayList<Product> products; // 产品列表

    public ProductCatalog() {
        this.products = new ArrayList<>();
    }

    // 添加产品到目录
    public void addProduct(Product product) {
        products.add(product);
    }

    // 从目录中移除产品
    public void removeProduct(Product product) {
        products.remove(product);
    }

    // 根据产品代码获取产品
    public Product getProduct(String code) {
        for (Product product : products) {
            if (product.getCode().equals(code)) {
                return product;
            }
        }
        return null;
    }

    // 根据索引获取产品
    public Product getProduct(int index) {
        if (index >= 0 && index < products.size()) {
            return products.get(index);
        }
        return null;
    }

    // 获取产品数量
    public int getNumberOfProducts() {
        return products.size();
    }

    // 显示所有产品
    public void displayProducts() {
        for (Product product : products) {
            System.out.println("产品代码：" + product.getCode());
            System.out.println("产品描述：" + product.getDescription());
            System.out.println("生产日期：" + product.getProductionDate());
        }
    }
}
