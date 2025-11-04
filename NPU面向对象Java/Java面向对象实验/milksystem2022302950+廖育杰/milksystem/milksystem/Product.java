package milksystem;
import java.util.ArrayList;
import java.util.Date;


// 产品类 Product
public class Product {
    private String code; // 产品代码
    private String description; // 产品描述
    private double price; // 产品价格
    private Date productionDate; // 生产日期
    private String shelfLife; // 保质期

    public Product(String code, String description, double price, Date productionDate, String shelfLife) {
        this.code = code;
        this.description = description;
        this.price = price;
        this.productionDate = productionDate;
        this.shelfLife = shelfLife;
    }

    // 获取产品代码
    public String getCode() {
        return code;
    }

    // 获取产品描述
    public String getDescription() {
        return description;
    }

    // 获取产品价格
    public double getPrice() {
        return price;
    }

    // 获取生产日期
    public Date getProductionDate() {
        return productionDate;
    }

    // 获取保质期
    public String getShelfLife() {
        return shelfLife;
    }
}
