/**
 * @LiangTong 2023370018
 * @JDK1.8
 */
package MilkSys;
import java.util.*;
import java.text.*;
// MilkDrink 类
public class MilkDrink extends Product {
    private String flavor;
    private String sugar;

    public MilkDrink(String code, String description, double price, Date productionDate, String shelfLife, String flavor, String sugar) {
        super(code, description, price, productionDate, shelfLife);
        this.flavor = flavor;
        this.sugar = sugar;
    }

    public String getFlavor() {
        return flavor;
    }

    public String getSugar() {
        return sugar;
    }
}