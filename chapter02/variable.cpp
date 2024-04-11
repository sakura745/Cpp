#include <iostream>
#include "auxilsource.cpp"

extern/*使用auxilsource.cpp 中的g_x定义*/ int g_x;//declaration
//extern int g_x = 10;//illegal : 则意味着从声明转为定义，报重定义的错误

int main() {
    int x;//default initialized value is anything

    std::cout << g_x << std::endl;//全局变量 缺省初始化为0
    std::cout << x << std::endl;//局部变量 初始化值随机
    //是因为函数体内的变量不知道会用多少次，如果初始化为一个定值，每次调用带变量都会消耗cpu。但全局变量生命周期和程序一样
    //因此可以给全局变量初始化为0，构造成本较低。

    int y = /*在初始化时，使用赋值操作符，相当于拷贝初始化*/ 10;//copy initialization
    int z(10);//directly initialization1
    int w{10};//directly initialization2
}

