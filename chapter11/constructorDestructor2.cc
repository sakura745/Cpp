#include <iostream>
#include <string>

struct Str {
    explicit/*不允许单一构造函数用来隐式类型转换*/ Str(int x)
        : val(x)
    {}
private:
    int val;
};
void fun(Str m) {

}
struct Str2 {
    Str2() = default;
    Str2(const Str2&/*传入原有的对象，构造一个新的对象。这种复制关系，构成了拷贝。复制的本质就是调用拷贝构造函数*/ x)
     : val/*新对象的val*/(x.val/*原有对象对应的val*/){//拷贝构造函数
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
        , a(std::move(x.a)) {

    }
    void fun() {
        std::cout << val << ' ' << a << std::endl;
    }
private:
    int val = 3;
    std::string a = "asdasd";
};

struct Str4 {
    Str4() = default;
    Str4(const Str4&) {
        std::cout << "Str4's copy constructor is called!" << std::endl;
    }
/*    Str4(Str4&&) noexcept {
        std::cout << "Str4's move constructor is called!" << std::endl;
    }*/
};
struct Str5 {
    Str5() = default;
    Str5(const Str5&) = default;
    Str5(Str5&&) noexcept /*不会抛出异常*/= default;
    //如果对于Str4 有移动构造函数，那么 Str5(Str5&&)声明noexcept没有问题；但是当Str4没有移动，有拷贝时，如果拷贝抛出异常
    // Str5(Str5&&)还声明noexcept 则系统会崩溃
private:
    int val;
    std::string s;
    Str4 m_str4;
};
int main() {
    //单一构造函数就视为类型转换。隐式 显式
//    Str m1 = 3;//单一构造函数可以这么用。可以看成int -> Str的隐式类型转换。但explicit 不允许。
//    fun(3);//illegal

    //explicit可以写
    Str m(3);
    Str m1{3};
    Str m2 = (Str)3;
    Str m3 = Str(3);
    fun(Str(3));
    fun((Str)3);
    Str m4 = static_cast<Str>(3);

    Str2 m5;
    Str2 m6 = m5;//因为是拷贝初始化，所以会调用拷贝构造函数
    Str2 m7(m5);//调用拷贝构造函数
    Str2 m8{m5};//调用拷贝构造函数

    Str3 m9;
    Str3 m10 = m9;

    //c98拷贝
    std::string ori("abc");
    std::string newStr = ori;
    std::cout << newStr << std::endl << ori << std::endl;

    //c11移动。不关心ori1，把ori1赋给newStr1
    std::string ori1("abc");
    std::string newStr1 = std::move(ori1);//构造了一个右值，其实是将亡值。使用了string的移动构造函数
    std::cout << newStr1 << std::endl << ori1 << std::endl;

    Str3 m11;
    m11.fun();
    Str3 m12 = std::move(m11);
    m11.fun();
    m12.fun();

    Str5 m13;
    Str5 m14 = std::move(m13);//Str4只有拷贝构造函数，没有移动构造函数。Str5的移动构造函数在处理时，会调用了Str4的拷贝构造函数
    //Str4有移动，则不会调用拷贝构造函数

}