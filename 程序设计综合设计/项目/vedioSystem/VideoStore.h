#ifndef VIDEOSTORE_H
#define VIDEOSTORE_H

#include <iostream>
#include <string>
#include "VideoTape.h"
#include "PurchaseRecord.h"
#include "SalesRecord.h"
#include "Inventory.h"
#include <windows.h>
#include <fstream>
#include <sstream>

using namespace std;

// 设置控制台文本颜色
void setColor(int color);

// 显示菜单
void showMenu();
void runProgram();  // 声明函数
// 快速排序：针对任何类型的容器（例如 VideoTape、PurchaseRecord、SalesRecord）
template <typename T>
void quickSort(LTvector<T>& items, int low, int high) {
    if (low < high) {
        int pivot = partition(items, low, high);  // 找到基准
        quickSort(items, low, pivot - 1);  // 排序基准左边部分
        quickSort(items, pivot + 1, high);  // 排序基准右边部分
    }
}

// 分区操作：通用的分区函数，返回排序后的基准位置
template <typename T>
int partition(LTvector<T>& items, int low, int high) {
    int pivot = items[high].getId();  // 选取最后一个元素作为基准
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (items[j].getId() <= pivot) {  // 如果当前元素小于或等于基准
            i++;
            swap(items[i], items[j]);  // 交换
        }
    }
    swap(items[i + 1], items[high]);  // 把基准放到正确的位置
    return (i + 1);
}

// 按照副本数量排序
template <typename T>
void quickSortNum(LTvector<T>& items, int low, int high) {
    if (low < high) {
        int pivot = partitionNum(items, low, high);  // 找到基准
        quickSortNum(items, low, pivot - 1);  // 排序基准左边部分
        quickSortNum(items, pivot + 1, high);  // 排序基准右边部分
    }
}

// 分区操作：按照副本数量排序
template <typename T>
int partitionNum(LTvector<T>& items, int low, int high) {
    int pivot = items[high].getCopiesAvailable();  // 选取最后一个元素作为基准
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (items[j].getCopiesAvailable() <= pivot) {  // 如果当前元素小于或等于基准
            i++;
            swap(items[i], items[j]);  // 交换
        }
    }
    swap(items[i + 1], items[high]);  // 把基准放到正确的位置
    return (i + 1);
}

// 按照价格排序
template <typename T>
void quickSortPri(LTvector<T>& items, int low, int high) {
    if (low < high) {
        int pivot = partitionPri(items, low, high);  // 找到基准
        quickSortPri(items, low, pivot - 1);  // 排序基准左边部分
        quickSortPri(items, pivot + 1, high);  // 排序基准右边部分
    }
}

// 分区操作：按照价格排序
template <typename T>
int partitionPri(LTvector<T>& items, int low, int high) {
    int pivot = items[high].getPrice();  // 选取最后一个元素作为基准
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (items[j].getPrice() <= pivot) {  // 如果当前元素小于或等于基准
            i++;
            swap(items[i], items[j]);  // 交换
        }
    }
    swap(items[i + 1], items[high]);  // 把基准放到正确的位置
    return (i + 1);
}

#endif // VIDEOSTORE_H
