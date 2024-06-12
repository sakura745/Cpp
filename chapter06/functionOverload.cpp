#include <iostream>

int fun(int x) {
    return x + 1;
}
double fun(double x) {
    return x + 1;
}

//int fun(int x) {
//    return x + 1;
//}
//double fun(int x) {
//    return x + 1;
//}
//这两个函数只有返回值类型不一样，但不属于重载。不能基于返回类型进行重载

void foo(int x);
void foo(double y);

int main() {
    std::cout << fun(3) << std::endl;
    std::cout << fun(3.5) << std::endl;

    foo(42);      // 完美匹配，调用 foo(int)
    foo(3.14);    // 完美匹配，调用 foo(double)
    foo('A');     // 平凡转换，将字符 'A' 转换为 int，调用 foo(int)
}

