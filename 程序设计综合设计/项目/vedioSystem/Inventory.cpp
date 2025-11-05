#include "VideoStore.h"
using namespace std;

// 添加录像带
void Inventory::addVideoTape(VideoTape video) {
    videoTapes.push_back(video);
}

// 删除录像带
void Inventory::removeVideoTape(int videoId) {
    for (size_t i = 0; i < videoTapes.get_size(); ++i) {
        if (videoTapes[i].getId() == videoId) {
            // 使用手动移位操作来模拟 std::vector 的 erase 功能
            for (size_t j = i; j < videoTapes.get_size() - 1; ++j) {
                videoTapes[j] = videoTapes[j + 1];
            }
            videoTapes.pop_back(); // 移除最后一个重复元素
            return;
        }
    }
}


// 添加进货记录
void Inventory::addPurchaseRecord(PurchaseRecord record) {
    purchaseRecords.push_back(record);
}

// 删除进货记录
void Inventory::removePurchaseRecord(int recordId) {
    for (size_t i = 0; i < purchaseRecords.get_size(); ++i) {
        if (purchaseRecords[i].getId() == recordId) {
            // 使用手动移位操作来模拟 std::vector 的 erase 功能
            for (size_t j = i; j < purchaseRecords.get_size() - 1; ++j) {
                purchaseRecords[j] = purchaseRecords[j + 1];
            }
            purchaseRecords.pop_back(); // 移除最后一个重复元素
            return;
        }
    }
}


// 添加销售记录
void Inventory::addSalesRecord(SalesRecord record) {
    salesRecords.push_back(record);
}

// 删除销售记录
void Inventory::removeSalesRecord(int recordId) {
    for (size_t i = 0; i < salesRecords.get_size(); ++i) {
        if (salesRecords[i].getId() == recordId) {
            // 使用手动移位操作来模拟 std::vector 的 erase 功能
            for (size_t j = i; j < salesRecords.get_size() - 1; ++j) {
                salesRecords[j] = salesRecords[j + 1];
            }
            salesRecords.pop_back(); // 移除最后一个重复元素
            return;
        }
    }
}

// 查找录像带
VideoTape* Inventory::findVideoTapeById(int videoId) {
    for (size_t i = 0; i < videoTapes.get_size(); ++i) {
        if (videoTapes[i].getId() == videoId) {
            return &videoTapes[i];
        }
    }
    return nullptr;
}

// 根据录像带名称查找录像带
LTvector<VideoTape> Inventory::findVideoTapesByName(const string& videoName) {
    LTvector<VideoTape> foundVideos;
    for (size_t i = 0; i < videoTapes.get_size(); ++i) {
        if (videoTapes[i].getMovieName() == videoName) {  // 如果录像带名称匹配
            foundVideos.push_back(videoTapes[i]);  // 将该录像带添加到返回的结果中
        }
    }
    return foundVideos;  // 返回找到的录像带列表
}

// 查找进货记录
PurchaseRecord* Inventory::findPurchaseRecordById(int recordId) {
    for (size_t i = 0; i < purchaseRecords.get_size(); ++i) {
        if (purchaseRecords[i].getId() == recordId) {
            return &purchaseRecords[i];
        }
    }
    return nullptr;
}

// 根据进货日期查询进货记录
LTvector<PurchaseRecord> Inventory::findPurchaseRecordsByDate(const string& purchaseDate) {
    LTvector<PurchaseRecord> result;
    for (size_t i = 0; i < purchaseRecords.get_size(); ++i) {
        if (purchaseRecords[i].getPurchaseDate() == purchaseDate) {
            result.push_back(purchaseRecords[i]);
        }
    }
    return result;
}

// 根据销售日期查询销售记录
LTvector<SalesRecord> Inventory::findSalesRecordsByDate(const string& saleDate) {
    LTvector<SalesRecord> result;
    for (size_t i = 0; i < salesRecords.get_size(); ++i) {
        if (salesRecords[i].getSaleDate() == saleDate) {
            result.push_back(salesRecords[i]);
        }
    }
    return result;
}

// 查找销售记录
SalesRecord* Inventory::findSalesRecordById(int recordId) {
    for (size_t i = 0; i < salesRecords.get_size(); ++i) {
        if (salesRecords[i].getId() == recordId) {
            return &salesRecords[i];
        }
    }
    return nullptr;
}

