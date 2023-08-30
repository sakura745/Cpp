#include <iostream>

/*[[nodiscard]]*/int fun(int a, int b) {
    return a + b;//返回数值
}
void fun1(int a, int b) {
    std::cout << a << ' ' << b << std::endl;//改变系统的状态
}

//c11
auto fun2(int a, int b) -> int {
    return a + b;
}

//c14
auto fun3(int a, int b) {//类型基于return 语句推导
    return a + b;
}
decltype(auto)/*更精确的控制返回类型，当有引用或者移动语义时，可以转换*/ fun4(int a, int b) {
    return a + b;
}

/*illegal,两条return类型不同
auto fun3(bool input) {
    if (input) {
        return 3;
    }
    else {
        return 1.5;
    }
}
*/

//legal
constexpr bool value = true;
auto fun4() {
    if constexpr (value) {//首先value是常量表达式，编译期间。其次if constexpr 也是编译期
        return 1;
    }
    else {
        return 3.14;
    }
}

struct Str{
    int x;
    int y;
};
Str fun5() {
    return Str{};
}
int main() {
    //before c17
    Str res = fun5();
    res.x;
    res.y;

    //c17
    auto [v1, v2] = fun5();//语法糖
    v1;
    v2;

    /*int x = */fun(2, 3);//没有保存返回值，空耗了计算资源，不是很好。
    //但fun函数添加nodiscard属性"[[nodiscard]] int fun(int a, int b)"就会有warning，提供给开发人员
}
