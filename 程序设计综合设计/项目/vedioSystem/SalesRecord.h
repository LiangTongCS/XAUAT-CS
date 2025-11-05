#ifndef SALESRECORD_H
#define SALESRECORD_H

#include "VideoTape.h"
#include <string>
using namespace std;

class SalesRecord {
private:
    int id;               // 销售记录ID
    VideoTape videoTape;  // 关联的录像带对象
    int quantitySold;     // 销售数量
    string saleDate;      // 销售日期
    float price;          // 销售价格

public:

    // 默认构造函数
    SalesRecord();
    // 构造函数
    SalesRecord(int id, VideoTape videoTape, int quantitySold, string saleDate, float price);

    // Getter 和 Setter 方法
    int getId() const;
    void setId(int id);

    VideoTape getVideoTape() const;
    void setVideoTape(VideoTape videoTape);

    int getQuantitySold() const;
    void setQuantitySold(int quantitySold);

    string getSaleDate() const;
    void setSaleDate(string saleDate);

    float getPrice() const;
    void setPrice(float price);

    // 显示销售信息
    void displaySalesInfo() const;
    float calculateTotalSales() const;
};

#endif // SALESRECORD_H
