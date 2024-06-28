#include <iostream>
#include <type_traits>//元编程库

template <int x>
struct M {
    constexpr static int val = x + 1;
};
//输入为数值x，输出为数值

consteval int fun(int x) {
    return x + 1;
}

constexpr int val2 = fun(3);

template <int x>
struct N {
    using type = int[x];
};
//输入为数值，输出为类型

//编译期的数组
template <unsigned... T> struct Cont;//声明 数值数组
template <auto... T> struct Cont2;//数值数组
template <typename... T> struct Cont3;//类型数组
template <template <typename> class... T> struct Cont4;//模板数组

int fun2(int input) {//函数有副作用：每次调用，都会产生不同的影响，x属于变量
    static int x = 0;
    return input + (x++);
}

int main() {

//    return M<3>::val;//整个计算是在编译期完成的，典型的元程序
//    return val2;//典型的元程序
//    return sizeof(int);//输入为类型，输出为数值。典型的元程序
    //return属于编译期输出，std::cout属于运行期输出
    N<2>::type a;

    int b[3];//运行期数组

    std::cout << std::is_same_v<decltype(a), int[2]> << std::endl;
    //is_same_v 输入为两个类型，输出为bool值


}