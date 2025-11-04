/**
 * @LiangTong 2023370018
 * @JDK1.8
 */
package MilkSys;
import java.util.*;
import java.text.*;
public class Main {
    public static void main(String[] args) {
        // 初始化 BrightFreshMilkSystem 和示例数据
        BrightFreshMilkSystem system = new BrightFreshMilkSystem();
        Product milk = new PureMilk("A002", "skim milk, 800ml", 18.0, new Date(), "6 months", "USA", "Low fat", "High protein");
        Product milkDrink = new MilkDrink("C001", "chocolate flavor, 270ml", 5.0, new Date(), "4 months", "Chocolate", "Medium sugar");
        Product yogurt = new Yogurt("D001", "taro flavor, 250ml", 13.1, new Date(), "3 months", "Taro", "Diluted");
        Product jelly = new Jelly("B001", "solid, 250ml", 8.5, new Date(), "5 months", "Fruit");

        system.catalog.addProduct(milk);
        system.catalog.addProduct(milkDrink);
        system.catalog.addProduct(yogurt);
        system.catalog.addProduct(jelly);

        // 进行一些操作，例如添加产品到订单
        system.addProduct("A002", 2);
        system.addProduct("C001", 3);
        system.addProduct("D001", 1);
        system.addProduct("B001", 3);

        // 显示当前订单和目录
        system.displayOrder();
        system.displayCatalog();

        // 提交订单并显示销售情况
        system.addOrder();
        system.displaySales();
    }
}
