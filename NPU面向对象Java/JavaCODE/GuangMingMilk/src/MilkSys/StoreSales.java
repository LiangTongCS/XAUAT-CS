/**
 * @LiangTong 2023370018
 * @JDK1.8
 */
package MilkSys;
import java.util.*;
import java.text.*;
// StoreSales 类
public class StoreSales {
    private List<Order> orders = new ArrayList<>();

    public void addOrder(Order order) {
        orders.add(order);
    }

    public void removeOrder(Order order) {
        orders.remove(order);
    }

    public Order getOrder(int index) {
        if (index >= 0 && index < orders.size()) {
            return orders.get(index);
        }
        return null;
    }

    public int getNumberOfOrders() {
        return orders.size();
    }

    public List<Order> getOrders() {
        return orders;
    }
}

