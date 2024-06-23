#include <iostream>
#include <string>
namespace ctordtor2 {
    struct Str {
        explicit/*不允许单参构造函数用来隐式类型转换*/ Str(int x)
                : val(x) {}

    private:
        int val;
    };
    void fun(Str m) {}

    struct Str2 {
        Str2() = default;

        Str2(const Str2&/*传入原有的对象，构造一个新的对象。这种复制关系，构成了拷贝。复制的本质就是调用拷贝构造函数*/ x)
                : val/*新对象的val*/(x.val/*原有对象对应的val*/) {//拷贝构造函数
            std::cout << "Copy constructor is called~" << std::endl;
        }

    private:
        int val = 3;
    };

    struct Str3 {
        Str3() = default;

        Str3(const Str3&) = default;

        Str3(Str3&&/*右值引用*/ x)//移动构造函数
                : val(x.val)//内建类型拷贝和移动的成本一样，所以移动就是拷贝
                , a(std::move(x.a))
        {}
        //右值引用对象作为表达式时是左值，是为了确保在不同的情况下的语义一致性
        void fun() {
            std::cout << val << ' ' << a << std::endl;
        }

    private:
        int val = 3;
        std::string a = "Str3 test~";
    };

    struct Str4 {
        Str4() = default;

        Str4(const Str4&) {
            std::cout << "Str4's copy constructor is called!" << std::endl;
        }
/*
        Str4(Str4&&) noexcept {
            std::cout << "Str4's move constructor is called!" << std::endl;
        }
*/
    };

    struct Str5 {
        Str5() = default;

        Str5(const Str5&) = default;

        Str5(Str5&&) noexcept /*不会抛出异常*/= default;
        //如果对于Str4 有移动构造函数，那么 Str5(Str5&&)声明noexcept没有问题；
        // 但是当Str4没有移动，有拷贝时，如果拷贝抛出异常
        // Str5(Str5&&)还声明noexcept 则系统会崩溃
        ///就是说如果Str4没有移动构造函数，那Str5移动构造函数的noexcept就要考虑是否使用了
    private:
        int val;
        std::string s;
        Str4 m_str4;
    };
}
using namespace ctordtor2;
int main() {
    //单参构造函数可以视为隐式类型转换。
//    Str m1 = 3;//单一构造函数可以这么用。使用赋值运算符来初始化是单参的特性用来仿照类型转换int a = 3.1; double->int
    //可以看成int -> Str的隐式类型转换。但使用 explicit 不允许转换。
//    fun(3);//illegal 同理

    //无论是否有explicit都可以写
    Str m(3);
    Str m1{3};
    Str m2 = (Str)3;
    Str m3 = Str(3);
    Str m4 = static_cast<Str>(3);
    fun(Str(3));
    fun((Str)3);
    fun(static_cast<Str>(3));
    std::cout << "----------------------" << std::endl;

    Str2 m5;
    Str2 m6 = m5;//因为是拷贝初始化，所以会调用拷贝构造函数。准确的说：拷贝初始化调用拷贝函数
    Str2 m7(m5);//调用拷贝构造函数。准确的说：直接初始化调用拷贝函数
    Str2 m8{m5};//调用拷贝构造函数
    std::cout << "----------------------" << std::endl;

    Str3 m9;
    Str3 m10 = m9;

    //c98拷贝
    std::string ori("ori_string");
    std::string newStr = ori;
    std::cout << ori << "#" << newStr << std::endl;

    //c11移动。不关心ori2，把ori2赋给newStr2
    std::string ori2("ori2_string");
    std::string newStr2 = std::move(ori2);//构造了一个右值，其实是将亡值。使用了string的移动构造函数
    std::cout << ori2 << "#" << newStr2 << std::endl;

    Str3 m11;
    m11.fun();
    Str3 m12 = std::move(m11);
    m11.fun();
    m12.fun();
    std::cout << "----------------------" << std::endl;

    Str5 m13;
    Str5 m14 = std::move(m13);
    //Str4只有拷贝构造函数，没有移动构造函数。Str5的移动构造函数在处理时，会调用了Str4的拷贝构造函数
    //Str4有移动，则不会调用拷贝构造函数
    ///就是说当移动操作发生时，如果没有移动构造函数，则会使用拷贝构造函数

}