#ifndef VIDEOTAPE_H
#define VIDEOTAPE_H

#include <string>
#include <iostream>
using namespace std;

class VideoTape {
private:
    int id;                     // 录像带的ID
    string movieName;           // 电影名称
    int copiesAvailable;        // 可用副本数

public:
    // 默认构造函数声明
    VideoTape();

    // 带参数的构造函数声明
    VideoTape(int id, const string& movieName, int copiesAvailable);

    // 获取录像带ID
    int getId() const;

    // 获取电影名称
    string getMovieName() const;

    // 获取可用副本数
    int getCopiesAvailable() const;

    // 设置电影名称
    void setMovieName(const string& newMovieName);

    // 设置可用副本数
    void setCopiesAvailable(int newCopiesAvailable);

    // 显示录像带信息
    void displayInfo() const;
};

#endif // VIDEOTAPE_H
