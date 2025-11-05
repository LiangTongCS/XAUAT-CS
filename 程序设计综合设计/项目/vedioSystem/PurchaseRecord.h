#ifndef PURCHASERECORD_H
#define PURCHASERECORD_H

#include "VideoTape.h"
#include <string>
using namespace std;

class PurchaseRecord {
private:
    int id;               // 进货记录ID
    VideoTape videoTape;  // 关联的录像带对象
    int quantity;         // 进货数量
    string purchaseDate;  // 进货日期
    float price;          // 进货价格

public:
    // 默认构造函数
    PurchaseRecord();
    // 构造函数
    PurchaseRecord(int id, VideoTape videoTape, int quantity, string purchaseDate, float price);

    // Getter 和 Setter 方法
    int getId() const;
    void setId(int id);

    VideoTape getVideoTape() const;
    void setVideoTape(VideoTape videoTape);

    int getQuantity() const;
    void setQuantity(int quantity);

    string getPurchaseDate() const;
    void setPurchaseDate(string purchaseDate);

    float getPrice() const;
    void setPrice(float price);

    // 显示进货记录信息
    void displayPurchaseInfo() const;
};

#endif // PURCHASERECORD_H
