#include <iostream>

void fun() {
    std::cout << "Global fun is called.\n";
}

namespace MyNS {
    void fun() {
        std::cout << "MyNs::fun is called.\n";
    }
    void g() {
        fun();
    }
}

namespace MyNS2 {
    struct Str {};
    void g(Str x) {

    }
}

int main() {
    //qualified lookup
    ::fun();
    MyNS::fun();

    //unqualified lookup
    fun();

    //逐级查找，即使MyNS中的fun形参类型与实参类型不同，也优先域查找
    MyNS::g();

    MyNS2::Str obj;
    g(obj);//unqualified
    // 没有使用::便可以调用g函数是因为结构体Str在定义的时候就将namespace信息赋给obj
    //实参依赖查找(ADL)：在函数调用时，编译器不仅会查找函数名所在的命名空间，还会查找与函数参数相关联的命名空间
    //意味着：当调用函数时，编译器会考虑函数参数的类型
}