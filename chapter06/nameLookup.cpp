#include <iostream>

void fun() {
    std::cout << "Global fun is called.\n";
}
void fun2(int) {
    std::cout << "Global fun2 is called.\n";
}

void fun3(int) {
    std::cout << "Global fun3 is called.\n";
}
namespace MyNS {
    void fun() {
        std::cout << "MyNs::fun is called.\n";
    }
    void fun2(double) {
        std::cout << "MyNs::fun2 is called.\n";
    }
    void g() {
        fun();
    }
    void g2() {
        fun2(3);
    }
    void g3() {
        fun3(3);
    }
    void fun3(double) {
        std::cout << "MyNs::fun3 is called.\n";
    }
}

namespace MyNS2 {
    struct Str {};
    void g4(Str x) {

    }
}

int main() {
    //qualified lookup
    ::fun();
    MyNS::fun();

    //unqualified lookup
    fun();

    MyNS::g();

    //逐级查找，即使MyNS中的fun2形参类型与实参类型不同，也优先域查找。也可以表示MyNs::g2()隐藏了::g2()
    MyNS::g2();

    MyNS::g3();//输出的是Global fun3 is called ,而不是MyNs::fun3 is called，
    //因为g3()定义在fun3()之前，不会查找到fun3()。为了解决该问题，可以先将声明置于g3()之前

    MyNS2::Str obj;
    g4(obj);//unqualified
    //正常来说，非限定查找不会找到名字空间内，但是上两行程序可以正常运行
    // 没有使用::便可以调用g4()是因为结构体Str在定义的时候就将namespace信息赋给obj，考虑到类型
    //实参依赖查找(ADL)：在函数调用时，编译器不仅会查找函数名所在的命名空间，还会查找与函数参数相关联的命名空间
    //意味着：当调用函数时，编译器会考虑函数参数的类型
}