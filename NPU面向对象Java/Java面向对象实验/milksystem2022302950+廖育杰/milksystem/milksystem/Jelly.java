package milksystem;
import java.util.ArrayList;
import java.util.Date;

// Jelly 类，继承自 Product
public class Jelly extends Product {
    private String flavor; // 口味

    public Jelly(String code, String description, double price, Date productionDate, String shelfLife, String flavor) {
        super(code, description, price, productionDate, shelfLife);
        this.flavor = flavor;
    }

    // 获取口味
    public String getFlavor() {
        return flavor;
    }
}

