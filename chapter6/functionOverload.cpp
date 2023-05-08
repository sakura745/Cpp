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


int main() {
    std::cout << fun(3) << std::endl;
    std::cout << fun(3.5) << std::endl;
}

