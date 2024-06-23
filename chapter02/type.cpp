#include <iostream>
#include <limits>

struct Str {
    char b;
    int x;
};
int main() {

    int x = 10;
    char y = 'a';

    std::cout << "sizeof:" << std::endl;
    std::cout << sizeof(x) << ' ' << sizeof(int) << '\n';
    std::cout << sizeof(y) << ' ' << sizeof(char) << '\n';
    std::cout << "---------" << std::endl;

    std::cout << "min max:" << std::endl;
    std::cout << std::numeric_limits<int>::min() << " " << std::numeric_limits<int>::max() << std::endl;
    std::cout << std::numeric_limits<unsigned int>::min() << " " << std::numeric_limits<unsigned int>::max() << std::endl;
    std::cout << "---------" << std::endl;

    //最大值 +1 会溢出变成最小值 : 是因为以二进制补码形式存储，+ 1变成一个循环
    unsigned int z = std::numeric_limits<unsigned int>::max();
    z = z + 1;
    std::cout << z << std::endl;
    int w = std::numeric_limits<int>::max();
    w = w + 1;
    std::cout << w << std::endl;
    std::cout << "---------" << std::endl;

    std::cout << "alignof:" << std::endl;
    std::cout << alignof(int) << std::endl;
    std::cout << alignof(char) << std::endl;
    std::cout << alignof(Str) << " " << sizeof(Str) << std::endl;

    //对Str无法进行加减乘除，因为没有构造+-*/的重载运算符
}

