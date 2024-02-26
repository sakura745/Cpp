#include <iostream>
#include <map>
#include <functional>

auto fun(int val) {
    return val + 1;
}

auto fun(double val) {
    return val + 1;
}

int factorical(int n) {//n的阶乘
    return n > 1 ? n * factorical(n - 1) : 1;
}
int main() {
    int y = 3;
    auto lam = [y] (int val) mutable/*说明符*/ {
        ++y;
        return val > y;
    };

    auto lam1 = [](int val) constexpr/* c17 *//* consteval c20也行 */ {
        return val + 1;
    };
    constexpr int val1 = lam1(100);
    std::cout << val1 << std::endl;

    auto lam2 = []<typename T>(T val)/*c20模板形参*/ {
        return val + 1;
    };
    int val2 = lam2(100.0f);

    ///捕获时计算c14 和 IIFE
    int a = 1;
    int b = 2;
    auto lam3 = [c = a + b/*捕获时计算*/] () {
        return c;
    }()/*IIFE，意思是在构造完lambda表达式之后，立即执行表达式，而不是再使用lam3()来调用*/;

    //目的是为了初始化常量使用的 const。
    const auto val3 = [c = a + b]() {
        return c;
    }();
    std::cout << val3 << std::endl;

    ///避免复制c14
    auto lam4 = [](auto/*c14合法*/ x) {
        return x + 1;
    };

    std::map<int, int> m{{2, 3}};
    auto lam5 = [](const std::pair<int, int>& p) {
        return p.first + p.second;
    };
    std::cout << lam5(*m.begin()) << std::endl;
    //lam5的lambda表达式的形参设置为常量引用，在使用lam5(*m.begin())时，避免复制。
    //但是实际上map的类型是std::pair<const int, int>,因此编译器的行为是使用lam5(*m.begin())时，
    //将std::pair<const int, int>复制给std::pair<int, int>，再进行调用引用。
    //避免类型转换的复制问题，lambda表达式形参使用(const auto& p)

    ///Lifting c14
//    auto bb = std::bind(fun, 3);//illegal 对于函数重载，编译器不能确定bind绑定哪个fun
//    std::cout << bb() << std::endl;
    auto lam6 = [](auto/*配合函数重载*/ x) {//相当于实现了函数模板
        return fun(x);
    };
    std::cout << lam6(3) << std::endl;
    std::cout << lam6(3.3) << std::endl;

    ///递归调用 c14-利用了auto
//    auto lam7 = [](int n) {
//        return n > 1 ? n * lam7(n - 1) : 1;
//    };
//    std::cout << lam7(5) << std::endl;
    //auto类型判断是要整个语句解析完整，才知道。如何知道后面部分是lamb表达式，要整个解析完，但是在解析到lam7(n - 1)时，
    //由于lam7的类型不确定，lam7(n - 1)行为不确定，所以不能接着解析。相当于a的问题是因为b，b的问题又是因为a，递归导致的。
    //由于不能接着解析，不能确定赋值右侧的部分，也不能使用。auto无法解析lam7类型

    //但是函数可以：递归函数factorical如何解析。当遇到int factorical(int n)，编译器知道factorical是一个函数，输入int值，
    // 返回int值，到了这一行， return n > 1 ? n * factorical(n - 1) : 1;自然可以解析
    std::cout << factorical(5) << std::endl;

    //修改为如下
    auto lam7 = [](int n) {
        auto lam8 = [](int n, const auto& lam9) -> int {
            return n > 1 ? n * lam9(n - 1, lam9)/*递归lam9*/ : 1;
        };
        return lam8(n, lam8);//递归lam8
    };
    std::cout << lam7(5) << std::endl;
    //auto类型判断是要整个语句解析完整，才知道。如何知道后面部分是lamb表达式，要整个解析完。lam7的函数体中没有调用lam7,
    //因此可以解析出lam7是一个lambda表达式。为什么内部可以解析出是lambda表达式：lam8函数体中，也没有出现lam8
    //因此可以解析出lam8是一个lambda表达式。
    // return lam8(n, lam8);这一句，函数定义好了，正常调用也没问题。才将lam8变成递归。
    //是用了const auto& lam9形成一个完整的表达式（函数模板表达式）。通过对lam9变成lambda表达式

    //如果最内层的lambda表达式类型 -> int 去掉，则为非法。return lam8(n, lam8);去掉，则为合法
    auto lam10 = [](int n) {
        auto lam8 = [](int n, const auto& lam9)  {
            return n > 1 ? n * lam9(n - 1, lam9) : 1;
        };
//        return lam8(n, lam8);
    };
    //外层lambda表达式返回void， 用cppinsights看出内层的本质类中的operator()的返回类型是auto
    //内层调用递归函数，又相当于最开始讨论的问题，是因为递归的原因。但是人为规定内层返回类型为int，
    //就不需要知道return n > 1 ? n * lam9(n - 1, lam9) : 1;返回的类型了
    //内层函数指定int类型，return lam8(n, lam8);返回类型也确定了，也都能work了。

}