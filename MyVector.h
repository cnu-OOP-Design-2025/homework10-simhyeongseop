#pragma once

#include <initializer_list>
#include <cstddef>
#include <stdexcept>

//과제 확인
template<typename T>
class MyVector {
    T* data;
    size_t cap;
    size_t length;

    void ensure_capacity(size_t minCapacity);
public:
    MyVector(std::initializer_list<T> init)
        : data(nullptr), cap(init.size()), length(init.size()) {
        if (cap > 0) {
            data = new T[cap];
            size_t i = 0;
            for (const auto& val : init) {
                data[i++] = val;
            }
        }
    }

    MyVector() : data(nullptr), cap(0), length(0) {}
    ~MyVector() { delete[] data; }

    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;

    void push_back(const T& val) {
        ensure_capacity(length + 1);
        data[length++] = val;
    }

    void pop_back() {
        if (length > 0) {
            --length;
        }
    }

    size_t size() const { return length; }

    T& operator[](int i) { return data[i]; }

    bool operator==(const MyVector& other) const;
    bool operator!=(const MyVector& other) const;
    bool operator<(const MyVector& other) const;
    bool operator>(const MyVector& other) const;
    bool operator<=(const MyVector& other) const;
    bool operator>=(const MyVector& other) const;

    class Iterator {
        T* ptr;
    public:
        Iterator(T* p = nullptr) : ptr(p) {}

        T& operator*();
        Iterator& operator++() {
            ++ptr;
            return *this;
        }
        Iterator& operator--() {
            --ptr;
            return *this;
        }
        Iterator operator+(int n) const {
            return Iterator(ptr + n);
        }
        Iterator operator-(int n) const {
            return Iterator(ptr - n);
        }

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

        int operator-(const Iterator& other) const;
    };

    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data ? data + length : nullptr);
    }

    Iterator insert(Iterator pos, const T& value) {
        int offset = pos - begin();
        if (offset < 0) {
            offset = 0;
        }
        size_t index = static_cast<size_t>(offset);
        if (index > length) {
            index = length;
        }

        ensure_capacity(length + 1);
        for (size_t i = length; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++length;
        return Iterator(data + index);
    }

    Iterator erase(Iterator pos) {
        if (length == 0) {
            return end();
        }

        int offset = pos - begin();
        if (offset < 0 || static_cast<size_t>(offset) >= length) {
            return end();
        }

        size_t index = static_cast<size_t>(offset);
        for (size_t i = index; i + 1 < length; ++i) {
            data[i] = data[i + 1];
        }
        --length;
        return Iterator(data + index);
    }

    void clear() {
        length = 0;
    }

    T& at(size_t i) {
        if (i >= length) {
            throw std::out_of_range("index out of range");
        }
        return data[i];
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("vector is empty");
        }
        return data[0];
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("vector is empty");
        }
        return data[length - 1];
    }

    size_t capacity() const { return cap; }

    bool empty() const { return length == 0; }
};