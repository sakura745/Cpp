#include <iostream>
#include <type_traits>
int main() {
    signed char x = 3;            //0000 0011
    std::cout << ~x << std::endl; //1111 1100
    signed char y = 5;            //0000 0101
    std::cout <<  (x & y) << std::endl;//0000 0001
    std::cout <<  (x | y) << std::endl;//0000 0111
    std::cout <<  (x ^ y) << std::endl;//0000 0110

    auto z = ~x;//z type is int, integral promotion.
    std::cout << std::is_same_v<decltype(z), int> << std::endl;

    std::cout << (x << 1) << std::endl;//0000 0110
    std::cout << (x >> 1) << std::endl;//0000 0001
    std::cout << (~x << 1) << std::endl;//1111 1000
    std::cout << (~x >> 1) << std::endl;//1111 1110

    unsigned char w = 0xff;//1111 1111 -> 255
    auto w2 = ~w;
    //int:w 0000..00 1111 1111 -> 255
    //w2:~w 1111..11 0000 0000
    std::cout << w2 << std::endl;

    signed char w3 = 0xff;//1111 1111 -> -1
    auto w4 = ~w3;
    //int:w 1111..11 1111 1111 --> -1
    //w2:~w 0000..00 0000 0000
    std::cout << w4 << std::endl;

    int a = 0x80000000;
    std::cout << a << std::endl;
    std::cout << (a >> 1) << std::endl;
    std::cout << (a << 1) << std::endl;

    unsigned int b = 0x80000000;
    std::cout << b << std::endl;
    std::cout << (b >> 1) << std::endl;
    std::cout << (b << 1) << std::endl;

    int c = -1;
    std::cout << c << std::endl;
    std::cout << (c >> 1) << std::endl;
    std::cout << (c << 1) << std::endl;


}