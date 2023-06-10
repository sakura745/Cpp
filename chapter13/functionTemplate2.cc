#include <iostream>
#include "header.h"

template <typename T>
void fun(T x){
    std::cout << x << std::endl;
}

//fun3的显式实例化声明，可以减轻编译器和链接器的负担，提升编译速度
extern template
void fun3/*隐式提供模板形参*/(int x);
//void fun3<int>/*显式提供模板形参*/(int x);

template
void fun4(double x);
//对于fun4，在functionTemplate2和source中都有定义，还可以通过，没有报重定义的错。标准规定的编译器对这种可以不报错。
//编译器可以不报错的意思就是也可以报错。所以多重定义不是个好的编程习惯。
//ChatGPT :
//函数模板的显式实例化定义可以出现在两个编译单元中而不报重定义错误是因为在C++标准中规定，函数模板的显式实例化定义是不会
// 被实例化的，只有当函数模板被使用（或者说被调用）时才会被实例化成相应的函数。
//因此，如果在两个编译单元中都出现了函数模板的显式实例化定义，只有当这个函数模板在两个编译单元中都被使用时
// 才会被实例化成相应的函数，否则编译器会认为这只是一个定义，而不会实际生成代码。这就避免了重定义错误的发生。

template <typename T>
void fun(T* x){
    std::cout << x << std::endl;
}

template
void fun<int*>(int* x);//它是template <typename T> void fun(T x)的显式实例化定义，因为模板中和函数中的形参都是T -> int*

template
void fun/*如果把显式转换变为隐式转换*/(int* x);//它是template <typename T> void fun(T* x)的显式实例化定义。选择特殊的进行推导
//现在它是处于template <typename T> void fun(T x) 和 template <typename T> void fun(T* x) 的下面
//改为处于template <typename T> void fun(T x) 的下面 ，则实例化为template <typename T> void fun(T x) .编译器从上往下编译




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