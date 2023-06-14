#include <iostream>
#include <vector>
#include <type_traits>

template <typename T>
using MyType = T;//模板本身引入别名

template <typename T>
using AddPointer = T*;

template <class T>
struct Alloc{};
template <class T>
using Vec = std::vector<T, Alloc<T>/*自定义分配器*/>;


template <typename T>
struct B {
    using TP = T*;//类模板成员引入别名
};

template <typename T>
using MyPointer = typename B<T>::TP;

//构造一个int模板特化,直接使用别名不可以。illegal: expected unqualified-id before ‘using’.
/*template <>
using MyPointer<int> = int&;*/

template <typename T>
struct B2 {
    using type = T*;
};

//但可以基于类模板的特化引入别名。通过类模板中对int特化
template <>
struct B2<int> {
    using type = int&;
};

template <typename T>
using MyPointer2 = typename B2<T>::type;

template <typename T>
using M = T*;
template <typename T>
void fun(M<T> input) { // M<T> 等价于 T*

}

template <typename T>
struct D {
    using typeD = T*;
};
template <typename T>
using M2 = typename D<T>::typeD;
template <typename T>
void fun2(M2<T> input) { // M<T> 等价于 typename D<T>::typeD，不支持实参推导。可能存在对于T的特化，因此无法推导出T
}


template <int... a/*模板形参包，零到多个参数*/>
void fun3() {
}
template <typename... a/*模板形参包，零到多个参数*/>
void fun4() {
}
template <template<typename> class... a/*模板形参包，零到多个参数*/>
void fun5() {
}

template <typename... T>
void fun6(T ... args/*函数形参包*/) {
}


//在主类(非特化版本)模板中，模板形参包必须是模板形参列表的最后一个形参。在函数模板中，模板参数包可以在列表中
// 更早出现，只要其后的所有形参都可以从函数实参推导或拥有默认实参即可：

template<typename U, typename... Ts>    // OK：能推导出 U
struct valid {};
// template<typename... Ts, typename U> // 错误：Ts... 不在结尾
// struct Invalid;

template<typename... Ts, typename U, typename = void>
void valid2(U, Ts...) {}    // OK：能推导出 U
// void valid(Ts..., U); // 不能使用：Ts... 在此位置是不推导语境

template <typename... T>
void fun7(T ... args/*函数形参包*/) {
    std::cout << sizeof.../*c11引入，表示包里包含了多少个类型*/(T) << std::endl;
}

template <typename... T>
class E;

template <typename T1, typename T2>
class F;

template <typename... T, typename T2>
class F<E<T...>, T2> {

};


int main() {
    MyType<int> x;//x -> int
    AddPointer<int> x2;//x2 -> int*

    MyPointer<double> x3;//x3 -> double*

    MyPointer2<int> x4 = x;//x4 -> int&
    std::cout << std::is_same_v<decltype(x4), int&> << std::endl;
    MyPointer2<float> x5;//x5 -> float*
    std::cout << std::is_same_v<decltype(x5), float*> << std::endl;

    int y;
    fun(&y);

//    fun2(&y);//illegal 不支持实参推导
    fun2<int>(&y);//legal 显式给出

    fun3<1, 2, 3>();
    fun4<int, double, char>();

    fun6<int, double, char>(3, 123.4, 'a');
    fun6(3, 123.4, 'a');//可以通过模板实参推导


    valid2(1.0, 1, 2, 3);     // OK：推导出 U 是 double，Ts 是 {int, int, int}

    fun7(1.0, 1, 3, "chs", 'c');//输出 5，5个参数调用
}
