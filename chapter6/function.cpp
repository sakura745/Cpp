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
    //    return 100;legal
    return 2 + 3;//legal
//    return true;legal
}
std::vector<int> fun2() {
    std::cout << "Hello2" << std::endl;
    return {1, 2, 3, 4, 5};
}
std::initializer_list<int> fun3() {
    std::cout << "Hello3" << std::endl;
    return {1, 2, 3, 4, 5};
}
int& fun4() {
    int x = 3;
    return x;
}
int& fun5() {
    static int x = 3;
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

    int& ref = fun4();//同样是生命周期的危险

    int& ref2 = fun5();//no warning. static

    Str a;
    Str b = a;//copy constructor is called

    Str res = fun6();//两次copy constructor首先是fun6中返回的x拷贝构造临时对象（函数域中的临时对象），再拷贝到res中。
//named （具名）RVO:直接将第一步构造临时对象省略，将返回的对象直接在res上操作。目的是提升性能
}

