package MilkGood;
import java.util.ArrayList;
import java.util.Date;

// 订单类，包含多个销售项
public class Order {
    private ArrayList<SaleItem> saleItems;

    public Order() {
        saleItems = new ArrayList<>();
    }

    public void addSaleItem(SaleItem saleItem) {
        saleItems.add(saleItem);
    }

    public void removeSaleItem(SaleItem saleItem) {
        saleItems.remove(saleItem);
    }

    public SaleItem getSaleItem(int index) {
        return saleItems.get(index);
    }

    public int getNumberOfItems() {
        return saleItems.size();
    }

    public double getTotalCost() {
        double totalCost = 0.0;
        for (SaleItem saleItem : saleItems) {
            totalCost += saleItem.getValue();
        }
        return totalCost;
    }
}
