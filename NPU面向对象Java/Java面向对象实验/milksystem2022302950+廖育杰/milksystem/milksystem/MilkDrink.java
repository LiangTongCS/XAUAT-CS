package milksystem;
import java.util.ArrayList;
import java.util.Date;
// MilkDrink 类，继承自 Product
public class MilkDrink extends Product {
    private String flavor; // 口味
    private String sugar; // 糖分

    public MilkDrink(String code, String description, double price, Date productionDate, String shelfLife,
                     String flavor, String sugar) {
        super(code, description, price, productionDate, shelfLife);
        this.flavor = flavor;
        this.sugar = sugar;
    }

    // 获取口味
    public String getFlavor() {
        return flavor;
    }

    // 获取糖分
    public String getSugar() {
        return sugar;
    }
}

