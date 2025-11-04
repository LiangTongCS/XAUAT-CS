/**
 * @LiangTong 2023370018
 * @JDK1.8
 */
package MilkSys;
import java.util.*;
import java.text.*;
// Yogurt 类
public class Yogurt extends Product {
    private String type;
    private String diluteConcentration;

    public Yogurt(String code, String description, double price, Date productionDate, String shelfLife, String type, String diluteConcentration) {
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
