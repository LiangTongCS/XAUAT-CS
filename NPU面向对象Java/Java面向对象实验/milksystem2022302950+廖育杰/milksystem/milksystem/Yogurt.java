package milksystem;
import java.util.ArrayList;
import java.util.Date;

// Yogurt 类，继承自 Product
public class Yogurt extends Product {
    private String type; // 类型
    private String diluteConcentration; // 稀释浓度

    public Yogurt(String code, String description, double price, Date productionDate, String shelfLife,
                  String type, String diluteConcentration) {
        super(code, description, price, productionDate, shelfLife);
        this.type = type;
        this.diluteConcentration = diluteConcentration;
    }

    // 获取类型
    public String getType() {
        return type;
    }

    // 获取稀释浓度
    public String getDiluteConcentration() {
        return diluteConcentration;
    }
}

