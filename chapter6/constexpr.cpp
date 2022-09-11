#include <iostream>

constexpr int x = 3;

constexpr int fun2() {
    return 3;
}//可以在编译期或运行期调用，区分编译还是运行在于函数整体是否可以在编译还是运行执行

int main() {
    constexpr int y = fun2();
    return y;
}