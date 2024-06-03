#include <iostream>
#include <type_traits>
int main() {
    int aaa = 0b1111;//二进制表示
    signed char x = 3;           		 //0000 0011
    std::cout << ~x << std::endl;		 //1111 1100
    signed char y = 5;           		 //0000 0101
    std::cout <<  (x & y) << std::endl;  //0000 0001
    std::cout <<  (x | y) << std::endl;  //0000 0111
    std::cout <<  (x ^/*按位亦或*/ y) << std::endl;  //0000 0110
    std::cout << "----------" << std::endl;

    auto z = ~x;//z type is int, integral promotion.
    std::cout << std::is_same_v<decltype(z), int> << std::endl;
    std::cout << "----------" << std::endl;

    std::cout << (x << 1) << std::endl; //0000 0110
    std::cout << (x >> 1) << std::endl; //0000 0001
    std::cout << (~x << 1) << std::endl;//1111 1000
    std::cout << (~x >> 1) << std::endl;//1111 1110
    std::cout << "----------" << std::endl;

    signed char x1 = -3;
    //x1:1000 0011,但在计算机中是补码表示 x1:1111 1101
    //~x1:0000 0010
    std::cout << ~x1 << std::endl;//~x1是2
    std::cout << (x1 << 1) << std::endl;//x1:1111 1101,移动后1111 1010是补码，原码为1000 0110 为-6
    std::cout << (x1 >> 1) << std::endl;//                   1111 1110是补码，原码为1000 0010 为-2
    std::cout << (~x1 << 1) << std::endl;//                                         0000 0100 为4
    std::cout << (~x1 >> 1) << std::endl;//                                         0000 0001 为1
    //所以负数右移注意写为补码。左移直接乘2就行
    std::cout << "----------" << std::endl;

    unsigned char w = 0xff;//1111 1111 -> 255
    auto w2 = ~w;
    //int:w 0000..00 1111 1111 -> 255
    //w2:~w 1111..11 0000 0000是补码 integral promotion
    //原码  1000..01 0000 0000：-256
    std::cout << w2 << std::endl;
    std::cout << "----------" << std::endl;

    //-128~127，0xff溢出。1111 1111最高位为符号位
    // 故1111 1111的原码形式为 1000 0001为-1
    signed char w3 = 0xff;
    auto w4 = ~w3;
    std::cout << w3 << std::endl;//输出不是-1，因为char对应ascii
    //c++insight:    auto w4 = ~w3;==> int w4 = ~static_cast<int>(w3);先提升再补反
    //w4's type is int,(integral promotion)
    //w3(int)原码:  1000 .... 0000 0001
    //w3 补码    :  1111 .... 1111 1111
    //w4(~w3)    :  0000 .... 0000 0000
    std::cout << w4 << std::endl;
    std::cout << "----------" << std::endl;
    //以上看出是0xff->1111 1111 integral promotion： 1111 .... 1111 1111
    //计算机(以补码的角度分析)是这么运行的


    int a = 0x80000000;//对于int（有符号）占4字符来说，正好溢出。最大为0x7fffffff
    std::cout << a - 1 << std::endl;//最大为0x7fffffff
    std::cout << a << std::endl;
    std::cout << (a >> 1) << std::endl;
    std::cout << (a << 1) << std::endl;
    std::cout << "----------" << std::endl;

    //无溢出
    unsigned int b = 0x80000000;
    std::cout << b << std::endl;
    std::cout << (b >> 1) << std::endl;
    std::cout << (b << 1) << std::endl;
    std::cout << "----------" << std::endl;

    int c = -1;
    std::cout << c << std::endl;
    std::cout << (c >> 1) << std::endl;
    std::cout << (c << 1) << std::endl;


}