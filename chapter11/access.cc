#include <iostream>
#include <vector>

//void abc();
class Str {
    friend int main();//可以被认为是函数的首次声明
    friend/*friend是单向的*/ class/*如果友元类声明或定义在该类之前，可以省略；声明定义之后不可以省略*/ Str2;
    //表示Str2是Str的朋友，Str的逻辑下，Str宣布谁是我的朋友。
    //Str2可以访问Str的**任何**数据成员和接口。Str不是Str2的朋友
    //friend关键字 不区分public  private protected
    friend void fun();//可以被认为是函数的首次声明
//    friend void ::abc();//illegal: abc()前加了全局域操作符，说明是全局函数。则该行代码不表示为该函数声明。需要在全局域
    //添加该函数的声明才能通过

    inline static int x;

    //友元类不能在类内定义
    //友元函数可以区分类内定义和类外定义
    friend void fun1(const Str&/*Str&才是友元函数的使用方式*/ val) {//友元函数的类内定义，会产生隐藏友元
    //fun1函数的作用域是什么？
    //一定不是Str内，因为属于Str的友元函数。所以是位于Str外的全局域中
        std::cout << val.y << std::endl;
    }
public:
    int y;
    int z;
};

void fun() {}//友元函数的类外定义，不会产生隐藏友元

class Str2 {
    void fun2() {
        std::cout << Str::x << std::endl;
    }
};

int main() {
    std::cout << Str::x << std::endl;
    fun();
//    fun1();//illegal: 类内定义的友元函数，作用域为类外全局域，但是编译器不会找到。好处是减轻编译器的负担，防止误用
    //怎么解决该问题：类外引入声明或者类外定义；或者通过ADL
    //ChatGPT：ADL是Argument-dependent Lookup的缩写，意为“参数相关查找”。它是一种编程语言特性，常用于C++和D等编程语言中。
    //当使用某个名称作为函数或操作符的参数时，编译器在查找该名称所在的命名空间时会优先查找与参数类型相关联的命名空间。
    //例如，C++ 中的 std::swap 函数可以交换两个变量的值，它接受两个参数并将它们交换。当使用 std::swap 函数时，编译器会首
    //先在当前命名空间中查找是否有该函数的定义，如果没有，它会在参数类型所关联的命名空间中查找。
    //使用ADL可以简化函数调用的代码，并促进代码的重用和扩展。但是它也可能会导致函数查找失败或查找到错误的函数定义，
    //因此应该谨慎使用。
    Str val;
    fun1(val);
    //这才是隐藏友元函数的正确打开方式。因为友元函数的目的就是要访问类的私有数据成员，参数为类的对象都是一切合乎常理的

}
