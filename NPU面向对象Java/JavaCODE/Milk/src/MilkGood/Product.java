package MilkGood;
import java.util.ArrayList;
import java.util.Date;
// 产品类，作为所有产品的父类
public class Product {
    private String code;
    private String description;
    private double price;
    private Date productionDate;
    private String shelfLife;

    public Product(String code, String description, double price, Date productionDate, String shelfLife) {
        this.code = code;
        this.description = description;
        this.price = price;
        this.productionDate = productionDate;
        this.shelfLife = shelfLife;
    }

    public String getCode() {
        return code;
    }

    public String getDescription() {
        return description;
    }

    public double getPrice() {
        return price;
    }

    public Date getProductionDate() {
        return productionDate;
    }

    public String getShelfLife() {
        return shelfLife;
    }
}



