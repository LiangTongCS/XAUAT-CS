package milksystem;
import java.util.ArrayList;
import java.util.Date;

// 商店销售记录类 StoreSales
public class StoreSales {
    private ArrayList<Order> orders; // 订单列表

    public StoreSales() {
        this.orders = new ArrayList<>();
    }

    // 添加订单到销售记录
    public void addOrder(Order order) {
        orders.add(order);
    }

    // 从销售记录中移除订单
    public void removeOrder(Order order) {
        orders.remove(order);
    }

    // 根据索引获取订单
    public Order getOrder(int index) {
        if (index >= 0 && index < orders.size()) {
            return orders.get(index);
        }
        return null;
    }

    // 获取订单数量
    public int getNumberOfOrders() {
        return orders.size();
    }

    // 显示所有销售订单
    public void displayOrders() {
        for (Order order : orders) {
            order.displaySaleItems();
            System.out.println("订单总额：" + order.getTotalCost());
        }
    }
}

