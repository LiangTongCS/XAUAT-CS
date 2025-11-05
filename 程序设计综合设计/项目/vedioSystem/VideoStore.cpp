#include "VideoStore.h"

// 设置控制台文本颜色
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // 获取控制台句柄
    SetConsoleTextAttribute(hConsole, color);  // 设置文本颜色
}

void showMenu() {
    setColor(7);
    cout << "\n--- 录像带商店进销存管理系统 ---" << endl;
    cout << "请输入功能菜单所对应的序号来实现您的需求" << endl;
    cout << "1.  查看录像带记录" << endl;
    cout << "2.  添加录像带记录" << endl;
    cout << "3.  修改录像带记录" << endl;
    cout << "4.  删除录像带记录" << endl;
    cout << "5.  查看进货记录" << endl;
    cout << "6.  添加进货记录" << endl;
    cout << "7.  修改进货记录" << endl;
    cout << "8.  删除进货记录" << endl;
    cout << "9.  查看销售信息" << endl;
    cout << "10. 添加销售信息" << endl;
    cout << "11. 修改销售信息" << endl;
    cout << "12. 删除销售信息" << endl;
    cout << "13. 按照录像带ID排序" << endl;
    cout << "14. 按照进货记录ID排序" << endl;
    cout << "15. 按照销售记录ID排序" << endl;
    cout << "16. 按照录像带副本数排序" << endl;
    cout << "17. 按照进货记录价格排序" << endl;
    cout << "18. 按照销售记录价格排序" << endl;
    cout << "19. 查看所有信息" << endl;
    cout << "20. 显示功能菜单" << endl;
    cout << "21. 显示格式说明书" << endl;
    cout << "0.  退出系统" << endl;
}

void addVideoTapeRecord(Inventory& inventory) {
    // 添加文件读取功能
    char readChoice;
    cout << "从本地文件读取录像带记录（VedioTape.txt）并添加到系统请输入 y " << endl;
    cout << "自己手动添加录像带记录请输入 n" << endl;
    cin >> readChoice;

    if (readChoice == 'n' || readChoice == 'N') {
        int id;
        string movieName;
        int copiesAvailable;
        cout << "请输入录像带ID: ";
        cin >> id;
        cin.ignore();  // 忽略输入缓冲区的换行符
        cout << "请输入电影名称: ";
        getline(cin, movieName);
        cout << "请输入库存数量: ";
        cin >> copiesAvailable;
        if (copiesAvailable < 0) {
            setColor(4);
            cout << "库存数量必须是正整数" << endl;
            return;
        }

        // 检查录像带是否已经存在
        VideoTape* video = inventory.findVideoTapeById(id);
        if (!video) {  // 如果该录像带ID不存在，进行添加
            VideoTape newVideo(id, movieName, copiesAvailable);
            inventory.addVideoTape(newVideo);
            setColor(2);
            cout << "录像带记录已添加！" << endl;
        }
        else {
            setColor(4);
            cout << "此ID所对应的录像带已存在, 无法添加。" << endl;
        }
    }
    else if (readChoice == 'y' || readChoice == 'Y') {
        // 打开文件
        ifstream file("VedioTape.txt");
        if (!file) {
            setColor(4);
            cout << "无法打开文件 VedioTape.txt" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string movieName;
            int copiesAvailable;

            // 解析每一行
            ss >> id;  // 读取录像带ID
            ss.ignore();    // 忽略空格
            getline(ss, movieName, ' ');  // 读取电影名称
            ss >> copiesAvailable;  // 读取库存数量

            if (copiesAvailable < 0) {
                setColor(4);
                cout << "库存数量必须是正整数" << endl;
                return;
            }

            // 检查录像带是否已经存在
            VideoTape* video = inventory.findVideoTapeById(id);
            if (!video) {  // 如果该录像带ID不存在，进行添加
                VideoTape newVideo(id, movieName, copiesAvailable);
                inventory.addVideoTape(newVideo);
                setColor(2);
                cout << "录像带记录已添加！" << endl;
            }
            else {
                setColor(4);
                cout << "ID:" << id << "," << "此ID所对应的录像带已存在, 无法添加。" << endl;
            }
        }
    }
}

