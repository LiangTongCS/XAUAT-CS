package MilkGood;
import java.util.ArrayList;
import java.util.Date;

// 果冻类，继承自产品类
public class Jelly extends Product {
    private String flavor;

    public Jelly(String code, String description, double price, Date productionDate, String shelfLife, String flavor) {
        super(code, description, price, productionDate, shelfLife);
        this.flavor = flavor;
    }

    public String getFlavor() {
        return flavor;
    }
}

