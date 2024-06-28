#include <iostream>
#include <type_traits>
#include <typeinfo>

//也是元编程的分支结构，但是使用场景较为固定
constexpr int fun(int x) {
    if (x > 3) {
        return x * 2;
    } else {
        return x - 100;
    }
}
constexpr int x = fun(100);

template <int x>
/*因为没有constexpr，所以是运行期执行fun函数*/int fun() {
    if constexpr/*不要写成if，会引入运行期的计算*/ (x > 3) {
        return x * 2;
    } else {
        return x - 100;
    }
}
//在编译期会变成
//template <>
//int fun<100>() {
//    return 200;
//}


//通过偏特化引入分支
template <int x>
struct Imp {
    constexpr static int value = x * 2;
    using type = int;
};
//相当于引入的分支
template <>
struct Imp<100> {
    constexpr static int value = 100 - 3;
    using type = double;
};
constexpr int x2 = Imp<97>::value;
using type1 = Imp<97>::type;//type1是int
constexpr int x3 = Imp<100>::value;
using type2 = Imp<100>::type;//type2是double


//为了仿照if constexpr的效果，写出x > 3和 x <= 3的这种范围性分支，通过引入requires语句
template <int x>
struct Imp2;//声明

template <int x>
    requires (x < 100)
struct Imp2<x>/*特化*/ {
    constexpr static int value = x * 2;
    using type = int;
};

template <int x>
    requires (x >= 100)
struct Imp2<x> {
    constexpr static int value = x - 99;
    using type = double;
};
constexpr auto x4 = Imp2<100>::value;
constexpr auto x5 = Imp2<10>::value;


//enable_if使用SFINAE
template <int x, std::enable_if_t<(x < 100)>/*x < 100 为true，enable_if_t返回 void */* = nullptr/*缺省模板参数*/>
constexpr auto fun3() {
    return x * 3;
}
template <int x, std::enable_if_t<(x >= 100)>* = nullptr>
constexpr auto fun3() {
    return x - 3;
}
//上述两个fun3是通过函数重载

constexpr auto x6 = fun3<99>();


template <int x, typename = void*/*缺省模板实参，无需写类型名T */>
struct Imp3;

template <int x>
struct Imp3<x, std::enable_if_t<(x < 100)>*> {
    constexpr static int value = x * 4;
};

template <int x>
struct Imp3<x, std::enable_if_t<(x >= 100)>*> {
    constexpr static int value = x - 4;
};

constexpr auto x7 = Imp3<91>::value;


//fun4不认为是像fun3一样的为重载，因此变成为会报重定义错误。是因为先进行 重载解析，再进行 模板重载实例化。
//进行重载解析的时候，就发现重定义了，没有到模板特化，因此不会考虑缺省实参
template <int x, typename = std::enable_if_t<(x < 100)>>
constexpr auto fun4() {
    return x * 3;
}
/*
template <int x, typename = std::enable_if_t<(x >= 100)>>
constexpr auto fun4() {
    return x - 3;
}
*/
constexpr auto x8 = fun4<99>();
//constexpr auto x9 = fun4<199>();//illegal。重载解析不会报错，实例化会报错。std::enable_if_t<(x < 100)>可以作为一个判断条件，开关。


template <int x>
constexpr auto fun5 = (x < 100) ? x * 5 : x - 5;
constexpr auto x9 = fun5<99>;
constexpr auto x10 = fun5<199>;
int main() {
    int y = fun<100>();//fun运行期执行

    std::cout << x2 << ' ';//输出为194
    std::cout << std::is_same_v<type1, int> << std::endl;
    std::cout << x3 << ' ';//输出为97
    std::cout << std::is_same_v<type2, double> << std::endl;

    std::cout << x4 << ' ' << x5 << std::endl;

    //conditional与三元表达式类似，详见cppreference
    using Type1 = std::conditional<true, int, double>::type;
    using Type2 = std::conditional_t<false, int, double>;
    using Type3 = std::conditional<sizeof(int) >= sizeof(double), int, double>::type;

    std::cout << typeid(Type1).name() << ' ' << typeid(Type2).name() << ' ' << typeid(Type3).name() << '\n';

    std::cout << x6 << std::endl;

    std::cout << x7 << std::endl;

    std::cout << x9 << std::endl;
    std::cout << x10 << std::endl;


}