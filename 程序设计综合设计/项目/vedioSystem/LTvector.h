#ifndef LTVECTOR_H
#define LTVECTOR_H

#include <stdexcept>
#include <cstddef> // for size_t

template <typename T>
class LTvector {
private:
    T* data;          // 动态分配的数组
    size_t capacity;  // 容量
    size_t size;      // 当前元素个数

    void resize(size_t new_capacity);

public:
    LTvector();                          // 默认构造函数
    LTvector(const LTvector& other);     // 拷贝构造函数
    LTvector& operator=(const LTvector& other); // 赋值运算符
    ~LTvector();                         // 析构函数

    void push_back(const T& value);      // 添加元素
    void pop_back();                     // 移除最后一个元素
    T& operator[](size_t index);         // 下标运算符
    const T& operator[](size_t index) const;

    size_t get_size() const;             // 获取当前大小
    size_t get_capacity() const;         // 获取容量
    bool empty() const;                  // 判断是否为空
    void clear();                        // 清空所有元素
};

// 默认构造函数
template <typename T>
LTvector<T>::LTvector() : data(nullptr), capacity(0), size(0) {}

// 拷贝构造函数
template <typename T>
LTvector<T>::LTvector(const LTvector& other)
    : data(nullptr), capacity(other.capacity), size(other.size) {
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

// 赋值运算符
template <typename T>
LTvector<T>& LTvector<T>::operator=(const LTvector& other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

// 析构函数
template <typename T>
LTvector<T>::~LTvector() {
    delete[] data;
}

// 动态调整容量
template <typename T>
void LTvector<T>::resize(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

// 添加元素
template <typename T>
void LTvector<T>::push_back(const T& value) {
    if (size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[size++] = value;
}

// 移除最后一个元素
template <typename T>
void LTvector<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Pop from empty LTvector");
    }
    --size;
}

// 下标运算符（可修改）
template <typename T>
T& LTvector<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// 下标运算符（只读）
template <typename T>
const T& LTvector<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// 获取当前大小
template <typename T>
size_t LTvector<T>::get_size() const {
    return size;
}

// 获取容量
template <typename T>
size_t LTvector<T>::get_capacity() const {
    return capacity;
}

// 判断是否为空
template <typename T>
bool LTvector<T>::empty() const {
    return size == 0;
}

// 清空所有元素
template <typename T>
void LTvector<T>::clear() {
    size = 0;
}

#endif // LTVECTOR_H
