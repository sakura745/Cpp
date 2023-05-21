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
    std::cout << "---------" << std::endl;

    std::cout << sizeof(float) << std::endl;
    std::cout << sizeof(double) << std::endl;
    std::cout << sizeof(long double) << std::endl;
    std::cout << std::numeric_limits<float>::max() << std::endl;
    std::cout << std::numeric_limits<double>::max() << std::endl;
    std::cout << "---------" << std::endl;

    //char对应到ASCII
    char ch = '\x4d';// \x表示十六进制 4d对应十进制为76，\x4d表示ascii上第76个字符
    char ch2 = '\103';// \表示八进制

    char ch3 = 103;// 表示十进制。注意没有 '' 和转义符号\"。八进制和十六进制有转义符号是为了防止计算机误认为是字符
    //也从侧面说明了char的底层。内存存储数字，类型为char时，会自动转化为ascii上数字对应的字符。

    char ch3_2 = 127;//ASCII 有128位，从0-127。因此char最大为127 输出超过127就相当于补码循环回来了。
    char ch3_3 = -129;//char 有符号位 范围-128~217。-129溢出了
    char ch4 = '103';//表示字符为1 0 3，而不是十进制。ch4输出最后一位3。整数不能用字符输出


    int x = 3.14_ddd;
    std::cout << x << (char)10/*ascii上10对应的为'\n'*/;
}

