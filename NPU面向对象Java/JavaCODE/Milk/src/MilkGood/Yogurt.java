package MilkGood;
import java.util.ArrayList;
import java.util.Date;

// 酸奶类，继承自产品类
public class Yogurt extends Product {
    private String type;
    private String diluteConcentration;

    public Yogurt(String code, String description, double price, Date productionDate, String shelfLife,
                  String type, String diluteConcentration) {
        super(code, description, price, productionDate, shelfLife);
        this.type = type;
        this.diluteConcentration = diluteConcentration;
    }

    public String getType() {
        return type;
    }

    public String getDiluteConcentration() {
        return diluteConcentration;
    }
}

