#include <vector>
#include <iostream>
#include <type_traits>

template <size_t A>
struct Wrap_ {
    template<size_t ID, typename TDummy = void>
    struct imp {
        constexpr static size_t value = ID + imp<ID - 1>::value;
    };

    template <typename TDummy>//不允许嵌套完全特化，因此引入假参数TDummy来引入部分特化
    struct imp<0, TDummy> {
        constexpr static size_t value = 0;
    };

    template <size_t ID>
    constexpr static size_t value = imp<A + ID>::value;
};



template<size_t ID, typename TDummy = void>
struct imp {
    constexpr static size_t value = ID + imp<ID - 1>::value;
};

template <typename TDummy>
struct imp<0, TDummy> {
    constexpr static size_t value = 0;
};

template <size_t A>
struct Wrap1_ {
    template <size_t ID>
    constexpr static size_t value = imp<A + ID>::value;
};


using Res = std::conditional_t<false,
                                std::remove_reference_t<int&>,
                                std::remove_reference_t<double&>>;
//std::remove_reference_t<int&>是std::remove_reference<int&>::type的简写，当没有访问type时，不会实例化。当访问type会实
// 例化
//因此Res的获得会构造std::remove_reference_t<int&>、std::remove_reference_t<double&>、std::conditional_t<...>的type。
//但std::conditional_t的是false，第二个参数std::remove_reference_t<int&>实例化没必要

using Res1 = std::conditional_t<false,
                                std::remove_reference<int&>,
                                std::remove_reference<double&>>::type;
//std::conditional_t<false, std::remove_reference<int&>, std::remove_reference<double&>>表示为std::remove_reference<double&>
//因此Res的获得会构造std::remove_reference<double&>的type。

//但当conditional中的第二、三个参数不同时，
//using Res2 = std::conditional_t<true,
//                               double&,
//                               std::remove_reference<double&>>::type;//illegal。因为double&没有type这个内建数据类型

template <typename T>
struct Identity {
    using type = T;
};
using Res3 = std::conditional_t<true,
                                Identity<double&>,
                                std::remove_reference<double&>>::type;//legal。给double&构造了一个type

//对于&& 和 || 的短路逻辑是运行期行为，而不是编译期行为。
template <typename T>
constexpr bool intOrDouble = std::is_same_v<T, int> || std::is_same_v<T, double>;//编译期一起求值，两个一起实例化

template <typename T>
constexpr bool intOrDouble2 = std::disjunction<std::is_same<T, int>, std::is_same<T, double>>::value;//编译期实现短路逻辑


template <typename... T> class Cont;

template <typename T, unsigned id>
struct At;

template <typename TCur, typename... T, unsigned id>
struct At<Cont<TCur, T...>, id> {
    using type = typename At<Cont<T...>, id - 1>::type;
};

template <typename TCur, typename... T>
struct At<Cont<TCur, T...>, 0> {
    using type = TCur;
};

using res = At<Cont<double, int, char, bool>, 2>::type;//获得数组中第2个元素的类型
//会产生如下实例
//At<Cont<double, int, char, bool>, 2>
//At<Cont<int, char, bool>, 1>
//At<Cont<char, bool>, 0>

using res2 = At<Cont<double, int, char, bool>, 3>::type;
//会产生如下实例
//At<Cont<double, int, char, bool>, 3>
//At<Cont<int, char, bool>, 2>
//At<Cont<char, bool>, 1>
//At<Cont<bool>, 0>
//上述实例互不相同，通过引入中间变量来减少分摊复杂度。



int main() {
    std::vector<int> a;
    std::vector<int> b;
    //上述两行编译器处理的消耗不同，第一行是从0开始处理，保存相应模板等信息；第二行是由于第一行所存储的信息，来处理第二行。
    //这种过程对于通常程序为优化，但是对于元编程来说，属于灾难。

    std::cout << Wrap_<3>::value<2> << std::endl;//5 + ... + 0
    //构造的实例：Wrap_<3>::imp<5>, Wrap_<3>::imp<4>, Wrap_<3>::imp<3>, ... Wrap_<3>::imp<0>
    std::cout << Wrap_<10>::value<2> << std::endl;//12 + ... + 0
    //构造的实例：Wrap_<10>::imp<12>, Wrap_<10>::imp<11>, ... Wrap_<10>::imp<0>
    //Wrap_<10>::imp<0>的构造会想 vector a b那样的使用Wrap_<3>::imp<0>吗？
    //并不会，因为Wrap_<10>和Wrap_<3>不同。但是Wrap_<10>和Wrap_<3>中的imp<0>没有什么区别。编译器会额外的构造。

    //进行优化：将元编程从类模板中提取。构造的实例不同。
    std::cout << Wrap1_<3>::value<2> << std::endl;
    //构造的实例：imp<5>, imp<4>, imp<3>, ... imp<0>
    std::cout << Wrap1_<10>::value<2> << std::endl;
    //构造的实例：imp<12>, imp<4>, imp<3>, ... imp<0>
    //就会重复使用imp<5>, imp<4>, imp<3>, ... imp<0>

    std::cout << std::is_same_v<Res, double> << std::endl;
    std::cout << std::is_same_v<Res1, double> << std::endl;

    std::cout << std::is_same_v<Res3, double> << std::endl;
    std::cout << std::is_same_v<Res3, double&> << std::endl;

    std::cout << std::is_same_v<res, char> << std::endl;



}