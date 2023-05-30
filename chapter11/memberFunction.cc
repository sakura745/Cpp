#include <iostream>
#include <vector>

struct Str {//引入成员函数之后的结构体，本质上变成类
    int x = 3;
    void fun() {//c++的方法，放到结构体内部
        std::cout << x << std::endl;
    }
};
void fun(Str obj) {//c语言的方法
    std::cout << obj.x << std::endl;
}
//将struct变为class
class Str1 {
public://struct中默认访问类型为public，class中默认访问类型为private，所以完全转换要表明public
    inline static int x = 3;
    void fun() {//类内定义 隐式内联
        std::cout << x << std::endl;
//        std::cout << this->x << std::endl;//legal，与上一行等价
    }
};

struct Str2 {//由于两遍处理，legal
    using MyRes = int;
    MyRes fun() {
        return x;
    }
    int x;
};
//当成员函数是类外定义的话，对于MyRes fun()来说，既fun()需要使用 域操作符，函数返回类型也要使用 域操作符
//Str2::MyRes Str2::fun() {//...}，但是这么写需要些两遍Str2::。可以使用trail returnint type，改为
//auto Str2::fun() -> MyRes {//...}

//illegal。因为第二遍处理的是函数定义
/*struct Str3 {
    MyRes fun() {
        return x;
    }
    using MyRes = int;
    int x;
};*/

class Str3 {
public:
    int x = 3;
    void fun(/*Str3* const this 隐藏的参数，this 的类型是 Str* const。   */) {
        std::cout << this << std::endl;
    }
};
class Str4 {
public:
    int x = 3;
    void fun(int x) {
        std::cout << x << std::endl;//fun也形成个域，域内单独的x
        std::cout << Str4::x << std::endl;//访问fun外的x
        std::cout << this->x << std::endl;//访问fun外的x
    }
};
class Str5 {
public:
    int x = 3;
    void fun() {
        this->x = 100;//this类型是 Str5 * const，指针不能修改，但可以修改指针指向的内容
    }
    void fun() const/*c98*/{//this指针类型变成 const Str5* const 都不能修改
        //this->x = 100;//illegal
        //不希望通过this指针来修改内部的数据成员
    }//这两个都是函数除了const都一样，可以通过const来重载。
    //为什么可以重载了，因为这两个函数对应的this指针的类型不同
};

struct  Str6 {
    static void fun() {
//        std::cout << x << std::endl;//illegal: Invalid use of member 'x' in static member function
    }
    int x;
};
struct  Str7 {
    static void fun() {
        static int x;//就不是静态数据成员，而是局部静态变量。生存周期是从首次调用fun开始，一直到整个程序结束
    }
};

struct  Str8 {
    static auto& size() {
        return x;
    }
    inline static std::vector<int> x;//生命周期是程序启动就有，生命周期与程序生命周期相同
};
//Str8 中x的生命周期比Str7的长，没有Str7的好

struct Str9 {
    static auto& instance() {//不会影响Str9的大小
        static Str9 x;
        return x;
    }
    //ChatGPT：
    //属于典型的单例模式：单例模式是一种创建模式，它确保一个类只有一个实例对象，并提供一个全局访问点以便其他类
    //可以访问该实例。在单例模式中，类的构造函数是私有的，因此无法从外部直接创建类的对象。该类会定义一个静态方
    //法或变量来访问唯一的对象实例，这个静态方法或变量会检查是否已经创建了对象，如果已经创建了对象就会返回这个
    //唯一的对象，如果还没有创建对象，则创建它并返回它的引用。单例模式常用于一些需要共享资源或状态信息的场景，
    //例如：线程池、缓存、配置文件等。由于单例模式可以在全局范围内访问该实例，因此它是一种非常便捷和可靠的解决方案。
};

//struct some_type {
//    void foo() &/*c11*/;//& 左值引用
//    void foo() &&/*c11*/; //&& 右值引用
//    void foo() const &/*c11*/;//const& 常量左值引用
//    void foo() const &&/*c11*/;//const&& 常量右值引用
//    //左值、右值引用是谁的性质。是调用对象的性质
//};
//c98提出的const限定符重载和c11提出的引用限定符重载，不能混用。就是说有一个使用了&，就都要使用&来重载

int main() {
    Str m_str;
    fun(m_str);//c语言的方法
    m_str.fun();//c++的方法

    Str1 m_str1;
    m_str1.fun();
    std::cout << Str1::x << std::endl;
    std::cout << "---------------------" << std::endl;

    Str1 m_str11;
    m_str11.x = 4;
    m_str11.fun();

    Str1 m_str22;
    m_str22.x = 5;
    m_str22.fun();

    //编译器怎么知道m_str11.fun();中fun的x是4，m_str22.fun();中fun的x是5？
    //会引入一个this指针，指向了当前的对象
    Str3 m_str111;
    std::cout << &m_str111 << std::endl;
    m_str111.fun();//fun(&m_str111)

    Str3 m_str222;
    std::cout << &m_str222 << std::endl;
    m_str222.fun();

    Str4 m_str4;
    m_str4.fun(8);

    Str6::fun();//调用静态成员函数，与静态数据成员一样
    //静态成员函数的作用是什么？
    //描述和类紧密相关的函数，又不需要一般的数据成员

//    some_type t;
//    t/*左值*/.foo();//左值引用
//    some_type()/*右值*/.foo();//右值引用
//    const some_type t1;
//    t1.foo();//常量左值引用
//    //右值：是希望可以修改的值。常量右值，没太大意义

}