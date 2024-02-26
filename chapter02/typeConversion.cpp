#include <iostream>

int main() {
    float x = 1.3;//type from double to float
    float y = 1.3f;//type from float to float

    long double z = 1.3;//type promotion
    int w = 'c';//type promotion

    unsigned a = -1;
    std::cout << a << '\n';//隐式转换后溢出，输出为unsigned最大值

    bool b = 3;
    int c = b;
    std::cout << b << '\n';
    std::cout << c << '\n';

    if (4)// int to bool
        {}

    int q = -1;
    unsigned p = 3;
    std::cout << (q < p) << std::endl;
    //输出0，因为无符号和有符号比较时，有符号会被隐式转换为无符号，-1 -> std::numeric_limits<unsigned>::max()

}