void searchVideoTape(Inventory& inventory) {
    char readChoice;
    cout << "通过录像带名称检索录像带请输入： y " << endl;
    cout << "通过录像带唯一ID检索录像带请输入： n" << endl;
    cin >> readChoice;

    if (readChoice == 'n' || readChoice == 'N') { // 根据ID查找
        int id;
        cout << "请输入录像带ID: ";
        cin >> id;
        VideoTape* video = inventory.findVideoTapeById(id);
        if (video) {  // 检查指针是否有效
            setColor(2);
            video->displayInfo();  // 使用 -> 调用成员函数，显示录像带信息
        }
        else {
            setColor(4);
            cout << "未找到该录像带。" << endl;
        }
    }
    else if (readChoice == 'y' || readChoice == 'Y') { // 根据名称查找
        string name;
        cout << "请输入录像带名称: ";
        cin >> name;  // 输入录像带名称

        LTvector<VideoTape> videos = inventory.findVideoTapesByName(name);  // 获取匹配名称的录像带

        if (videos.get_size() > 0) {  // 如果找到了录像带
            setColor(2);  // 设置颜色为绿色
            for (size_t i = 0; i < videos.get_size(); ++i) {
                videos[i].displayInfo();  // 显示每一个录像带的信息
            }
        }

        else {
            setColor(4);  // 设置颜色为红色
            cout << "未找到该名称的录像带。" << endl;
        }
    }
}

void modifyVideoTapeRecord(Inventory& inventory) {
    int id;
    cout << "请输入要修改的录像带ID: ";
    cin >> id;
    cin.ignore();  // 忽略输入缓冲区的换行符

    VideoTape* video = inventory.findVideoTapeById(id);
    if (video) {
        string newMovieName;
        int newCopiesAvailable;
        cout << "请输入新的电影名称: ";
        getline(cin, newMovieName);
        cout << "请输入新的库存数量: ";
        cin >> newCopiesAvailable;
        if (newCopiesAvailable < 0) {
            setColor(4);
            cout << "库存数量必须是正整数" << endl;
            return;
        }
        video->setMovieName(newMovieName);
        video->setCopiesAvailable(newCopiesAvailable);
        setColor(2);
        cout << "录像带记录已修改！" << endl;
    }
    else {
        setColor(4);
        cout << "找不到该录像带记录！" << endl;
    }
}

void deleteVideoTapeRecord(Inventory& inventory) {
    int id;
    cout << "请输入要删除的录像带ID: ";
    cin >> id;
    if (inventory.findVideoTapeById(id)) {
        inventory.removeVideoTape(id);
        setColor(2);
        cout << "录像带记录已删除！" << endl;
    }
    else {
        setColor(4);
        cout << "找不到该录像带记录！" << endl;
    }
}

void viewPurchaseRecords(Inventory& inventory) {
    char readChoice;
    cout << "通过进货日期检索进货记录请输入： y " << endl;
    cout << "通过进货记录唯一ID检索请输入： n" << endl;
    cin >> readChoice;

    if (readChoice == 'n' || readChoice == 'N') {
        int id;
        cout << "请输入进货记录ID: ";
        cin >> id;
        PurchaseRecord* record = inventory.findPurchaseRecordById(id);
        if (record) {  // 检查指针是否有效
            setColor(2);
            record->displayPurchaseInfo();  // 使用 -> 调用成员函数，显示进货记录信息
        }
        else {
            setColor(4);
            cout << "未找到该进货记录。" << endl;
        }
    }
    else if (readChoice == 'y' || readChoice == 'Y') {
        // 查询进货记录的日期
        string purchaseDate;
        cout << "请输入进货日期 : ";
        cin >> purchaseDate;  // 输入进货日期

        LTvector<PurchaseRecord> purchases = inventory.findPurchaseRecordsByDate(purchaseDate);  // 获取匹配日期的进货记录

        if (purchases.get_size() > 0) {  // 如果找到了匹配的进货记录
            setColor(2);  // 设置颜色为绿色
            for (size_t i = 0; i < purchases.get_size(); ++i) {
                purchases[i].displayPurchaseInfo();  // 显示每一条进货记录的信息
            }
        }
        else {
            setColor(4);  // 设置颜色为红色
            cout << "未找到该日期的进货记录。" << endl;
        }
    }
}

