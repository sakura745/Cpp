#include <iostream>
#include "header.h"
#include <type_traits>

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


//模板的完全特化：对int的特化
template <>
void fun/*隐式推导*/(int x){
    std::cout << x << std::endl;
}
template <>
void fun<double>/*显示给定*/(double x){
    std::cout << x << std::endl;
}


template<typename T>
void fun5(T x) {
    std::cout << "Fun5 is called.\n";
}
template<typename T>
void fun5(T* x) {
    std::cout << "Fun5 overload * is called.\n";
}
template<>
void fun5(int* x) {
    std::cout << "Fun5 template Specialization is called.\n";
}

template<typename T>
void fun6(T x) {
    std::cout << "Fun6 is called.\n";
}
template<typename T>
void fun6(T* x) {
    std::cout << "Fun6 overload * is called.\n";
}
template<>
void fun6<int*>(int* x) {
    std::cout << "Fun6 template Specialization is called.\n";
}

template<typename T>
void fun7(T x) {
    std::cout << "Fun7 is called.\n";
}
template<>
void fun7(int* x) {
    std::cout << "Fun7 template Specialization is called.\n";
}
template<typename T>
void fun7(T* x) {
    std::cout << "Fun7 overload * is called.\n";
}

template<typename T>
void fun8(T x) {
    std::cout << "Fun8 is called.\n";
}
//选择重载代替特化
void fun8(int* x) {
    std::cout << "Normal fun8  is called.\n";
}
template<typename T>
void fun8(T* x) {
    std::cout << "Fun8 overload * is called.\n";
}



template <typename Res, typename T1>
Res fun9(T1 x) {
    return Res{};
}
//函数返回类型，重载不起作用
template<>
double fun9(int x) {
    return double{};
}

//无法重载，可以使用if constexpr解决。将模板修改为如下，从而避免使用函数模板特化
template <typename Res, typename T1>
Res fun10(T1 x) {
    if constexpr (std::is_same_v<Res, int>) {
        std::cout << "If constexpr int.\n";
    } else {
        std::cout << "If constexpr else.\n";
    }
    return Res{};
}


template <typename Res, typename T1>
Res fun11(T1 x, const Res&/*假参数*/) {
    std::cout << "No-op no-int arguments.\n";
    return Res{};
}

template <typename T1>
int fun11(T1 x, const int&/*假参数*/) {
    std::cout << "No-op int arguments.\n";
    return int{};
}

//illegal
/*template<typename T>
int fun10<int, T>(T x) {}*///error : Function template partial specialization is not allowed.只对Res进行特化


//c20。通过auto简化函数模板
void fun12(auto x) {
    std::cout << "c20.\n";
}

int main() {
    fun<int>(3);//显式实例化的同时，也调用了函数

    //构造链接库：是通过给用户调用接口，不暴露出函数内部的实现。通过模板的定义，暴露了函数的实现。一般通过模板的声明，不能
    //调用函数。但是可以通过 **显式实例化定义** ，引入实例化，不调用函数。
    //提供一个动态库，库中包含了模板的定义以及相应实例化之后的结果，提供给用户是模板的声明。当用户使用声明时，系统可以尝试
    //在动态库中找到实例化的结果，就能完成链接，程序就能得到编译。
    fun1<int>(4);//直接调用fun1()函数，不用再实例化了（header.h已经有了实例化的定义）
    fun2<int>(4);//直接调用fun2()函数，不用再实例化了（header.h已经有了实例化的定义）

    fun3<int>(4);//声明是在本翻译单元中，显式实例化定义是在source翻译单元中，模板是在header.h中给出

    int x = 77;
    fun5(&x);//输出：Fun5 template Specialization is called. 因为模板特化不会引入新的名称，所以在Name Lookup时，只会查找
    // fun5和其重载函数的名称，不会查找特化名称。编译器会选择T* （更特殊的版本）。然后再进行Function Template Specialization
    //发现T*的模板特化，因此最后输出Fun5 template Specialization is called.
    //特化隐式给定类型为<int>。是T* 对于int* 的特化


    //特化显式给定类型为<int*>。是T对于int* 的特化
    fun6(&x);//输出Fun6 overload * is called.因为模板特化不会引入新的名称，所以在Name Lookup时，只会查找
    // fun6和其重载函数的名称，不会查找特化名称。编译器会选择T* （更特殊的版本）。然后再进行Function Template Specialization
    //发现T的模板特化，T*的模板没有特化，因此最后输出Fun6 overload * is called.


    fun7(&x);//输出Fun7 overload * is called.因为模板特化不会引入新的名称，所以在Name Lookup时，只会查找
    // fun7和其重载函数的名称，不会查找特化名称。编译器会选择T* （更特殊的版本）。然后再进行Function Template Specialization
    //发现T*的模板没有特化，因为特化位置改变了，特化自动推导为T的特化，因此最后输出Fun7 overload * is called.
    //特化隐式给定类型为<int>。是T 对于int 的特化

    fun8(&x);//输出Normal fun8  is called.在Name Lookup时，查找模板fun8、其重载函数的名称和正常的fun8函数。直接选择fun8，
    // 完美匹配。最后输出Normal fun8  is called.

    //但有重载不能代替函数模板特化的情况
    //使用if constexpr代替
    fun10<int>(&x);//If constexpr int.
    fun10<double>(&x);//If constexpr else.

    //还可以使用构造假形参（为了使用函数模板重载）
    fun11(&x, int{});//No-op int arguments.
    fun11(&x, double{});//No-op  no-int arguments.

    fun12(&x);
    fun12(x);
}