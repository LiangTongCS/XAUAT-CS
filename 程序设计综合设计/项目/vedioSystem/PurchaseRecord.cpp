#include "PurchaseRecord.h"
#include <iostream>
using namespace std;

// 默认构造函数
PurchaseRecord::PurchaseRecord()
    : id(0),
    videoTape(VideoTape()),  // 默认构造 VideoTape 对象
    quantity(0),
    purchaseDate(""),
    price(0.0f) {
}

// 构造函数
PurchaseRecord::PurchaseRecord(int id, VideoTape videoTape, int quantity, string purchaseDate, float price) {
    this->id = id;
    this->videoTape = videoTape;
    this->quantity = quantity;
    this->purchaseDate = purchaseDate;
    this->price = price;
}

// Getter 和 Setter 方法
int PurchaseRecord::getId() const {
    return id;
}

void PurchaseRecord::setId(int id) {
    this->id = id;
}

VideoTape PurchaseRecord::getVideoTape() const {
    return videoTape;
}

void PurchaseRecord::setVideoTape(VideoTape videoTape) {
    this->videoTape = videoTape;
}

int PurchaseRecord::getQuantity() const {
    return quantity;
}

void PurchaseRecord::setQuantity(int quantity) {
    this->quantity = quantity;
}

string PurchaseRecord::getPurchaseDate() const {
    return purchaseDate;
}

void PurchaseRecord::setPurchaseDate(string purchaseDate) {
    this->purchaseDate = purchaseDate;
}

float PurchaseRecord::getPrice() const {
    return price;
}

void PurchaseRecord::setPrice(float price) {
    this->price = price;
}

// 显示进货记录信息
void PurchaseRecord::displayPurchaseInfo() const {
    cout << "进货记录ID : " << id << endl;
    videoTape.displayInfo();
    cout << "进货数量 : " << quantity << endl;
    cout << "进货日期 : " << purchaseDate << endl;
    cout << "进货价格 : " << price << endl;
}
