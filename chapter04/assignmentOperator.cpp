#include <iostream>

int main() {
    int x = 3;//初始化，不是赋值
    x = 5;//赋值

    const int y = 4;
    //y = 3;//左操作数不可修改

    int a, b;
    a = b = 3;//先算b=3,再算a=b。右结合

    short c = 0x80000;
    std::cout << c << std::endl;
//    short d = { 0x8000000 };// 直接报错error

    int d = 3;
    short e;
//    e = { d };//同样报错，因为d可能溢出

    constexpr int g = 3;
    short h;
    h = { g };//编译器常量constexpr，编辑阶段已知

    //q p交换
    int q = 2;
    int p = 3;
    //q = q ^ p;
    //q = q ^ p;
    //p = q ^ p;等价
    q ^= p ^= q ^= p;//没提升速度，但节约了空间
    std::cout << q << '\n';
    std::cout << p << '\n';
}