/**
 * @LiangTong 2023370018
 * @JDK1.8
 */
package MilkSys;
import java.util.*;
import java.text.*;
// Order 类
public class Order {
    private List<SaleItem> items = new ArrayList<>();

    public void addSaleItem(SaleItem saleItem) {
        items.add(saleItem);
    }

    public void removeSaleItem(SaleItem saleItem) {
        items.remove(saleItem);
    }

    public SaleItem getSaleItem(Product product) {
        for (SaleItem item : items) {
            if (item.getProduct() == product) {
                return item;
            }
        }
        return null;
    }

    public int getNumberOfItems() {
        return items.size();
    }

    public double getTotalCost() {
        double total = 0;
        for (SaleItem item : items) {
            total += item.getValue();
        }
        return total;
    }

    public List<SaleItem> getItems() {
        return items;
    }
}
