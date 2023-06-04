#include <iostream>
#include <memory>

namespace virtualFunction2 {
    class Base {
    public:
        virtual void fun(int x = 3000) {
            std::cout << "Base: " << x << std::endl;
        }
    };
    class Derive : public Base {
    public:
        void fun(int x = 4) override final/*告诉编译器，fun()不会再override，这是最终版。编译器会优化vtable，提升性能*/ {
            std::cout << "Derive: " << x << std::endl;
        }
    };
    void proc(Base& b) {
        b.fun();
    }
    void proc1(Base b) {
        b.fun();
    }

    class Base2 {
    public:
        virtual void fun(int x = 3000) {
            std::cout << "Base2: " << x << std::endl;
        }
    };
    class Derive2 final/*这个类所有的虚函数都为final，不会再派生类*/ : public Base2 {
    public:
        void fun(int x = 4) override {
            std::cout << "Derive2: " << x << std::endl;
        }
    };


    class Base3 {
    public:
        Base3() {
            fun();
        }
        virtual void fun() {
            std::cout << "Base3" << std::endl;
        }
    };
    class Derive3 final : public Base3 {
    public:
        Derive3() : Base3() {
            fun();
        }
        void fun() {
            std::cout << "Derive3" << std::endl;
        }
    };

    class Base4 {
    public:
        ~Base4() {
            std::cout << "~Base4()\n";
        }

    };
    class Derive4 final : public Base4 {
    public:
        ~Derive4() {
            std::cout << "~Derive4()\n";
        }
    };

    class Base5 {
    public:
        virtual ~Base5() {
            std::cout << "~Base5()\n";
        }

    };
    class Derive5 final : public Base5 {
    public:
        ~Derive5()/*会继承基类析构函数的特性，也为虚函数*/ {
            std::cout << "~Derive5()\n";
        }
    };

    class Base6 {
    public:
        virtual ~Base6() = default;//就是为了把析构函数设置为virtual函数
    };
    class Derive6 final : public Base6 {
    public:
        ~Derive6() {}
    };

    class Base7 {
    protected:
        virtual void fun() {
            std::cout << "Base7"<< std::endl;
        }
    };
    class Derive7 : public Base7 {
    public:
        void fun() override final {
            std::cout << "Derive7" << std::endl;
        }
    };
}
using namespace virtualFunction2;

int main() {
    Derive d;
    proc(d);//输出为 Derive: 3000。虚函数的缺省实参只会考虑静态类型，d的静态类型为Base。在编译期，proc函数的行为变成
    //b.fun(3000)。所以输出为 Derive: 3000。

    proc1(d);//输出为 Base: 3000。构造Derive之前，先构造Base，构造Base时，Base内所有的虚函数都只有Base内定义。构造
    //完Base后，再构造Derive，会把原来指向Base内虚函数的指针，指向为Derive内的虚函数。当proc1()传入Derive类型，会有一个
    //Derive到Base的隐式转换。当然就输出Base内的虚函数了。
//    Base tmp = d;//legal : Derive到Base的隐式转换
    //为什么proc()形参为Base&或Base*就可以呢？指针指向的内存，就是对象，类型就是Derive类型，当然就调用Derive内的虚函数了
    //引用的底层也是指针。

    Derive3 d3;//输出为Base3 Derive3。构造Derive3对象，执行到Derive3的构造函数之前，要先构造Base3。执行Base3的构造函数，
    //当Base3()这一行代码构造完，Base3已经通过缺省的方式初始化完毕，相应的编译器会构造vtable，vtable中所有的虚函数都指向
    //Base3中的定义。之后，会调用Base3构造函数内的fun()，所以先输出 Base3。在构造Base3完成之后，才会对Derive3通过Base3来
    //完成初始化列表 Derive3() : Base3()，Derive3所有函数都初始化完毕，vtable中的fun()由Base3指向了Derive3版本，所以会输
    //出Derive3

//    Derive4* d4 = new Derive4();
//    delete d4;
    //先输出~Derive4() 再输出~Base4()，先构造的后析构


    //行为未定义（析构函数不是虚函数）
    Derive4* d5 = new Derive4();
    Base4* b4 = d5;
    delete b4;
    std::shared_ptr<Base4> ptr(new Derive4());
    std::unique_ptr<Base4> ptr2(new Derive4());

    //行为确定（析构函数为虚函数）：先输出~Derive5() 再输出~Base5()，先构造的后析构。
    Base5* b5 = new Derive5();
    delete b5;
    std::shared_ptr<Base5> ptr3(new Derive5());
    std::unique_ptr<Base5> ptr4(new Derive5());
    //删除逻辑 对应vtable构造的顺序。Derive5构造的对象，动态类型是Derive5，析构Derive5()，c++规定，调用完派生类析构函数，
    //再调用基类析构函数
    //让上述行为确定的，是通过将基类析构设置为虚函数。上述什么行为：是通过基类的指针来删除派生类的对象。
    //换句话说：基类析构函数为虚函数是“通过基类的指针来删除派生类的对象”的情况下设置的。

    Derive7 d6;
    d6.fun();
    Base7& b7 = d6;
//    b7.fun();//illegal。 动态绑定属于运行期行为。权限属于编译期行为，由于b7的静态类型为Base7& Base7中没有fun()的访问权
    //限

}