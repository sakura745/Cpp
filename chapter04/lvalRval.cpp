#include <iostream>
#include <vector>

struct Str {
    int x;
    //...
};
void fun(std::vector<int>&& par) {//"&&" is rvalue reference
    //xvalue传给 rvalue reference
    //rvalue reference是只能绑定到临时对象的引用的一种
}

void fun1(const int& par) {

}
int main() {
    int x;
    x = 3;//讨论表达式，去掉分号。x为glvalue，3为prvalue
    int y;
    y = 4;
    int xx = 3;//3作为初始化作用，3是prvalue。该语句的"="不是等于运算符，是表示拷贝初始化的，上一行的"="是等于运算符
    3 + 2;//3是运算符"+"的操作数的值，3 也是 prvalue
    int{};//prvalue 作为临时的对象
    Str{};//prvalue 作为临时的对象
    std::vector<int> x1;//x1 is a glvalue,
    fun(std::move(x1));//std::move()将 x1 构造为 xvalue

    //... 后续代码不会继续使用xvalue 将亡值

    const int a = 1;//a不能修改的左值(不能位于等号的左侧) "immutable lvalue"
    //首先a是一个glvalue。其次，a不是xvalue。因此a是lvalue
    //a = 5;//error:左值不一定能放到等号左边

    int z = int{};
    Str z2 = Str{};
    Str{}/*prvalue可以放到等号左边*/ = Str{};

    int b = 3;//b 是 左值(首先是确定对象、位或函数的表达式，其次是资源没被释放，因此是左值)
    int d = b;//当前语句中的b是右值，这是c++支持的左值与右值的转换
    int c = 3;
    b + c;//+运算符，b,c操作数是纯右值，b+c这个表达式就是将b,c从lvalue 转化为 rvalue

    //Temporary Materialization。概念的引出就是为了满足下面的条件
    Str{}.x;//Str{}作为临时变量，是prvalue。通过操作符'.'，来访问结构体中的x。相当于访问结构体这一整块内存中的取出x。
    //Str{}从prvalue 变成 xvalue
    fun1(3);//3是prvalue. fun1的参数是&引用，引用从定义上是绑定，但是不能把绑定到纯右值上。从定义上看，3从prvalue
    // 转到xvalue

    decltype((3)) e;//e->int, 3 is a prvalue
    decltype((x)) f = e;//f->int&, x is a lvalue

    //因为std::move(x) is xvalue. decltype(xvalue)->T&&. T&& means rvalue reference.
    //decltype(std::move(x)) g = x;//error: rvalue reference cannot bind lvalue,但可以绑定到左值引用、右值、将亡值上
    decltype(std::move(x)) g = std::move(x);//g->int&&, 绑定到将亡值上

    //左值通常希望访问地址
    //右值引用对象用作表达式时是左值
    int&& rvalRef/*从右值引用变成左值*/ = 5;

   //左值、右值等的相互转换是为了满足在不同上下文达到最佳的语义和性能，编译器自行的转换行为。
}