void addPurchaseRecord(Inventory& inventory) {
    int id;
    int quantity;
    string purchaseDate;
    float price;
    int videoId;

    cout << "请输入进货记录ID: ";
    cin >> id;
    cout << "请输入关联的录像带ID: ";
    cin >> videoId;
    cout << "请输入进货数量: ";
    cin >> quantity;
    cin.ignore();  // 忽略换行符
    cout << "请输入进货日期: ";
    getline(cin, purchaseDate);
    cout << "请输入进货价格: ";
    cin >> price;

    if (quantity < 0) {
        setColor(4);
        cout << "进货数量必须是正整数" << endl;
        return;
    }
    else if (price < 0) {
        setColor(4);
        cout << "进货价格必须是正数" << endl;
        return;
    }

    PurchaseRecord* record = inventory.findPurchaseRecordById(id);
    if (!record) {  // 若无记录，则可添加
        VideoTape* video = inventory.findVideoTapeById(videoId);
        if (video) {
            PurchaseRecord newPurchase(id, *video, quantity, purchaseDate, price);
            inventory.addPurchaseRecord(newPurchase);
            // 更改货品数量
            inventory.purchaseVideoTape(videoId, quantity);
            setColor(2);
            cout << "进货记录已添加！" << endl;
        }
        else {
            setColor(4);
            cout << "录像带ID不存在！" << endl;
        }
    }
    else {
        setColor(4);
        cout << "此ID所对应的进货记录已存在,无法添加。" << endl;
    }
}

void modifyPurchaseRecord(Inventory& inventory) {
    int id;
    cout << "请输入要修改的进货记录ID: ";
    cin >> id;
    cin.ignore();  // 忽略换行符

    PurchaseRecord* record = inventory.findPurchaseRecordById(id);
    if (record) {
        int newQuantity;
        float newPrice;
        cout << "请输入新的进货数量: ";
        cin >> newQuantity;
        cout << "请输入新的进货价格: ";
        cin >> newPrice;

        if (newQuantity < 0) {
            setColor(4);
            cout << "进货数量必须是正整数" << endl;
            return;
        }
        else if (newPrice < 0) {
            setColor(4);
            cout << "进货价格必须是正数" << endl;
            return;
        }

        // 更新进货记录
        int videoIDPR = record->getVideoTape().getId();  // 获取影片ID
        int oldQuantity = record->getQuantity();          // 获取旧的进货数量
        inventory.purchaseVideoTape(videoIDPR, -oldQuantity);  // 撤销旧的进货数量
        inventory.purchaseVideoTape(videoIDPR, newQuantity);  // 添加新的进货数量

        record->setQuantity(newQuantity);  // 更新进货数量
        record->setPrice(newPrice);        // 更新进货价格

        setColor(2);
        cout << "进货记录已修改！" << endl;
    }
    else {
        setColor(4);
        cout << "找不到该进货记录！" << endl;
    }
}

void deletePurchaseRecord(Inventory& inventory) {
    int id;
    cout << "请输入要删除的进货记录ID: ";
    cin >> id;

    PurchaseRecord* record = inventory.findPurchaseRecordById(id);
    if (record) {
        // 更新库存数量
        int videoIDPR = record->getVideoTape().getId(); // 获取影片ID
        int oldQuantity = record->getQuantity();
        inventory.purchaseVideoTape(videoIDPR, -oldQuantity); // 撤销进货数量

        // 删除进货记录
        inventory.removePurchaseRecord(id);
        setColor(2);
        cout << "进货记录已删除！" << endl;
    }
    else {
        setColor(4);
        cout << "找不到该进货记录！" << endl;
    }
}

void viewSalesRecord(Inventory& inventory) {
    char readChoice;
    cout << "通过销售日期检索销售信息请输入： y" << endl;
    cout << "通过销售记录唯一ID检索请输入： n" << endl;
    cin >> readChoice;

    if (readChoice == 'n' || readChoice == 'N') {
        int id;
        cout << "请输入销售记录ID: ";
        cin >> id;
        SalesRecord* record = inventory.findSalesRecordById(id);
        if (record) {  // 检查指针是否有效
            setColor(2);
            record->displaySalesInfo();  // 显示销售信息
        }
        else {
            setColor(4);
            cout << "未找到该销售记录。" << endl;
        }
    }
    else if (readChoice == 'y' || readChoice == 'Y') {
        string saleDate;
        cout << "请输入销售日期: ";
        cin >> saleDate;  // 输入销售日期

        LTvector<SalesRecord> sales = inventory.findSalesRecordsByDate(saleDate);  // 获取匹配日期的销售记录

        if (sales.get_size() > 0) {  // 如果找到了匹配的销售记录
            setColor(2);  // 设置颜色为绿色
            for (size_t i = 0; i < sales.get_size(); ++i) {
                sales[i].displaySalesInfo();  // 显示每一条销售记录的信息
            }
        }

        else {
            setColor(4);  // 设置颜色为红色
            cout << "未找到该日期的销售记录。" << endl;
        }
    }
}

