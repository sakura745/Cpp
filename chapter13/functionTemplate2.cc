#include <iostream>
#include "header.h"

template <typename T>
void fun(T x){
    std::cout << x << std::endl;
}

//fun3的显式实例化声明
extern template
void fun3(int x);

int main() {
    fun<int>(3);//显式实例化的同时，也调用了函数

    //构造链接库：是通过给用户调用接口，不暴露出函数内部的实现。通过模板的定义，暴露了函数的实现。一般通过模板的声明，不能
    //调用函数。但是可以通过 **显式实例化定义** ，引入实例化，不调用函数。
    //提供一个动态库，库中包含了模板的定义以及相应实例化之后的结果，提供给用户是模板的声明。当用户使用声明时，系统可以尝试
    //在动态库中找到实例化的结果，就能完成链接，程序就能得到编译。
    fun1<int>(4);//直接调用fun1()函数，不用再实例化了（header.h已经有了实例化的定义）
    fun2<int>(4);//直接调用fun2()函数，不用再实例化了（header.h已经有了实例化的定义）

    fun3<int>(4);//声明是在本翻译单元中，显式实例化定义是在source翻译单元中，模板是在header.h中给出


}