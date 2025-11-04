package Test;
import java.util.ArrayList;
import java.util.Date;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;
import MilkGood.package.*;
public class BrightFreshMilkSystemTest {
    private BrightFreshMilkSystem milkSystem;

    @Before
    public void setUp() {
        milkSystem = new BrightFreshMilkSystem();
        // 在这里可以初始化一些示例产品和订单
    }

    @Test
    public void testAddProductToOrder() {
        Product product = new PureMilk("A001", "Full Cream Milk", 5.0, new Date(), "30 days",
                "USA", "3.5%", "3.0%");
        milkSystem.addProduct(product, 2);
        assertEquals(2, milkSystem.getCurrentOrder().getNumberOfItems());
    }

    @Test
    public void testRemoveProductFromOrder() {
        Product product1 = new PureMilk("A001", "Full Cream Milk", 5.0, new Date(), "30 days",
                "USA", "3.5%", "3.0%");
        Product product2 = new MilkDrink("B001", "Chocolate Milkshake", 3.0, new Date(), "15 days", "Chocolate", "Medium Sugar");

        milkSystem.addProduct(product1, 2);
        milkSystem.addProduct(product2, 1);
        assertEquals(3, milkSystem.getCurrentOrder().getNumberOfItems());

        milkSystem.removeProduct(product1);
        assertEquals(1, milkSystem.getCurrentOrder().getNumberOfItems());
    }

    @Test
    public void testTotalCostOfOrder() {
        Product product1 = new PureMilk("A001", "Full Cream Milk", 5.0, new Date(), "30 days",
                "USA", "3.5%", "3.0%");
        Product product2 = new MilkDrink("B001", "Chocolate Milkshake", 3.0, new Date(), "15 days", "Chocolate", "Medium Sugar");

        milkSystem.addProduct(product1, 2);
        milkSystem.addProduct(product2, 1);

        assertEquals(13.0, milkSystem.getCurrentOrder().getTotalCost(), 0.01);
    }

    // 添加更多测试用例以覆盖其他功能

    @Test
    public void testDisplayCatalog() {
        // 实现代码
    }
}