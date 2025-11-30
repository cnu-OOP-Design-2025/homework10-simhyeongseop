#pragma once

#include <initializer_list>
#include <cstddef>


template<typename T>
class MyVector {
    T* data;            // 동적 배열을 가리키는 포인터
    size_t cap;         // 현재 할당된 배열 크기
    size_t length;      // 실제 저장된 요소 개수    
public:

    MyVector(std::initializer_list<T> init) {
        length = init.size();
        cap = length;
        data = new T[cap];
        size_t i = 0;
        for (const auto& val : init) {
            data[i++] = val;
        }
    }

    MyVector(): data(nullptr), length(0), cap(0) {}
    ~MyVector() { delete[] data; }
    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;

    void push_back(const T& val);   // Vector 마지막에 항목을 추가하는 함수 구현, 필요시 벡터 크기 증가
    void pop_back();                // Vector의 마지막 항목을 제거하는 함수 구현
    size_t size() const;            // Vecotr에 있는 항목 개수(length)를 리턴하는 함수 구현
    T& operator[](int i) ;          // [] 연산자 구현

    bool operator==(const MyVector& other) const;

    bool operator!=(const MyVector& other) const;

    bool operator<(const MyVector& other) const;

    bool operator>(const MyVector& other) const;

    bool operator<=(const MyVector& other) const;

    bool operator>=(const MyVector& other) const;


    // Vector에 대한 반복자
    class Iterator {
        T* ptr;         // 항목에 대한 포인터
    public:
        Iterator(T* p = nullptr): ptr(p) {}

        T& operator*(); // 역참조 연산자 구현 

        Iterator& operator++();   //전위 증가 연산자 구현
        Iterator& operator--();   //전위 감소 연산자 구현
        Iterator operator+(int n) const ;   // 산술 연산자 구현
        Iterator operator-(int n) const ;   // 산술 연산자 구현

        bool operator==(const Iterator& other) const ;
        bool operator!=(const Iterator& other) const ;

        int operator-(const Iterator& other) const ;
    };

    // 첫번째 항목에 대한 iterator 리턴 함수 구현
    Iterator begin() ;
    // 마지막 항목에 대한 iterator 리턴 함수 구현 
    Iterator end() ;


    // insert: 지정 위치에 요소 삽입 함수 구현
    Iterator insert(Iterator pos, const T& value);

    // erase: 지정 위치 요소 제거 함수 구현
    Iterator erase(Iterator pos);

    // clear: 모든 요소 제거 함수 구현 (size = 0 초기화)
    void clear() ;

    // at: 범위 체크 후, i번째 항목 접근 함수 구현
    T& at(size_t i); 

    // front/back
    T& front() ;    // 첫번째 항목 리턴 함수 구현
    T& back() ;     // 마지막 항목 리턴 함수 구현

    // capacity
    size_t capacity() const ;   // cap 값 리턴하는 함수 구현

    // empty
    bool empty() const ;    // 현재 vector가 empty인지 확인하는 함수 구현

};

/* 복사 생성자 */
template<typename T>
MyVector<T>::MyVector(const MyVector& other)
    : data(nullptr), cap(other.cap), length(other.length) {
        if (cap == 0) { return; }   // 원본이 0이면 복사가 필요 없음.
        else{
            data = new T[cap];
            for (size_t i = 0; i < length; ++i){
                data[i] = other.data[i];
            }
        }
}

/* 이동 생성자 */
template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept
    : data(other.data), cap(other.cap), length(other.length) {
        other.data = nullptr;
        other.cap = 0;
        other.length = 0;
}

/* 복사 대입 */
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this == &other) { return *this; }
    else {
        T* new_data = nullptr;
        if (other.cap > 0) {
            new_data = new T[other.cap];
            for (size_t i = 0; i < other.length; ++i)
                new_data[i] = other.data[i];
        } else{
            delete[] data;
            data = new_data;
            cap = other.cap;
            length = other.length;
            return *this;
        }
    }
}

/* 이동 대입 */
template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this == &other) { return *this; }
    else{
        delete[] data;

        data = other.data;
        cap = other.cap;
        length = other.length;

        other.data = nullptr;
        other.cap = 0;
        other.length = 0;
        return *this;
    }  
}

/* push_back : Vector 마지막에 항목을 추가하는 함수 구현, 필요시 벡터 크기 증가 */
template<typename T>
void MyVector<T>::push_back(const T& val) {
    if (length == cap) {
        size_t new_cap = (cap == 0) ? 1 : (cap * 2);
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < length; ++i){
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        cap = new_cap;
    }
    data[length++] = val;
}

