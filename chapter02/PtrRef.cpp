#include <iostream>
int* ptr;//default initialization pointer, ptr is 0
int main() {
    int x = 42;
    int y = 56;
    int* p1 = &x;
    p1 = &y;
    char z = 'c';
    char* p2 = &z;
    std::cout << sizeof(x) << '\n';
    std::cout << sizeof(z) << '\n';
    std::cout << sizeof(p1) << '\n';
    std::cout << sizeof(p2) << '\n';
    std::cout << &x << '\n';//get address
    std::cout << *p1 << '\n';//Dereference

    std::cout << *ptr << '\n';//address is 0 cannot dereference. It will be wrong!

}

