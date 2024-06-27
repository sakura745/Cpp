#include <iostream>
#include <vector>
#include <type_traits>

template <typename T>
using MyType = T;//模板本身引入别名

template <typename T>
using AddPointer = T*;

template <class T>
struct Alloc {};
template <class T>
using Vec = std::vector<T, Alloc<T>/*自定义分配器*/>;


template <typename T>
struct B {
    using TP = T*;//类模板成员引入别名
};

template <typename T>
using MyPointer = typename B<T>::TP;


template <typename T>
using alias = T*;
//构造一个int模板特化,直接使用别名不可以。illegal: expected unqualified-id before ‘using’.
//对int特化进行using
//template <>
//using alias<int> = int&;


//但可以基于类模板的特化引入别名
template <typename T>
struct B2 {
    using type = T*;
};
//通过类模板中对int特化
template <>
struct B2<int> {
    using type = int&;
};

template <typename T>
using MyPointer2 = typename B2<T>::type;

template <typename T>
using M = T*;
template <typename T>
void fun(M<T> input) {} // M<T> 等价于 T*


template <typename T>
struct D {
    using typeD = T*;
};

template <typename T>
struct D<T*> {
    using typeD = T*;
};

template <typename T>
using M2 = typename D<T>::typeD;

template <typename T>
void fun2(M2<T> input) {} // M<T> 等价于 typename D<T>::typeD，不支持实参推导。可能存在对于T的特化，因此无法推导出T

int main() {
    MyType<int> x;//x -> int
    AddPointer<int> x2;//x2 -> int*
//    Vec<int> xx;//编译器要求Alloc分配器要有value_type等成员

    MyPointer<double> x3;//x3 -> double*
    MyPointer2<int> x4 = x;//x4 -> int&
    std::cout << std::is_same_v<decltype(x4), int&> << std::endl;
    MyPointer2<float> x5;//x5 -> float*
    std::cout << std::is_same_v<decltype(x5), float*> << std::endl;

    int y;
    fun(&y);

//    fun2(&y);//illegal 不支持实参推导
    fun2<int>(&y);//legal 显式给出
}
