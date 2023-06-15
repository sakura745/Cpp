#include <iostream>
#include <type_traits>//元编程库

template <int x>
struct M {
    constexpr static int val = x + 1;
};

consteval int fun(int x) {
    return x + 1;
}

constexpr int val2 = fun(3);

template <int x>
struct N {
    using type = int[x];
};

template <unsigned... T> struct Cont;//声明，编译期数组
template <auto... T> struct Cont2;//声明，编译期数组
template <typename... T> struct Cont3;//声明，编译期数组
template <template <typename> class... T> struct Cont4;//声明，编译期数组

int fun2(int input) {//函数有副作用：每次调用，都会产生不同的影响，x属于变量
    static int x = 0;
    return input + (x++);
}

int main() {

//    return M<3>::val;//整个计算是在编译期完成的，典型的元程序
//    return val2;//典型的元程序
//    return sizeof(int);//典型的元程序
     N<2>::type a;
     std::cout << std::is_same_v<decltype(a), int[2]> << std::endl;

     int b[3];//运行期数组


}