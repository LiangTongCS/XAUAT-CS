package milksystem;
import java.util.ArrayList;
import java.util.Date;

// 订单类 Order
public class Order {
    private ArrayList<SaleItem> saleItems; // 销售项列表

    public Order() {
        this.saleItems = new ArrayList<>();
    }

    // 添加销售项到订单
    public void addSaleItem(SaleItem saleItem) {
        int index = findSaleItemIndex(saleItem.getProduct());
        if (index != -1) {
            // 如果该产品已经在订单中，修改其数量
            SaleItem existingSaleItem = saleItems.get(index);
            existingSaleItem.setQuantity(existingSaleItem.getQuantity() + saleItem.getQuantity());
        } else {
            saleItems.add(saleItem);
        }
    }

    // 从订单中移除销售项
    public void removeSaleItem(Product product) {
        int index = findSaleItemIndex(product);
        if (index != -1) {
            saleItems.remove(index);
        }
    }

    // 获取销售项数量
    public int getNumberOfItems() {
        return saleItems.size();
    }

    // 获取订单总额
    public double getTotalCost() {
        double totalCost = 0;
        for (SaleItem saleItem : saleItems) {
            totalCost += saleItem.getValue();
        }
        return totalCost;
    }

    // 根据产品查找销售项的索引
    private int findSaleItemIndex(Product product) {
        for (int i = 0; i < saleItems.size(); i++) {
            SaleItem saleItem = saleItems.get(i);
            if (saleItem.getProduct().equals(product)) {
                return i;
            }
        }
        return -1;
    }

    // 显示所有销售项
    public void displaySaleItems() {
        for (SaleItem saleItem : saleItems) {
            System.out.println("数量：" + saleItem.getQuantity());
            System.out.println("代码：" + saleItem.getProduct().getCode());
            System.out.println("价格：" + saleItem.getProduct().getPrice());
        }
    }
}

