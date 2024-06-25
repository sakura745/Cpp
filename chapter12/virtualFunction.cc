#include <iostream>

namespace virtualFunction {
    class Base {
    public:
        virtual void baseMethod() {}
        int baseMember;
    };
    class myClassDerived : public Base {
    public:
//        virtual void derivedMethod() {}
        int derivedMember;
    };
    class myClassDerived2 : public myClassDerived {
    public:
//        virtual void derivedMethod2() {}
        int derivedMember2;
    };


    class BBase {
    public:
//        virtual void baseMethod() {}
        int baseMember;
    };
    class mmyClassDerived : public BBase {
    public:
        virtual void derivedMethod() {}
        int derivedMember;
    };
    class mmyClassDerived2 : public mmyClassDerived {
    public:
//        virtual void derivedMethod2() {}
        int derivedMember2;
    };


    class Base2 {
    public:
        virtual void fun() {
            std::cout << "Base2::fun() is called.\n";
        }
    };
    class Derive2 : public Base2 {
    public:
        void fun() {//基类的虚函数被再派生类重写 override：函数签名void fun()保持不变，但有个例外
            std::cout << "Derive2::fun() is called.\n";
        }
    };

    void proc(Base2& b) {
        b.fun();
    }

    //签名会改变的唯一例外
    class Base3 {};
    class Derive3 : public Base3 {};
    class Base4 {
    public:
        virtual Base3& fun() {
            std::cout << "Base4::fun() is called.\n";
            static Base3 base3;
            return base3;
        }
    };
    class Derive4 : public Base4 {
    public:
        Derive3& fun() {//基类虚函数在派生类重写，函数签名改变了。由Base3& 变为 Derive3&。或由Base3* 变为 Derive3*。这是唯一的例外
            std::cout << "Derive4::fun() is called.\n";
            static Derive3 deri3;
            return deri3;
        }
    };

    class Base5 {//只要包含了纯虚函数的基类就叫抽象基类
    public:
        Base5() = default;
        virtual void fun() = 0/*纯虚函数*/;
        //通常纯虚函数不给定义。只是为了建立个vtable，给出了抽象接口：目的是让其在派生类给出具体的实现
        //比如说有Right Triangle **is a** Triangle，**is** also **a** Shape。直角三角形可以定义一个具体函数draw()，
        //用来画出形状，三角形也可以用函数draw()来画出形状，但Shape不能用函数draw()来画出形状，只能在Shape中定义一个
        //纯虚函数，来抽象给出一个接口，给其派生类（Triangle、Right Triangle）使用。必须在基类中定义draw()，才能实现多态
    };
    class Derive5 : public Base5 {
    public:
        void fun() {
            std::cout << "Derive5::fun() is called.\n";
        }
    };
    class Derive5_1 : public Base5 {
        void fff() {}
    };

    class Base6 {
    public:
        virtual void fun() = 0;
    };
    class Derive6 : public Base6 {
    public:
        void fun() {
            std::cout << "Derive6::fun() is called.\n";
        }
    };
    class Derive6_1 : public Derive6 {};

    class Base7 {
    public:
        virtual void fun() = 0;//纯虚函数可以给定义，但是不能类内定义，只能类外定义
    };
    void Base7::fun() {//纯虚函数的定义意义不大，只是从底层上可以有定义。但是仍改变不了Base7是抽象基类的特性。
        std::cout << "Base7::fun() is called.\n";
    }
    class Derive7 : public Base7 {
    public:
        void fun() {
            Base7::fun();
            std::cout << "Derive7::fun() is called.\n";
        }
    };


    class Base8 {
    public:
        virtual void fun() {
            std::cout << "Base8::fun() is called.\n";
        }
    };
    class Derive8 : public Base8 {
    public:
        void fun() {
            std::cout << "Derive8::fun() is called.\n";
        }
    };
    class Derive8_1 : public Derive8 {
    public:
        void fun() {
            std::cout << "Derive8_1::fun() is called.\n";
        }
    };


    class Base9 {
    public:
        virtual void fun() {
            std::cout << "Base9::fun() is called.\n";
        }
    };
    class Derive9 : public Base9 {
    public:
        void fun() override/*当对虚函数因各种原因重写失败时，会主动报错*/ {
            std::cout << "Derive9::fun() is called.\n";
        }
    };

}
using namespace virtualFunction;

