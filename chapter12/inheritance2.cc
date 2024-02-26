#include <iostream>

namespace inheritance2 {
    class Base {
    public:
        Base() {
            std::cout << "Base ctor is called.\n";
        }
        int val = 2;
    };
    class Derive : public Base {//Derive所在的类域嵌套在Base类域里面
    public:
        Derive() {
            std::cout << "Derive ctor is called.\n";
        }
        void fun() {
            std::cout << val << std::endl;//输出的val是Derive域的val，因为Derive的val覆盖了Base的val
            std::cout << Base::val << std::endl;//用域操作符指定val，显式访问基类成员
        }
        int val = 3;
    };


    class Base1 {
    public:
        Base1(int) {
            std::cout << "Base1 ctor is called.\n";
        }

    };
    class Derive1 : public Base1 {
    public:
        Derive1(int a) : Base1(a)/*在派生类中显式调用了基类的构造函数，不需要使用域操作符：Base1::Base1(a)*/ {
            std::cout << "Derive1 ctor is called.\n";
        }
    };

}

using namespace inheritance2;

int main() {
    Derive d;//先构造Base，再构造Derive。因为Derive **是一个** Base
    d.fun();
    std::cout << d.val << std::endl;

    Derive1 d1(3);

}
