#include <iostream>
constexpr int x = 3;

//可以在编译期或运行期调用，但定义是在编译器constexpr，区分编译还是运行在于函数整体是否可以在编译还是运行执行，
//用complier explorer查看
constexpr int fun2() {
    return 3;
}
constexpr int fun(int y) {
    return y + 1;
}

int main() {
    constexpr int y = fun2();//fun2变成编译期使用
    int a;
    std::cin >> a;
    int b = fun(a);//fun变成运行期使用
    return b;
}