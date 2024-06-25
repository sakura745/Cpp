#include <iostream>

namespace inheritance {
    struct Base2 {
        void fun() {}
    };
    class Derive2 : public/*需要public的话，要写出public。class缺省是private */ Base2 {};

    class DDDDerive;//类的声明
    //class DDDDerive : public Base;//illegal 不是类的声明


    struct Base {
        void fun() {}
    };
    struct subBase : Base {};
    struct Derive : public/*public可写可不写，struct缺省是public*/ subBase {
        void fun2() {}
    };
    struct DDerive : public subBase {};


    struct Base3 {
    //给Base3自己使用，维护一些中间状态
    private:
        void fun() {}

    //给公共成员使用的
    public:
        void ffun() {}

    //除了自己，继承也可以使用
    protected://可以在基类或者派生类使用。就是protected = private + 派生
        void fffun() {}
        int x;//数据成员也成员函数一样的权限
    };
    class Derive3 : public Base3 {
    public:
        void fun2() {
//            fun();//illegal。也不能调用父类（基类）私有成员
            ffun();//legal。 可以调用父类（基类）公有成员。继承引入是一个关系：Derive3是一个Base3，所以可以访问
            fffun();//legal。可以调用父类（基类）保护成员。可以在派生类调用
        }
    };
}

using namespace inheritance;

int main() {
    //不是同一类型，不能引用或指向
//    int x;
//    double& reff = x;//illegal
//    double* ptrr = &x;//illegal

    //但基类的指针或引用可以指向派生类对象，表示**是一个**。即使是两层派生：Base -> subBase -> Derive
    //Derive类型 是一个 Base类型
    Derive d;
    Base& ref = d;
    Base* ptr = &d;
    Base b = d;//存在派生到基类的隐式转换

    //反过来不行。不满足**是一个**的关系
//    Base bb;
//    Derive& rref = bb;//illegal
//    Derive* pptr = &bb;//illegal

    //静态类型：编译器可以确定的类型
    int x1 = 3;//x1的静态类型为int
    //ref的静态类型为Base&

    //动态类型：运行器实际赋予的类型
    //因为ref是绑定在类型为Derive的d上，ref的动态类型是Derive&
    //ptr的动态类型为Derive*

    //用ref访问Derive中的fun2()可以吗？不可以，因为编译器会报错，编译器只看静态类型
//    ref.fun2();//illegal

    DDerive dd;
    ptr = &dd;//ptr动态类型变成DDerive*
    //动态类型可以改变

    Base3 b;
//    b.fun();//illegal. fun()是private只能在Base3内部调用
    b.ffun(); //legal.
//    b.fffun();//illegal. fffun()是protected不能在Base3外部调用

    Derive3 d2;
    d2.ffun();//继承引入是一个关系：Derive3是一个Base3，所以可以访问
//    d2.fffun();//fffun()是protected不能在Base3外部调用

    Derive3 d3;
    d3.fun2();//legal. public
    d3.ffun();
//    d3.fffun();//illegal. protected里的private权限

    //基类和派生类的访问权限通常设置一致

}