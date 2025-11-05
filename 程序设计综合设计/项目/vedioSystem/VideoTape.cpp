#include "VideoTape.h"

// 默认构造函数的实现
VideoTape::VideoTape() : id(0), movieName(""), copiesAvailable(0) {}

// 带参数构造函数的实现
VideoTape::VideoTape(int id, const string& movieName, int copiesAvailable)
    : id(id), movieName(movieName), copiesAvailable(copiesAvailable) {}

// 获取录像带ID
int VideoTape::getId() const {
    return id;
}

// 获取电影名称
string VideoTape::getMovieName() const {
    return movieName;
}

// 获取可用副本数
int VideoTape::getCopiesAvailable() const {
    return copiesAvailable;
}

// 设置电影名称
void VideoTape::setMovieName(const string& newMovieName) {
    movieName = newMovieName;
}

// 设置可用副本数
void VideoTape::setCopiesAvailable(int newCopiesAvailable) {
    copiesAvailable = newCopiesAvailable;
}

// 显示录像带信息
void VideoTape::displayInfo() const {
    cout << "录像带ID : " << id << ",  录像带名称 : " << movieName
        << ", 副本数量 : " << copiesAvailable << endl;
}
