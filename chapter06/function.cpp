#include <iostream>
#include <vector>
#include <initializer_list>

void/*隐式返回的原因*/ fun() {
    std::cout << "Hello" << std::endl;
    //[space]隐式返回：应该返回到main函数，返回到函数的调用者
    return;//显式返回
}
int fun1() {
    std::cout << "Hello1" << std::endl;
    //    return 100;//legal
    return 2 + 3;//legal
//    return true;//legal
}
std::vector<int> fun2() {
    std::cout << "Hello2" << std::endl;
    return {1, 2, 3, 4, 5};
}
std::initializer_list<int> fun3() {//初始化列表推荐作为函数形参，不推荐作为函数返回类型
    std::cout << "Hello3" << std::endl;
    return {1, 2, 3, 4, 5};
}

//fun4会引起悬挂引用的问题。因为x是局部变量。
//fun5解决了悬挂引用的问题。
int& fun4() {
    int x = 3;
    return x;
}
int& fun5() {
    static int x = 3;//局部静态对象。生存周期是从初始化开始，到整个程序结束，而不是函数返回。
    return x;
}

struct Str {
    Str() = default;
    Str(const Str&) {
        std::cout << "Copy constructor is called\n";
    }
};
Str fun6() {
    Str x;
    return x;
}
int /*main虽然返回类型是int，但可以隐式返回*/ main() {
    fun();
    int x = fun1();
    std::cout << x << std::endl;

    auto y = fun2();

    auto z = fun3();//warning:initializer_list包含首尾两个指针，指针指向了被销毁的对象
    //用z进行操作时，可能会报错。

    int& ref = fun4();//同样是生命周期的危险

    int& ref2 = fun5();//no warning. static

    Str a;
    Str b = a;//copy constructor is called

    Str res = fun6();//两次copy constructor。首先是fun6中返回的x拷贝出Str函数，构造临时对象（函数域中的临时对象），
    // 再是fun6()拷贝到res中。
    //named(具名)RVO:直接将构造临时对象省略，返回的对象直接在res上操作。底层是获取res的地址，
    // 直接在res上进行操作。目的是提升性能
}

