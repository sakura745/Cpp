#ifndef PROJECT_HEADER_H
#define PROJECT_HEADER_H
#include "iostream"
//fun1的模板定义
template <typename T>
void fun1(T x) {
    std::cout << x << std::endl;
}

//fun1显式实例化定义
template
void fun1<int>/*显式提供模板实参*/(int x);


//fun2的模板定义
template <typename T>
void fun2(T x) {
    std::cout << x << std::endl;
}

//fun2显式实例化定义
template
void fun2/*隐式提供模板实参*/(int x);


//fun3的模板定义
template <typename T>
void fun3(T x) {
    std::cout << "Template fun3 is called.\n";
}


template <typename T>
void fun4(T x) {
    std::cout << x << std::endl;
}
#endif //PROJECT_HEADER_H
