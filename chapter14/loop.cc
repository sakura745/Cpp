#include <iostream>
#include <type_traits>

//示例1：用于计算二进制中包含1的个数
//数值模板
template <int x>
constexpr auto fun = (x % 2) + fun<x / 2>;//循环体

//数值模板的特化
template <>
constexpr auto fun<0> = 0;//循环结束条件，相当于一个分支

constexpr auto x = fun<99>;


//示例2：使用循环处理数组 --- 处理类型的循环
template <typename...> class Cont;
using Input = Cont<int, char, double, bool, void>;
//声明
template <typename Res/*处理完成*/, typename Rem/*待处理*/>
struct Imp;
//函数循环体
template <typename... Processed, typename T1, typename T2, typename... TRemain>
struct Imp<Cont<Processed...>, Cont<T1, T2, TRemain...>> {
    using type1 = Cont<Processed..., T1>;//处理完成，将T1加入
    using type = typename Imp/*递归到当前Imp*/<type1, Cont<TRemain...>>::type;
};
//终止条件1：还剩下一个T1
template <typename... Processed, typename T1>
struct Imp<Cont<Processed...>, Cont<T1>> {
    using type = Cont<Processed..., T1>;
};
//终止条件2：什么也不剩下
template <typename... Processed>
struct Imp<Cont<Processed...>, Cont<>> {
    using type = Cont<Processed...>;
};

using Output = Imp<Cont<>/*表示处理完的为空*/, Input/*待处理的为Input中*/>::type;



//示例3：获得数组后三个元素
template <typename Res, typename Rem>
struct Imp2 {
    using type = Res;
};

template <typename U1, typename U2, typename U3, typename T, typename... TRemain>
struct Imp2<Cont<U1, U2, U3>, Cont<T, TRemain.../*表示待处理的部分不为空：T是一个，包是零或多个*/>> {
    using type1 = Cont<U2, U3, T>;
    using type = typename Imp2<type1, Cont<TRemain...>>::type;
};

//终止条件1
template <typename U1, typename U2, typename T, typename... TRemain>
struct Imp2<Cont<U1, U2>, Cont<T, TRemain...>> {
    using type1 = Cont<U1, U2, T>;
    using type = typename Imp2<type1, Cont<TRemain...>>::type;
};
//终止条件2
template <typename U1, typename T, typename... TRemain>
struct Imp2<Cont<U1>, Cont<T, TRemain...>> {
    using type1 = Cont<U1, T>;
    using type = typename Imp2<type1, Cont<TRemain...>>::type;
};
//终止条件3
template <typename T, typename... TRemain>
struct Imp2<Cont<>, Cont<T, TRemain...>> {
    using type1 = Cont<T>;
    using type = typename Imp2<type1, Cont<TRemain...>>::type;
};


using Output2 = Imp2<Cont<>, Input>::type;

int main() {
    std::cout << x << std::endl;

    std::cout << std::is_same_v<Output, Cont<int, double, void>> << std::endl;

    std::cout << std::is_same_v<Output2, Cont<double, bool, void>> << std::endl;
}