void deleteSalesRecord(Inventory& inventory) {
    int id;
    cout << "请输入要删除的销售记录ID: ";
    cin >> id;

    SalesRecord* record = inventory.findSalesRecordById(id);
    if (record) {
        // 更新库存数量
        int videoIDPR = record->getVideoTape().getId();  // 获取影片ID
        int oldQuantity = record->getQuantitySold();
        inventory.salesVideoTape(videoIDPR, -oldQuantity);  // 撤销销售数量

        // 删除销售信息
        inventory.removeSalesRecord(id);
        setColor(2);
        cout << "销售信息已删除！" << endl;
    }
    else {
        setColor(4);
        cout << "找不到该销售信息！" << endl;
    }
}


void addSalesRecord(Inventory& inventory) {
    int id, quantitySold, videoId;
    string saleDate;
    float price;

    cout << "请输入销售记录ID: ";
    cin >> id;
    cout << "请输入关联的录像带ID: ";
    cin >> videoId;
    cout << "请输入销售数量: ";
    cin >> quantitySold;
    cin.ignore();  // 忽略换行符
    cout << "请输入销售日期: ";
    getline(cin, saleDate);
    cout << "请输入销售价格: ";
    cin >> price;

    if (quantitySold < 0) {
        setColor(4);
        cout << "销售数量必须是正整数" << endl;
        return;
    }
    else if (price < 0) {
        setColor(4);
        cout << "销售价格必须是正数" << endl;
        return;
    }

    SalesRecord* record = inventory.findSalesRecordById(id);
    if (!record) {  // 检查销售记录是否已存在
        VideoTape* video = inventory.findVideoTapeById(videoId);
        if (video) {
            SalesRecord newSales(id, *video, quantitySold, saleDate, price);
            inventory.addSalesRecord(newSales);
            // 更新录像带库存数量
            int i = inventory.salesVideoTape(videoId, quantitySold);
            if (i) {
                inventory.removeSalesRecord(id);
            }
            else {
                setColor(2);
                cout << "销售信息已添加！" << endl;
            }
        }
        else {
            setColor(4);
            cout << "录像带ID不存在！" << endl;
        }
    }
    else {
        setColor(4);
        cout << "此ID所对应的销售记录已存在,无法添加。" << endl;
    }
}

void modifySalesRecord(Inventory& inventory) {
    int id;
    cout << "请输入要修改的销售记录ID: ";
    cin >> id;
    cin.ignore();  // 忽略换行符

    SalesRecord* record = inventory.findSalesRecordById(id);
    if (record) {
        int newQuantitySold;
        float newPrice;
        cout << "请输入新的销售数量: ";
        cin >> newQuantitySold;
        cout << "请输入新的销售价格: ";
        cin >> newPrice;

        if (newQuantitySold < 0) {
            setColor(4);
            cout << "销售数量必须是正整数" << endl;
            return;
        }
        else if (newPrice < 0) {
            setColor(4);
            cout << "销售价格必须是正数" << endl;
            return;
        }

        // 更新库存数量
        int videoIDPR = record->getVideoTape().getId();  // 获取影片ID
        int oldQuantity = record->getQuantitySold();
        inventory.salesVideoTape(videoIDPR, -oldQuantity);  // 撤销原销售数量
        int i = inventory.salesVideoTape(videoIDPR, newQuantitySold);  // 设置新销售数量
        if (i) {
            inventory.salesVideoTape(videoIDPR, oldQuantity);  // 还原原销售数量
            setColor(4);
            cout << "无法修改！" << endl;
            cout << "销售数量必须不大于录像带数量！" << endl;
        }
        else {
            // 更新销售信息
            record->setQuantitySold(newQuantitySold);
            record->setPrice(newPrice);
            setColor(2);
            cout << "销售信息已修改！" << endl;
        }
    }
    else {
        setColor(4);
        cout << "找不到该销售信息！" << endl;
    }
}






