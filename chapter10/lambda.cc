#include <iostream>
#include <string>
struct Str {
    auto fun() {
        int val = 3;
        auto lam = [val, this/* 是一个指针，指向结构体的对象（成员函数），在这里是x */] () {
            return val > x/* x既不是局部自动对象，也不是静态对象，想要捕获x要传入this，x相当于this->x */;
        };
        return lam();
    }
    int x;
};

struct Str1 {
    auto fun() {
        int val = 3;
        auto lam = [val, *this/* c17将this改为*this，解引用就不是指向这个对象了，变成就是这个对象，
 *                                  变成值捕获，直接复制到函数体中 */] () {
            return val > x;
        };
        return lam;
    }
    int x;
};

auto wrapper() {
    Str1 s;
    return s.fun();
}
int main() {
    //lambda表达式构造一个对象 x
    auto x = [] (int val) {
        return val > 3 && val < 10;
    };
    std::cout << x(5) << std::endl;
    auto y/*隐式转化为double*/ = [] (int val) {
        if (val > 3)
            return 3.0;
        else
            return 1.4;
    };
    auto z = [] (int val) -> double/*return类型不同，将不能自动推导，显式指定类型*/ {
        if (val > 3)
            return 3.0;
        else
            return 1.4f;
    };

    //static int a = 10;// 因为是静态对象，不需要捕获也能使用。clang报错，gcc报warning
    int a = 10;//局部自动对象，需要捕获才能使用
    auto a1 = [a] (int val) { return val > a; };
    std::cout << a1(5) << std::endl;

    auto a2 = [a/*值捕获，复制到函数体中*/] (int val) mutable/*用于值捕获且修改值时*/ {
        ++a;
        return val > a;
    };
    std::cout << a2(12) << " " << a/*还是10，不会传递到lambda表达式外部*/ << std::endl;

    auto a3 = [&a/*引用捕获*/] (int val) {
        ++a;
        return val > a;
    };
    std::cout << a3(12) << " " << a/*是11，引用*/ << std::endl;

    int aa = 3;
    auto a4 = [&a, aa/*混合捕获*/] (int val) {
        ++a;
        return val > aa;
    };
    std::cout << a4(4) << " " << a << std::endl;

    auto a5 = [=/*对隐式的对象使用 值捕获*/, &aa/*显式引用捕获*/] (int val) {
        //... 很多局部自动对象
        return val > aa;
    };
    auto a6 = [&/*对隐式的对象使用 引用捕获*/, aa/*显式值捕获*/] (int val) {
        //... 很多局部自动对象
        return val > aa;
    };

    Str s;
    s.fun();//Str中使用this对成员函数的捕获，其中this对应s的地址

    int zz = 3;
    auto lam = [yy = zz/*c14。初始化捕获*/] (int val) {
        return val > yy;
    };
    std::cout << lam(100) << std::endl;

    std::string ss = "hello";
    auto lam1 = [sss = std::move(ss)] () {
        std::cout << sss << std::endl;
    };
    std::cout << ss << std::endl;
    lam1();

    ///初始化捕获的优点
    //通常情况下
    int bbb = 3;
    int ccc = 5;
    auto lam2 = [bbb, ccc] (int val) {
        return val > (bbb + ccc);//每调用一次lambda表达式，bbb+ccc都要执行一次
    };

    //在一定程度上提高了效率
    auto lam3 = [aaa = bbb + ccc/*构造lambda表达式执行，存储为aaa，每次调用lambda表达式，
                                 * 直接调用aaa即可*/] (int val) {
        return val > aaa;
    };

    //用于建立一个新的同名变量，不会污染外部名字作用域 -- 相当于值捕获的显式
    auto lam4 = [bbb/*用来函数体计算的*/ = bbb/*给函数体bbb初始化的对象*/] (int val) {
        return val > bbb;
    };
    std::cout << "------------" << std::endl;

    auto lamb = wrapper();
    //wrapper返回了lambda表达式，该表达式捕获了this指针，this指针指向的是wrapper中构造的局部自动对象s。
    //在调用wrapper之后，s已经被销毁了。就是说lamb中，包含了一个悬挂指针dangling pointer
    lamb();//行为是未定义的
    ///c17将this 改为 *this。好处是不会产生悬挂指针，行为是安全的。坏处是变成了值捕获，从指针的复制变成对解引用对象复制
    ///要消耗更多资源

}