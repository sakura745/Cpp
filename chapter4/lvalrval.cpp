#include <iostream>
#include <vector>

struct Str {
    int x;

    //...
};
void fun(std::vector<int>&& par) {//par is rvalue reference

}

void fun1(const int& par) {

}
int main() {
    int x;
    x = 3;//讨论表达式，去掉分号。x为glvalue，3为prvalue
    int y;
    y = 4;
    int{};//prvalue 作为临时的对象
    Str{};//prvalue 作为临时的对象
    std::vector<int> x1;//x1 is a glvalue, x1 is also a xvalue
    fun(std::move(x1));//std::move()构造xvalue

    //... 后续代码不会继续使用xvalue 将亡值

    const int a = 1;//a is a immutable lvalue
    //首先a是一个glvalue。其次，a不是xvalue。因此a是lvalue
    //a = 5;error:左值不一定能放到等号左边

    int z = int();
    Str z2 = Str();
    Str() = Str();//prvalue可以放到等号左边


    int b = 3;
    int c = 3;
    b + c;//+运算符，b c操作数，b+c这个表达式就是从lvalue 转化为 rvalue

    Str().x;//Str()作为临时变量，是prvalue。通过操作符'.'，来访问结构体中的x。相当于访问结构体这一整块内存中的取出x。
    //prvalue -> xvalue
    fun1(3);    //prvalue -> xvalue

    decltype((3)) e;//e->int, 3 is a prvalue
    decltype((x)) f = e;//f->int&, x is a lvalue
    //decltype(std::move(x)) g = x;//error: rvalue reference cannot bind lvalue
    decltype(std::move(x)) g = std::move(x);//g->int&&, x is a xvalue


}