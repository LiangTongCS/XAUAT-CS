/**
 * @LiangTong 2023370018
 * @JDK1.8
 */
package MilkSys;
import java.util.*;
import java.text.*;
// Jelly 类
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
