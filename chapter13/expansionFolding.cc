#include <iostream>

template <typename... T>
void fun(T... args) { // T是模式  T...是包展开
}


//如果两个形参包在同一模式中出现，那么它们同时展开而且长度必须相同：
template <typename...>
struct Tuple {};

template <typename T1, typename T2>
struct Pair {};

template <class... Args1>
struct zip
{
    template <class... Args2>
    struct with
    {
        using type = Tuple<Pair<Args1, Args2>...>;
        // Pair<Args1, Args2>... 是包展开
        // Pair<Args1, Args2> 是模式
    };
};

using T1 = zip<short, int>::with<unsigned short, unsigned>::type;
// Pair<Args1, Args2>... 会展开成
// Pair<short, unsigned short>, Pair<int, unsigned>
// T1 是 Tuple<Pair<short, unsigned short>, Pair<int, unsigned>>
//Tuple<Pair<Args1, Args2>...> : Args1 Args2分别是对Args1 Args2的遍历，Args1 Args2构成Pair后，再包展开

//using T2 = zip<short>::with<unsigned short, unsigned>::type;
// 错误：包展开中的形参包包含不同长度

template <class... Args1>
struct zip1
{
    template <class... Args2>
    struct with1
    {
        using type = Tuple<Tuple<Args1..., Args2>...>;
    };
};

using T3 = zip1<short, int>::with1<unsigned short, unsigned>::type;
//T3 是 Tuple<Tuple<short, int, unsigned short>，Tuple<short, int, unsigned>>
//Tuple<Tuple<Args1..., Args2>...>：Args1... 是对Args1的展开，Args2是对Args2的遍历



//c11的做法
void fun2() {//fun2递归的结束
    std::cout << "Fun2 is finished.\n";
}

template <typename U, typename... T>
void fun2(U u, T... args) {
    std::cout << u << std::endl;
    fun2(args...);
}


//c17的做法
template <typename... T>
void fun3(T... args) {
    ((std::cout << args << std::endl)/*E*/,/*op*/ ...);//折叠表达式
}

template <typename... Args>
int sum(Args&&... args) {
    return (args + ...);
}

int main() {
    fun<int, double, char>(1, 1.3, '1');//T...包展开为int double char，每个T是模式

    fun2(1, 2, "hello", 'c');//将1视为u，剩余的参数视为args...；fun2(args...)：将2视为u，剩余的视为args...；以此类推，
    // 最后args...对应为空，则调用void fun2()。基本的包展开的应用
    std::cout << "-------------------------------------" << std::endl;
    fun3(1, 2, "hello", 'c');

    std::cout << sum(1, 2, 3, 4, 5) << std::endl;
    //(args + ...);对应的折叠表达式为 (1 + (2 + (3 + (4 + 5))))
    //(... + args);对应的折叠表达式为 ((((1 + 2) + 3) + 4) + 5)
    //...表示一个折叠的过程


}
