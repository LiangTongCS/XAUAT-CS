#ifndef INVENTORY_H
#define INVENTORY_H

#include "VideoTape.h"
#include "PurchaseRecord.h"
#include "SalesRecord.h"
#include "LTvector.h"
using namespace std;

class Inventory {
private:
    LTvector<VideoTape> videoTapes;         // 录像带列表
    LTvector<PurchaseRecord> purchaseRecords;  // 进货记录列表
    LTvector<SalesRecord> salesRecords;      // 销售记录列表

public:
    // 添加录像带、进货记录、销售记录的方法
    void addVideoTape(VideoTape video);
    void removeVideoTape(int videoId);
    void addPurchaseRecord(PurchaseRecord record);
    void removePurchaseRecord(int recordId);
    void addSalesRecord(SalesRecord record);
    void removeSalesRecord(int recordId);

    // 查找录像带、进货记录、销售记录的方法
    VideoTape* findVideoTapeById(int videoId);
    LTvector<VideoTape> findVideoTapesByName(const string& videoName);

    // 在 Inventory 类中添加根据进货日期查询进货记录的函数
    LTvector<PurchaseRecord> findPurchaseRecordsByDate(const string& purchaseDate);

    // 在 Inventory 类中添加根据销售日期查询销售记录的函数
    LTvector<SalesRecord> findSalesRecordsByDate(const string & saleDate);

    PurchaseRecord* findPurchaseRecordById(int recordId);
    SalesRecord* findSalesRecordById(int recordId);

    // 修改录像带、进货记录、销售记录的方法
    void modifyVideoTape(int videoId, string newMovieName, int newCopiesAvailable);
    void modifyPurchaseRecord(int recordId, int newQuantity, float newPrice);
    void modifySalesRecord(int recordId, int newQuantitySold, float newPrice);

    // 显示库存信息
    void displayInventory() const;

    // 进货录像带，增加副本数
    void purchaseVideoTape(int videoId, int quantity);
    // 卖货录像带，增加副本数
    int salesVideoTape(int videoId, int quantity);
    //按照录像带ID排序
    void sortVideoTapeById();
    //按照进货记录ID排序
    void sortPurchById();
    //按照销售记录ID排序
    void sortSaleById();
    //按照录像带副本数排序
    void sortVideoTapeByNum();
    //按照进货价格排序
    void sortPurchByPri();
    //按照销售价格排序
    void sortSaleByPri();
};

#endif // INVENTORY_H
