#include <iostream>
#include "header.h"

extern "C"//告诉外部链接，Add函数为C形式，设置C语言接口。（C语言不接受函数重载）
int Add(int x, int y) {//define
    return x + y;
}

int Sub(int x, int y) {
    return x - y;
}
int main() {
    int z = Add(2, 3);
    std::cout << z << std::endl;
    z = Sub(2, 3);
    std::cout << z << std::endl;
}
/*
 * 栈帧(Stack Frame)结构:
 * stack是内存 frame是函数
 * 先调用main，main函数入栈，
 * 再调用Add，Add函数入栈（压在main函数上）
 * Add函数返回给z到main函数中，Add函数出栈（从main函数上拿走）
 * 调用Sub函数，Sub函数入栈（压在main函数上）
 * Aub函数返回给z到main函数中，Sub函数出栈（从main函数上拿走）
 * 返回return 0
 * 实际上cout也是一个函数
 *
 * 帧(Frame)结构:
 * 先是实参入栈，如Add函数的2,3
 * 再是执行函数的返回地址，如13行执行函数的返回地址入栈
 * 然后再是函数内的局部变量入栈，Add函数没有局部变量
 */


