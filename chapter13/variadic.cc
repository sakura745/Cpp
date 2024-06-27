#include <iostream>

///模板形参包
template <int.../*模板形参包，零到多个数值*/ a>
void fun() {}

template <typename.../*模板形参包，零到多个类型*/ a>
void fun2() {}

template <template <typename> class.../*模板形参包，零到多个类模板*/ a>
void fun3() {}
template <typename T>
class B {};
template <typename T>
class B2 {};
template <typename T>
class B3 {};


///函数形参包
template <typename... T>
void fun4(T.../*函数形参包*/ args) {}

template <typename... Types>
struct Tuple {};


//在主类模板中(非特化版本)，模板形参包必须是模板形参列表的最后一个形参。特化版本没有限制
//在函数模板中，模板参数包可以在列表中更早出现，只要其后的所有形参都可以从函数实参推导或拥有默认实参即可

template <typename U, typename... Ts>    // OK：能推导出 U
struct valid {};

//template <typename... Ts, typename U> // 错误：Ts... 不在结尾
//struct Invalid {};

template <typename... Ts, typename U, typename = void>
void valid2(U, Ts...) {}    // OK：能推导出 U
// void valid(Ts..., U); // 不能使用：Ts... 在此位置是不推导语境

template <typename... T>
void fun5(T.../*函数形参包*/ args) {
    std::cout << sizeof...(T)/* sizeof... c11引入，表示包里包含了多少个类型*/ << std::endl;
}

template <typename... T>
class E;

template <typename T1, typename T2>
class F;

template <typename... T, typename T2>//F的特化版本 T -> T...
class F<E<T...>, T2> {};

int main() {
    fun<1, 2, 3>();
    fun2<int, double, char>();
    fun3<B, B2, B3>();

    fun4<int, double, char>(3, 123.4, 'a');//T要对应上
    fun4(3, 123.4, 'a');//可以通过模板实参推导

    Tuple<> t0;           // Types contains no arguments
    Tuple<int> t1;        // Types contains one argument: int
    Tuple<int, float> t2; // Types contains two arguments: int and float
//    Tuple<0> t3;          // error: 0 is not a type


    valid2(1.0, 1, 2, 3);     // OK：推导出 U 是 double，Ts 是 {int, int, int}

    fun5(1.0, 1, 3, "chs", 'c');//输出 5，5个参数调用
}
