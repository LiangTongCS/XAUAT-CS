package milksystem;
import java.util.ArrayList;
import java.util.Date;

// PureMilk 类，继承自 Product
public class PureMilk extends Product {
    private String countryOfOrigin; // 原产国
    private String butterfat; // 脂肪含量
    private String protein; // 蛋白质含量

    public PureMilk(String code, String description, double price, Date productionDate, String shelfLife,
                    String countryOfOrigin, String butterfat, String protein) {
        super(code, description, price, productionDate, shelfLife);
        this.countryOfOrigin = countryOfOrigin;
        this.butterfat = butterfat;
        this.protein = protein;
    }

    // 获取原产国
    public String getCountryOfOrigin() {
        return countryOfOrigin;
    }

    // 获取脂肪含量
    public String getButterfat() {
        return butterfat;
    }

    // 获取蛋白质含量
    public String getProtein() {
        return protein;
    }
}

