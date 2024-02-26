#include <iostream>
#include <vector>
#include <utility>

//类模板的定义
template <typename T>
class B {
public:
    void fun(T input) {//类模板成员函数的类内定义
        std::cout << input << std::endl;
    }
    auto fun1() {
        return B<int>{};//可以简写为B{};
    }
    auto fun2() {
        return B{};
    }
    void fun3();//类内成员函数的声明
private:
    //友元函数模板
    template <typename T2>
    friend void fun4();

    //惯用法：
    friend void fun5(B input) {//B是一个类型信息，全称为 B<T>
        std::cout << input.val << std::endl;
    }

    friend auto operator + (B input1, B input2) {
        B res;
        res.val = input1.val + input2.val;
        ///虽然gcc可以通过编译，但不是一个安全的行为。当模板被实例化为非float类型，B<float> 类型不是非float类型的友元函数
//        B<float> tmp;
//        tmp.val;

        return res;
    }

    //c11之后，声明模板参数为友元
    friend T;

    int val = 123;
};
template <typename T2>
void fun4() {
    B<int> tmp;
    tmp.val;

    B<char> tmp2;
    tmp2.val;
}

//类模板成员函数的类外定义
template <typename T>
void B<T>::fun3() {

}

//类模板的声明
template<typename T>
class B;

struct Str{};

class B2 {
public:
    //类(B2)的成员函数模板 的类内定义
    template<typename T>
    void fun() {
    }

    //类成员函数模板的声明
    template<typename T>
    void fun2();
};
//类(B2)的成员函数模板的类外定义
template<typename T>
void B2::fun2() {
}

template <typename T>
class B3 {
public:
    //类模板的成员函数模板 的类内定义
    template<typename T2>
    void fun() {
        T2 tmp1;
        T tmp2;
    }

    //类模板的成员函数模板的声明
    template<typename T2>
    void fun2();
private:
    T m_data;
};
//类模板的成员函数模板 的类外定义
template <typename T>//对应类模板
template <typename T2>//对应类模板内的函数模板
void B3<T>::fun2() {}

namespace N {
    template<class T>
    class Y {//类模板定义
        void mf() {}
    };
}
using N::Y;

template
class N::Y<char*>;//对所有成员函数实例化

template
void N::Y<double>::mf();//只会实例化mf()这一个成员函数

template <class T>
class B4 {
public:
    void fun() {
        std::cout << "B4's Any types.\n";
    };
};
//类模板的完全特化
template <>
class B4<int> {
public:
    void fun() {//甚至可以改成fun1()（函数模板的特化，函数名不可以改），就是说特化版本与基础版本可以拥有完全不同的实现
        std::cout << "B4's Int types.\n";
    };
};

template <class T1, class T2>
class B5 {
public:
    void fun() {
        std::cout << "B5's Any types.\n";
    };
};
//类模板的偏（部分）特化
template <class T2>
class B5<int, T2> {
public:
    void fun() {
        std::cout << "B5's Int and else types.\n";
    };
};


template <class T>
class B6 {
public:
    void fun() {
        std::cout << "B6's Any types.\n";
    };
};
//类模板的偏（部分）特化：一般类型是调用输出B6's Any types，指针类型调用B6's pointer types
template <class T>
class B6<T*> {
public:
    void fun() {
        std::cout << "B6's pointer types.\n";
    };
};

template <class T>
class B7 {
public:
    B7(T input) {}
};


template <class T>
class B8 {
public:
    B8(T input) {}

    //用户自定义：通过迭代器
    template<class T2>
    B8(T2 beg, T2 end) {};
};
template<class T2>
B8(T2 beg, T2 end) -> B8<typename std::iterator_traits<T2>::value_type>;


template <typename T1, typename T2>
std::pair<T1, T2> make_pair(T1 val1, T2 val2) {
    return std::pair<T1, T2>(val1, val2);
}
int main() {
    B<int> x;//实例化
    B<char> y;
    x.fun(3);
    x.fun1();

    B<Str> z;//legal
//    z.fun(Str{});//illegal 没有重载 << 操作符
    //上述说明了：只有成员函数被调用的时候，才会实例化：fun()。

    z.fun1();
    z.fun3();

    B2 x2;
    x2.fun<int>();

    B3<int> x3;//T -> int
    x3.fun<float>();// T2 ->float

    fun4<double>();

    B<int> x4;
    fun5(x4);
    //fun5()依赖于B而存在
    B<char> x5;
    fun5(x5);

    B<int> x6;
    B<int> res = x4 + x6;

    B4<int> x7;
    x7.fun();
    B4<float> x8;
    x8.fun();

    B5<double, char> x9;
    x9.fun();
    B5<int/*必须是int才能调用偏特化中的实现*/, float> x10;
    x10.fun();

    B6<double> x11;
    x11.fun();
    B6<int*> x12;
    x12.fun();


    B7 x13(3);//c17:基于构造函数的实参推导
    B8 x14(7);// T -> int
    std::vector<double> v{1.2, 1234.1, 0.02};
    auto d = B8(v.begin(), v.end());//用户自定义：迭代器。推导出 T -> double

    std::pair<int, double> p{3, 3.14};
    std::pair p2{3, 3.14};//c17可以自动推导
    auto mp = make_pair(3, 2.71828);//c17之前引入的辅助模板推导函数
    //实际上，c++内部的make_pair就是这个按照这个思想来实现的。

}