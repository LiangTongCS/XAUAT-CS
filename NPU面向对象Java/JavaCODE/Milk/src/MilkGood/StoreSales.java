package MilkGood;
import java.util.ArrayList;
import java.util.Date;

// 销售类，包含多个订单
public class StoreSales {
    private ArrayList<Order> orders;

    public StoreSales() {
        orders = new ArrayList<>();
    }

    public void addOrder(Order order) {
        orders.add(order);
    }

    public void removeOrder(Order order) {
        orders.remove(order);
    }

    public Order getOrder(int index) {
        return orders.get(index);
    }

    public int getNumberOfOrders() {
        return orders.size();
    }
}
