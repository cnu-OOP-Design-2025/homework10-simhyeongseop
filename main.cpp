#include <iostream>
#include "MyVector.h"

void test1() {
    MyVector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);

    std::cout << "v.size(): " << v.size() << "\n"; // 3
    std::cout << "v[0]: " << v[0] << "\n";         // 0
    std::cout << "v[1]: " << v[1] << "\n";         // 1
    std::cout << "v[2]: " << v[2] << "\n";         // 2

    MyVector<int>::Iterator it = v.begin();
    std::cout << "*it: " << *it << "\n";           // 0
    ++it;
    std::cout << "*it after ++: " << *it << "\n";  // 1

    std::cout << "Range-based for: ";
    for (auto& x : v)
        std::cout << x << " ";                     // 0 1 2
    std::cout << "\n";
}

void test2() {
    MyVector<int> a = {1,2,3};
    MyVector<int> b = {1,2,3};
    MyVector<int> c = {1,2,4};

    std::cout << "a == b: " << (a == b) << "\n";   // 1
    std::cout << "a != b: " << (a != b) << "\n";   // 0
    std::cout << "a != c: " << (a != c) << "\n";   // 1

    std::cout << "a < c: " << (a < c) << "\n";     // 1
    std::cout << "c > a: " << (c > a) << "\n";     // 1
    std::cout << "a <= b: " << (a <= b) << "\n";   // 1
    std::cout << "c >= a: " << (c >= a) << "\n";   // 1

    MyVector<int> d;
    d.push_back(1); d.push_back(2);
    std::cout << "d < a: " << (d < a) << "\n";     // 1
    std::cout << "a > d: " << (a > d) << "\n";     // 1

    MyVector<int> empty;
    std::cout << "empty < a: " << (empty < a) << "\n"; // 1
    std::cout << "a > empty: " << (a > empty) << "\n"; // 1
    std::cout << "empty == empty: " << (empty == empty) << "\n"; // 1

    std::cout << "a == a: " << (a == a) << "\n";   // 1
    std::cout << "a < a: " << (a < a) << "\n";     // 0
    std::cout << "a > a: " << (a > a) << "\n";     // 0
}


void test3() {
    MyVector<int> v = {10, 20, 30};
    std::cout << "Initial: ";
    for (auto& x : v) 
        std::cout << x << " "; // 10 20 30
    std::cout << "\n";

    // push_back & pop_back
    v.push_back(40);
    std::cout << "After push_back: ";
    for (auto& x : v) 
        std::cout << x << " "; // 10 20 30 40
    std::cout << "\n";

    v.pop_back();
    std::cout << "After pop_back: ";
    for (auto& x : v) 
        std::cout << x << " "; // 10 20 30
    std::cout << "\n";

    // insert
    v.insert(v.begin() + 1, 15);
    std::cout << "After insert at pos 1: ";
    for (auto& x : v) 
        std::cout << x << " "; // 10 15 20 30
    std::cout << "\n";

    // erase
    v.erase(v.begin() + 2);
    std::cout << "After erase pos 2: ";
    for (auto& x : v) 
        std::cout << x << " "; // 10 15 30
    std::cout << "\n";

    // at, front, back
    std::cout << "at(1): " << v.at(1) << "\n";  // 15
    std::cout << "front: " << v.front() << "\n";   // 10
    std::cout << "back: " << v.back() << "\n";  //30

    // clear
    v.clear();
    std::cout << "After clear, size: " << v.size() << "\n"; // 0
    std::cout << "Empty: " << v.empty() << "\n"; // 0


}

int main() {
    std::cout << "[TEST1]\n";
    test1();
    std::cout << "\n[TEST2]\n";
    test2();
    std::cout << "\n[TEST3]\n";
    test3();
    
    return 0;
}