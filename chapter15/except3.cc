#include <iostream>

void fun() throw()/*c98写法，不会抛出异常*/{

}
void fun2() noexcept/*限定符*/ /*c11写法，不会抛出异常*/{
}
void fun3() noexcept(false)/*c11写法，会抛出异常*/{
}
void fun4() /*noexcept(false)*/ {
}
void foo() noexcept/*限定符*/(noexcept/*操作符*/(fun3()) && noexcept(fun2())) /*fun2 和 fun3都不会抛出异常时，foo不抛出异常*/{
    fun2();
    fun3();
}

void fooo() noexcept(true) {
    throw 1;
}

//可以编译，对于noexcept是兼容的
class Base {
public:
    virtual void fun_() noexcept(false)
    {}
};

class Derive : public Base{
public:
    void fun_() noexcept override
    {}
};

//编译报错，对于noexcept是不兼容的
/*class Base2 {
public:
    virtual void fun_() noexcept
    {}
};

class Derive2 : public Base2{
public:
    void fun_() noexcept(false) override
    {}
};*/

int main() {
    std::cout << noexcept/*操作符*/(fun2()) << std::endl;
    std::cout << noexcept(fun3()) << std::endl;

//    fooo();//声明了noexcept函数中抛出异常，会导致terminate被调用。是运行错误，而不是编译错误

//    try {
//        fooo();
//    }
//    catch (...) {
//        std::cout << "Exception is caught.\n";
//    }
    //还是会调用terminate。因为函数声明时已经说明noexcept，就不会栈展开，但是还是抛出异常，直接在调用fooo时直接调用terminate
    //修改：可将noexcept(true)去掉。noexcept是个约定，只要违反了noexcept，抛出了异常，c++就会终止程序，没有阻止终止程序的手段。


    //函数指针
    void (*ptr)()/*不一定会不会抛出异常*/ = fun2/*不会抛出异常，因为noexcept限定了*/;//形式上的兼容性
    (*ptr)();

    void (*ptr2)() noexcept/*不会抛出异常*/ = fun2;//形式上的兼容性

//    void (*ptr3)() noexcept = fun4;//illegal 形式上不兼容，不知道fun4是否会抛出异常，但(*ptr3)()不会抛出异常
    //兼容：从上往下可以，从下往上不可以。上一级要对异常有较好的处理方式

}