// 修改录像带信息
void Inventory::modifyVideoTape(int videoId, string newMovieName, int newCopiesAvailable) {
    VideoTape* video = findVideoTapeById(videoId);
    if (video) {
        video->setMovieName(newMovieName);
        video->setCopiesAvailable(newCopiesAvailable);
    }
}

// 修改进货记录
void Inventory::modifyPurchaseRecord(int recordId, int newQuantity, float newPrice) {
    PurchaseRecord* record = findPurchaseRecordById(recordId);
    if (record) {
        record->setQuantity(newQuantity);
        record->setPrice(newPrice);
    }
}

// 修改销售记录
void Inventory::modifySalesRecord(int recordId, int newQuantitySold, float newPrice) {
    SalesRecord* record = findSalesRecordById(recordId);
    if (record) {
        record->setQuantitySold(newQuantitySold);
        record->setPrice(newPrice);
    }
}
// 显示库存信息
void Inventory::displayInventory() const {
    cout << "录像带记录信息： " << endl;
    for (size_t i = 0; i < videoTapes.get_size(); ++i) {
        videoTapes[i].displayInfo();
    }
    cout << endl;

    cout << "进货记录信息：" << endl;
    for (size_t i = 0; i < purchaseRecords.get_size(); ++i) {
        purchaseRecords[i].displayPurchaseInfo();
        cout << endl;
    }
    cout << endl;

    cout << "销售记录信息： " << endl;
    for (size_t i = 0; i < salesRecords.get_size(); ++i) {
        salesRecords[i].displaySalesInfo();
        cout << endl;
    }
}

// 进货录像带，增加副本数
void Inventory::purchaseVideoTape(int videoId, int quantity) {
    VideoTape* tape = findVideoTapeById(videoId);  // 查找录像带
    if (tape != nullptr) {
        int currentCopies = tape->getCopiesAvailable();  // 获取当前可用副本数
        tape->setCopiesAvailable(currentCopies + quantity);  // 更新副本数
        cout << "Successfully purchased " << quantity << " copies of \"" << tape->getMovieName() << "\"." << endl;
    }
    else {
        cout << "VideoTape with ID " << videoId << " not found." << endl;
    }
}

// 卖货录像带，减少副本数
int Inventory::salesVideoTape(int videoId, int quantitySold) {
    VideoTape* tape = findVideoTapeById(videoId);  // 查找录像带
    if (tape != nullptr) {
        int currentCopies = tape->getCopiesAvailable();  // 获取当前可用副本数
        if (quantitySold <= currentCopies) {
            tape->setCopiesAvailable(currentCopies - quantitySold);  // 更新副本数
            return 0;
        }
        else {
            setColor(4);
            cout << "出售量大于存货量，无法添加！ " << endl;
            return 1;
        }
    }
    else {
        cout << "VideoTape with ID " << videoId << " not found." << endl;
    }
}

void Inventory::sortVideoTapeById() {
    quickSort(videoTapes, 0, videoTapes.get_size() - 1);  // 使用快速排序
    setColor(2);
    cout << "按照录像带ID排序完成！" << endl;
}

void Inventory::sortPurchById() {
    quickSort(purchaseRecords, 0, purchaseRecords.get_size() - 1);  // 使用快速排序
    setColor(2);
    cout << "按照进货记录ID排序完成！" << endl;
}

void Inventory::sortSaleById() {
    quickSort(salesRecords, 0, salesRecords.get_size() - 1);  // 使用快速排序
    setColor(2);
    cout << "按照销售记录ID排序完成！" << endl;
}

void Inventory::sortVideoTapeByNum() {
    quickSortNum(videoTapes, 0, videoTapes.get_size() - 1);  // 使用快速排序
    setColor(2);
    cout << "按照录像带副本数排序完成！" << endl;
}

void Inventory::sortPurchByPri() {
    quickSortPri(purchaseRecords, 0, purchaseRecords.get_size() - 1);  // 使用快速排序
    setColor(2);
    cout << "按照进货记录价格排序完成！" << endl;
}

void Inventory::sortSaleByPri() {
    quickSortPri(salesRecords, 0, salesRecords.get_size() - 1);  // 使用快速排序
    setColor(2);
    cout << "按照销售记录价格排序完成！" << endl;
}