int main () {
    myClassDerived2 d;

    //是因为继承
    Base& ref = d;
    Base* ptr = &d;

    //是因为virtual，多态
    //把基类的引用转换为派生类的引用
    myClassDerived2& d2 = dynamic_cast<myClassDerived2&>(ref);
    //把基类的指针转换为派生类的指针
    myClassDerived2* ptr2 = dynamic_cast<myClassDerived2*>(ptr);
    //支持上述类型转换，是因为基类引入了动态类型信息typeinfo，typeinfo是vtable定义的，vtable是因为定义了virtual函数。
    //vtable、typeinfo和操作都是通过指针来完成的
    //所以支持上述类型转换，是因为virtual函数引入。"virtual"去掉，error : source type is not polymorphic.
    //只要**基类**没有vtable，不支持动态类型转换。强调的基类，如果派生类 virtual去掉，还是可以动态类型转换

    //可以将mmyClassDerived引入virtual，mmyClassDerived2就可以转换；或者BBase有虚函数也可以
    mmyClassDerived2 dd;
    mmyClassDerived& rref = dd;
    mmyClassDerived* pptr = &dd;
    mmyClassDerived2& dd2 = dynamic_cast<mmyClassDerived2&>(rref);
    mmyClassDerived2* pptr2 = dynamic_cast<mmyClassDerived2*>(pptr);

    //ptr转化成ptr2，pptr转化成pptr2：基类的指针转化为派生类指针，如果基类指针当初指的是派生类的地址，
    //则指针转化成功；否则转换后的指针指向nullptr
    //ref转化成d2，rref转化成dd2：基类的引用转化为派生类，如果基类引用当初绑定在派生类上，
    //则引用转化成功；否则转换后的引用会抛出异常
    //dynamic_cast 是运行期转换，需要相对较多的时间和资源。慎用！

    Derive2 d3;
    d3.fun();
    Base2& b2 = d3;
    b2.fun();//输出为"Derive2::fun() is called."。如果把Base2中的virtual去掉，输出"Base2::fun() is called."
    //没有vtable。所有调用都是在编译期被绑定，只看静态类型。不能调用派生类的函数

    Derive2 d4;
    proc(d4);//输出：Derive2::fun() is called.
    Base2 b4;
    proc(b4);//输出：Base2::fun() is called.
    //相当于用一个函数proc()，实现了实参类型不同，表现了不同的行为。这个功能叫动态多态（运行器多态）：通过动态类型实现的
    std::cout << "-----------------" << std::endl;

    Derive5 d5;
    Base5& b5 = d5;
    b5.fun();
//    Base5 b6;//illegal
    //不能声明抽象基类的对象，有缺省构造函数也不行
    //但可以声明指针、引用:上面这个 Base5& b5 = d5; 就是

//    Derive5_1 d5_1;//illegal. 因为Derive5_1，派生于Base5，只要没有对基类中的纯虚函数重写override，Derive5_1也被视为抽象基类。
    //不能声明抽象基类的对象
    //如果Base5中有100个纯虚函数，Derive5_1想要声明对象，要对Base5中的所有纯虚函数进行一一重写(override)

    //Base6是抽象基类，Derive6派生于Base6，对纯虚函数有override，
    //Derive6_1派生于Derive6，没有对纯虚函数的override。但仍可以声明对象
    Derive6_1 d6;//抽象类不能传递，只能影响一层继承
    //说明对于Derive6_1来继承自上一层类Derive6，Derive6是具体的类（不是抽象基类），因此Derive6_1可以正常使用
    //只要是继承于具体的类就行。不用关心继承类Derive6的上一层继承类Base6是什么。
    std::cout << "----------------" << std::endl;

    Derive7 d7;
    Base7& b7 = d7;
    b7.fun();

    //如果想要纯虚函数也输出内容呢，可以在派生类override的函数体中给出Base7::fun();
    //可以在纯虚函数中定义输出一些辅助逻辑，再通过上述方法让辅助逻辑在派生类实现开头调用

    //Base8中声明了fun()为虚函数，在Derive8和Derive8_1中fun()不用virtual关键字，fun()仍然还是虚函数
    //因为在声明了虚函数，会生成对应的vtable，vtable中会有fun()的记录

    Derive9 d9;
    Base9& b9 = d9;
    b9.fun();

}