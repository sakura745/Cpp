#include <iostream>

//自定义类型，如物理单位等
int operator "" _ddd(long double x) {
    return (int)x * 2;
}


int main() {
    char a;//1 byte ASCII
    wchar_t b;//2 bytes
    char16_t c;//2 bytes
    char32_t d;//4 bytes
    std::cout << sizeof(short) << std::endl;
    std::cout << sizeof(int) << std::endl;
    std::cout << sizeof(long) << std::endl;
    std::cout << sizeof(long long) << std::endl;

    std::cout << sizeof(float) << std::endl;
    std::cout << sizeof(double) << std::endl;
    std::cout << sizeof(long double) << std::endl;
    std::cout << std::numeric_limits<double>::max() << std::endl;
    char ch = '\x4d';//对应到ASCII中

    int x = 3.14_ddd;
    std::cout << x << '\n';
}

