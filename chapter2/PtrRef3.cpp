#include <iostream>

void fun(void* param) {
    std::cout << (param + 1) << '\n';//result make error
}

int main() {
    int x = 52;
    int* p = &x;
    *p;//dereference
    std::cout << p << '\n';
    p = p - 1;//decrease address with type size. such as int, p's address - 4
    std::cout << p << '\n';
    p = p + 1;//increase address with type size. such as int, p's address + 4
    std::cout << p << '\n';
    int* q = &x;
    std::cout << (p == q) << '\n';

    int y = 42;
    int* pt1 = &y;
    char* pt2 = nullptr;

    std::cout << pt1 << '\n';
    std::cout << (pt1 + 1) << '\n';
    fun(pt1);//result make error
//    fun(pt2);
}

