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

template<typename T>
void MyVector<T>::ensure_capacity(size_t minCapacity) {
    if (cap >= minCapacity) {
        return;
    }
    size_t newCap = cap ? cap : 1;
    while (newCap < minCapacity) {
        newCap *= 2;
    }
    T* newData = new T[newCap];
    for (size_t i = 0; i < length; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    cap = newCap;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other)
    : data(nullptr), cap(other.cap), length(other.length) {
    if (cap > 0) {
        data = new T[cap];
        for (size_t i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this == &other) {
        return *this;
    }

    T* newData = other.cap ? new T[other.cap] : nullptr;
    for (size_t i = 0; i < other.length; ++i) {
        newData[i] = other.data[i];
    }

    delete[] data;
    data = newData;
    cap = other.cap;
    length = other.length;
    return *this;
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept
    : data(other.data), cap(other.cap), length(other.length) {
    other.data = nullptr;
    other.cap = 0;
    other.length = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] data;
    data = other.data;
    cap = other.cap;
    length = other.length;

    other.data = nullptr;
    other.cap = 0;
    other.length = 0;
    return *this;
}

template<typename T>
bool MyVector<T>::operator==(const MyVector& other) const {
    if (length != other.length) {
        return false;
    }
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector& other) const {
    return !(*this == other);
}

template<typename T>
bool MyVector<T>::operator<(const MyVector& other) const {
    size_t minLen = length < other.length ? length : other.length;
    for (size_t i = 0; i < minLen; ++i) {
        if (data[i] < other.data[i]) {
            return true;
        }
        if (data[i] > other.data[i]) {
            return false;
        }
    }
    return length < other.length;
}

template<typename T>
bool MyVector<T>::operator>(const MyVector& other) const {
    return other < *this;
}

template<typename T>
bool MyVector<T>::operator<=(const MyVector& other) const {
    return !(*this > other);
}

template<typename T>
bool MyVector<T>::operator>=(const MyVector& other) const {
    return !(*this < other);
}

template<typename T>
T& MyVector<T>::Iterator::operator*() {
    if (!ptr) {
        throw std::out_of_range("invalid iterator dereference");
    }
    return *ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator==(const Iterator& other) const {
    return ptr == other.ptr;
}

template<typename T>
bool MyVector<T>::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}

template<typename T>
int MyVector<T>::Iterator::operator-(const Iterator& other) const {
    if (!ptr && !other.ptr) {
        return 0;
    }
    if (!ptr || !other.ptr) {
        throw std::out_of_range("iterators are incompatible");
    }
    return static_cast<int>(ptr - other.ptr);
}