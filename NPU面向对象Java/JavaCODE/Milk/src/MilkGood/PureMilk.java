package MilkGood;
import java.util.ArrayList;
import java.util.Date;
// 纯牛奶类，继承自产品类
public class PureMilk extends Product {
    private String countryOfOrigin;
    private String butterfat;
    private String protein;

    public PureMilk(String code, String description, double price, Date productionDate, String shelfLife,
                    String countryOfOrigin, String butterfat, String protein) {
        super(code, description, price, productionDate, shelfLife);
        this.countryOfOrigin = countryOfOrigin;
        this.butterfat = butterfat;
        this.protein = protein;
    }

    public String getCountryOfOrigin() {
        return countryOfOrigin;
    }

    public String getButterfat() {
        return butterfat;
    }

    public String getProtein() {
        return protein;
    }
}
