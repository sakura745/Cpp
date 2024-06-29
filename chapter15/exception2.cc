#include <iostream>

struct Str {
    Str() { throw 100;}
};
struct Str2 {
    ~Str2() {
        std::cout << "Str2::~Str2 is called.\n";
    }
};

class Cla {
public:
/*    Cla() {
        //想要在缺省构造中捕获异常，但是异常是在m_mem初始化的时候抛出的，
        //构造函数体中的不是初始化，是赋值。因此不能捕获
        try {
        } catch (int) {
            std::cout << "Exception is caught at Cla::Cla.\n";
        }
    }*/
    //想要初始化捕获。如下修改：这种写法叫做function-try-block
    Cla()
    try : m_mem()  {
    //": m_mem()" 也可以不写 以初始化来捕获，那try和ctor共享'{}'
    // try { //cla ctor body
    } catch (int) {
        std::cout << "Exception is caught at Cla::Cla.\n";
    }

private:
    Str m_mem;

};

//function-try-block 作用在一般函数上
void fun()
try {
    throw 123;
} catch (...) {
    std::cout << "Catch exception 123.\n";
}

void fun(Str x)
try {
    throw 123;
} catch (...) {
    std::cout << "Catch exception fun(Str{}).\n";
}


class Cla2 {
public:
    Cla2()
    try {
    } catch (int) {
        std::cout << "Exception is caught at Cla2::Cla2.\n";
    }
    ~Cla2() {
        std::cout << "Cla2::~Cla2 is called.\n";
    }
private:
    Str2 m2_mem;
    Str m_mem;
};


int main() {
    try {
        Cla obj;
    } catch (int) {
        std::cout << "Cla exception is caught at main().\n";
    }
    //输出 Exception is caught at Cla::Cla.
    //     Exception is caught at main().
    //而不是只有Exception is caught at Cla::Cla. 在构造函数中抛出异常，表示构造失败，Cla obj; obj的行为不可知，因此
    //需要在构造之后还抛出异常，相当于构造函数中的try-block的catch中隐式加入throw;
    //catch(int) { //.... throw;}，这是c++标准规定的


    fun();

//    fun(Str{});//还是会报terminate异常，表示Str{}异常不会被fun中的try捕获，当然了。因此Str{}的异常是构造本身出现的，
    //而不是调用Str{}出现的。想要捕获，有如下：
    try {
        fun(Str{});
    } catch (...) {
        std::cout << "Catch exception fun(Str{}) in main.\n";
    }
    std::cout << "---------------------------------" << std::endl;

    try {
        Cla2 obj2;//Str2{}已经构造了。再构造Str{}，抛出异常，通过栈展开，销毁Str2{}，调用Str2的析构函数
        //但是Cla2的析构函数没有调用，因为Cla2的对象没有初始化完成就抛出异常，当然不会调用析构函数了
    } catch (...) {
        std::cout << "Cla2 exception is caught at main().\n";
    }
}