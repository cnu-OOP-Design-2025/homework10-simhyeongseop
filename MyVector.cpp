#include "MyVector.h"
#include <stdexcept>

// 내부 capacity 확보
template<typename T>
void MyVector<T>::ensure_capacity(size_t minCapacity) {
    if (cap >= minCapacity) return;

    size_t newCap = (cap == 0 ? 1 : cap * 2);
    while (newCap < minCapacity) newCap *= 2;

    T* newData = new T[newCap];
    for (size_t i = 0; i < length; i++) newData[i] = data[i];

    delete[] data;
    data = newData;
    cap = newCap;
}

// ----------- 기본 연산 -----------

template<typename T>
void MyVector<T>::push_back(const T& val) {
    ensure_capacity(length + 1);
    data[length++] = val;
}

template<typename T>
void MyVector<T>::pop_back() {
    if (length == 0) return;
    length--;
}

template<typename T>
size_t MyVector<T>::size() const {
    return length;
}

template<typename T>
T& MyVector<T>::operator[](int i) {
    return data[i];
}

// ----------- 비교 연산자 (lexicographical) -----------

template<typename T>
bool MyVector<T>::operator==(const MyVector& other) const {
    if (length != other.length) return false;
    for (size_t i = 0; i < length; i++)
        if (data[i] != other.data[i]) return false;
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector& other) const {
    return !(*this == other);
}

template<typename T>
bool MyVector<T>::operator<(const MyVector& other) const {
    size_t n = (length < other.length ? length : other.length);
    for (size_t i = 0; i < n; i++) {
        if (data[i] < other.data[i]) return true;
        if (data[i] > other.data[i]) return false;
    }
    return length < other.length;
}

template<typename T>
bool MyVector<T>::operator>(const MyVector& other) const {
    return other < *this;
}

template<typename T>
bool MyVector<T>::operator<=(const MyVector& other) const {
    return !(other < *this);
}

template<typename T>
bool MyVector<T>::operator>=(const MyVector& other) const {
    return !(*this < other);
}

// ----------- Iterator 구현 -----------

template<typename T>
T& MyVector<T>::Iterator::operator*() {
    return *ptr;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++() {
    ptr++;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--() {
    ptr--;
    return *this;
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator+(int n) const {
    return Iterator(ptr + n);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator-(int n) const {
    return Iterator(ptr - n);
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
    return (int)(ptr - other.ptr);
}

// -------- begin / end --------

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
    return Iterator(data);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end() {
    return Iterator(data + length);
}

// -------- insert / erase --------

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::insert(Iterator pos, const T& value) {
    size_t index = pos - begin();
    ensure_capacity(length + 1);

    for (size_t i = length; i > index; i--)
        data[i] = data[i - 1];

    data[index] = value;
    length++;

    return Iterator(data + index);
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator pos) {
    size_t index = pos - begin();
    if (index >= length) return end();

    for (size_t i = index; i < length - 1; i++)
        data[i] = data[i + 1];

    length--;
    return Iterator(data + index);
}

// -------- clear / at / front / back / capacity / empty --------

template<typename T>
void MyVector<T>::clear() {
    length = 0;
}

template<typename T>
T& MyVector<T>::at(size_t i) {
    if (i >= length) throw std::out_of_range("at() index error");
    return data[i];
}

template<typename T>
T& MyVector<T>::front() {
    return data[0];
}

template<typename T>
T& MyVector<T>::back() {
    return data[length - 1];
}

template<typename T>
size_t MyVector<T>::capacity() const {
    return cap;
}

template<typename T>
bool MyVector<T>::empty() const {
    return length == 0;
}

// 명시적 템플릿 인스턴스화
template class MyVector<int>;