/* pop_back : Vector의 마지막 항목을 제거하는 함수 구현 */
template<typename T>
void MyVector<T>::pop_back() {
    if (length == 0) { return; }
    else { length--; }
}

/* size : Vecotr에 있는 항목 개수(length)를 리턴하는 함수 구현 */
template<typename T>
size_t MyVector<T>::size() const {
    return length;
}

/* 인덱스로 참조 */
template<typename T>
T& MyVector<T>::operator[](int i) {
    return data[i];
}

/*  비교연산자(==,!=,<,>,<=,>=) */
template<typename T>
bool MyVector<T>::operator==(const MyVector& other) const {
    if (length != other.length) return false;
    for (size_t i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector& other) const {
    return !(*this == other);
}

template<typename T>
bool MyVector<T>::operator<(const MyVector& other) const {
    size_t min_len = (length < other.length) ? length : other.length;
    for (size_t i = 0; i < min_len; ++i) {
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
    return !(*this > other);
}

template<typename T>
bool MyVector<T>::operator>=(const MyVector& other) const {
    return !(*this < other);
}

/* 역참조 연산자 */
template<typename T>
T& MyVector<T>::Iterator::operator*() {
    return *ptr;
}

/* 전위 증가 연산자 */
template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++() {
    ++ptr;
    return *this;
}

/* 전위 감소 연산자 */
template<typename T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--() {
    --ptr;
    return *this;
}

/* 산술 연산자 + */
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator+(int n) const {
    return Iterator(ptr + n);
}

/* 산술 연산자 - */
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator-(int n) const {
    return Iterator(ptr - n);
}

/* ptr 같은 위치 */
template<typename T>
bool MyVector<T>::Iterator::operator==(const Iterator& other) const {
    return ptr == other.ptr;
}

/* ptr 다른 위치 */
template<typename T>
bool MyVector<T>::Iterator::operator!=(const Iterator& other) const {
    return ptr != other.ptr;
}

/* 두 iterator 간에 거리 계산 */
template<typename T>
int MyVector<T>::Iterator::operator-(const Iterator& other) const {
    return static_cast<int>(ptr - other.ptr);
}

/* begin : 첫번째 항목에 대한 iterator 리턴 */
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
    return Iterator(data);
}

/* end : 마지막 항목에 대한 iterator 리턴 */
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::end() {
    if (data == nullptr) return Iterator(nullptr);
    return Iterator(data + length);
}

/* insert : 지정 위치에 요소 삽입 */
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::insert(Iterator pos, const T& value) {
    Iterator start = begin();
    Iterator finish = end();
    size_t idx = 0;
    if (pos == finish) {
        idx = length;
    } else {
        idx = static_cast<size_t>(pos - start);
        if (idx > length) idx = length;
    }

    if (length == cap) {
        size_t new_cap = (cap == 0) ? 1 : cap * 2;
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < length; ++i)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
        cap = new_cap;
    }
    if (cap == 0) {
        cap = 1;
        data = new T[cap];
    }

    for (size_t i = length; i > idx; --i)
        data[i] = data[i - 1];
    data[idx] = value;
    ++length;
    return Iterator(data + idx);
}

/* erase : 지정 위치에 요소 삭제 */
template<typename T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator pos) {
    if (length == 0) { return end(); }
    Iterator start = begin();
    size_t idx = static_cast<size_t>(pos - start);
    if (idx >= length){ return end(); }
    for (size_t i = idx; i + 1 < length; ++i){
        data[i] = data[i + 1];
    }
    length--;
    return Iterator(data + idx);
}

/* clear : 모든 요소 제거 (size = 0 초기화) */
template<typename T>
void MyVector<T>::clear() {
    length = 0;
}

/* at : 범위 체크 후, i번째 항목 접근 */
template<typename T>
T& MyVector<T>::at(size_t i) {
    if (i >= length) {
        throw "인덱스 에러 발생";
    }
    return data[i];
}

/* front : 첫번째 항목 접근 */
template<typename T>
T& MyVector<T>::front() {
    if (length == 0) {
        throw "MyVector::front - empty vector";
    }
    return data[0];
}

/* back : 마지막 항목 접근 */
template<typename T>
T& MyVector<T>::back() {
    if (length == 0) {
        throw "MyVector::back - empty vector";
    }
    return data[length - 1];
}

/* capacity : cap 값 리턴 */
template<typename T>
size_t MyVector<T>::capacity() const {
    return cap;
}

/* empty : 현재 vector가 empty인지 확인 */
template<typename T>
bool MyVector<T>::empty() const {
    return length == 0;
}