void runProgram() {
    setColor(3);
    cout << "欢迎使用录像带商店进销存管理系统" << endl;
    cout << "制作人：梁桐   班级：计算机2203 " << endl;
    cout << "密码是我的学号：" ;
    setColor(6);
    cout << "2209060322" << endl;
    setColor(3);
    cout << "------------------------------------------" << endl;
    cout << "请输入密码启动程序，祝您使用愉快！" << endl;
    long long passWord;
    cin >> passWord;
    if (passWord != 2209060322) {
        setColor(4);
        cout <<"密码错误！" << endl;
    }
    else {
        // 创建库存对象
        Inventory inventory;
        showMenu();  // 显示功能菜单
        while (true) {
            setColor(3);
            cout << "输入20显示功能菜单" << endl;
            cout << "输入21显示格式说明书" << endl;
            cout << "请输入数字选择你要使用的功能：" << endl;
            setColor(7);
            int choice;
            cin >> choice;  // 获取用户选择

            switch (choice) {
            case 1: {
                searchVideoTape(inventory);  // 调用提取的函数
                break;
            }
            case 2: { // 添加录像带记录
                addVideoTapeRecord(inventory);
                break;
            }
            case 3: { // 修改录像带记录
                modifyVideoTapeRecord(inventory);
                break;
            }
            case 4: { // 删除录像带记录
                deleteVideoTapeRecord(inventory);
                break;
            }
            case 5: { // 查看进货记录
                viewPurchaseRecords(inventory);
                break;
            }
            case 6: { // 添加进货记录
                addPurchaseRecord(inventory);
                break;
            }
            case 7: { // 修改进货记录
                modifyPurchaseRecord(inventory);
                break;
            }
            case 8: { // 删除进货记录
                deletePurchaseRecord(inventory);
                break;
            }
            case 9: { // 查看销售信息
                viewSalesRecord(inventory);
                break;
            }
            case 10: { // 添加销售信息
                addSalesRecord(inventory);
                break;
            }
            case 11: { // 修改销售信息
                modifySalesRecord(inventory);
                break;
            }
            case 12: { // 删除销售信息
                deleteSalesRecord(inventory);
                break;
            }
            case 13: { // 通过录像带ID排序
                inventory.sortVideoTapeById();
                break;
            }
            case 14: {
                //按照进货记录ID排序
                inventory.sortPurchById();
                break;
            }
            case 15: { 
                //按照销售记录ID排序
                inventory.sortSaleById();
                break;
            }
            case 16: { 
                //按照录像带副本数排序
                inventory.sortVideoTapeByNum();
                break;
            }
            case 17: { 
                //按照进货价格排序
                inventory.sortPurchByPri();
                break;
            }
            case 18: { 
                //按照销售价格排序
                inventory.sortSaleByPri();
                break;
            }
            case 19: { // 查看所有记录
                setColor(2);
                inventory.displayInventory();
                break;
            }
            case 20: {
                showMenu();  // 显示功能菜单
                break;
            }
            case 21: {
                setColor(6);
                cout << "------------------------------------------" << endl;
                cout << "---格式说明书---" << endl;
                cout << "所有功能选择输入必须为正整数" << endl;
                cout << "所有ID必须为正整数" << endl;
                cout << "所有价格须为正实数" << endl;
                cout << "所有副本数量输入必须为正整数" << endl;
                cout << "所有录像带名称中空格使用‘-’字符替换" << endl;
                cout << "所有日期格式须为xxxx-yy-zz" << endl;
                cout << "VedioTape.txt文件内每行内容格式应为" << endl;
                cout << "ID 电影名称 副本数" << endl;
                cout << "VedioTape.txt文件内不得出现非ASCII码字符" << endl;
                cout << "------------------------------------------" << endl;
                break;
            }
            case 0: { // 退出
                setColor(2);
                cout << "谢谢使用，程序退出！" << endl;
                return;
            }
            default:
                setColor(4);
                cout << "无效输入，请重新选择！" << endl;
                break;
            }
        }
    }
}




