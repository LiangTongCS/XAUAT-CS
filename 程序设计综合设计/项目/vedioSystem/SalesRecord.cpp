#include "SalesRecord.h"
#include <iostream>
using namespace std;


// 默认构造函数
SalesRecord::SalesRecord()
    : id(0),                          // 销售记录ID 默认为 0
    videoTape(VideoTape()),          // 使用 VideoTape 的默认构造函数
    quantitySold(0),                 // 销售数量 默认为 0
    saleDate(""),                    // 销售日期 默认为 空字符串
    price(0.0f)                      // 销售价格 默认为 0.0
{
}

// 构造函数
SalesRecord::SalesRecord(int id, VideoTape videoTape, int quantitySold, string saleDate, float price) {
    this->id = id;
    this->videoTape = videoTape;
    this->quantitySold = quantitySold;
    this->saleDate = saleDate;
    this->price = price;
}

// Getter 和 Setter 方法
int SalesRecord::getId() const {
    return id;
}

void SalesRecord::setId(int id) {
    this->id = id;
}

VideoTape SalesRecord::getVideoTape() const {
    return videoTape;
}

void SalesRecord::setVideoTape(VideoTape videoTape) {
    this->videoTape = videoTape;
}

int SalesRecord::getQuantitySold() const {
    return quantitySold;
}

void SalesRecord::setQuantitySold(int quantitySold) {
    this->quantitySold = quantitySold;
}

string SalesRecord::getSaleDate() const {
    return saleDate;
}

void SalesRecord::setSaleDate(string saleDate) {
    this->saleDate = saleDate;
}

float SalesRecord::getPrice() const {
    return price;
}

void SalesRecord::setPrice(float price) {
    this->price = price;
}

// 显示销售信息
void SalesRecord::displaySalesInfo() const {
    cout << "销售记录ID : " << id << endl;
    videoTape.displayInfo();
    cout << "销售数量 : " << quantitySold << endl;
    cout << "销售日期 : " << saleDate << endl;
    cout << "销售价格 : " << price << endl;
}

// 计算销售总额
float SalesRecord::calculateTotalSales() const {
    return quantitySold * price;
}
