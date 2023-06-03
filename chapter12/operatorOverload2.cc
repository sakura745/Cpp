#include <iostream>


struct Str {
    Str() = default;
    Str(int* p) : ptr(p) {}

    int&/*为了写操作，所以要是&*/ operator */*一元操作符*/ (/*不写参数，因为有个隐藏参数this*/) {
        return *ptr;
    }

    int operator * () const/*为了const Str对象的只读、不写，而进行重载*/{
        return *ptr;
    }

    Str* operator -> () {
        return this;
    }

    int val = 5;
private:
    int* ptr;
};

struct Str2 {
    Str2* operator -> () {
        return this;
    }
    int bla = 123;
};
struct Str3 {
    Str3() = default;

    Str2 operator -> () {
        return Str2{};
    }
    int val;
};
struct Str4 {
    Str4(int p) : val(p) {}

    int operator() () {//函数调用运算符的重点是构造可调用对象
        return val;
    }
    int operator() (int x, int y, int z) {
        return val + x + y + z;
    }
    bool operator() (int input) {
        return val < input;
    }
private:
    int val;
};
bool fun(int input) {
    return 100 < input;
}

struct Str5 {
    /*explicit*/ Str5(int p) : val(p) {}
    /*explicit*/ operator int/*operator int函数名*/() const/*防止const 类型转化失败*/ {//函数没有返回类型，或者说返回类型已经在函数名中了 int
        return val;
    }
    friend auto operator + (Str5 a, Str5 b) {
        return Str5(a.val + b.val);
    }

    explicit operator bool() const {
        return val == 0;
    }
private:
    int val;
};

struct Str6 {
    explicit Str6(int p) : val(p) {}

    explicit operator bool() const {
        return val == 0;
    }
private:
    int val;
};
struct Str7 {
    Str7(int p) : val(p) {}

    friend bool operator == (Str7 obj1, Str7 obj2) {
        return obj1.val == obj2.val;
    }
    //c20支持隐式交换操作数，因此甚至可以不设置为友元
//    bool operator == (Str7 obj2) {
//        return val == obj2.val;
//    }

    friend bool operator == (Str7 obj1, int x) {
        return obj1.val == x;
    }
//    bool operator == (int x) const{
//        return val == x;
//    }

    auto operator <=> (int x) {
        return val <=> x;
    }
private:
    int val;
};
int main() {
    int x = 100;
    Str ptr(&x);
    std::cout << *ptr << std::endl;
    *ptr = 101;


    Str* pt = nullptr;
    pt->val;
    Str m1;
    m1.val;
    //val不是对象，因为它不能单独使用，不能称之为左值或者右值。需要依附在类型为Str的对象上: pt->val; m1.val;
    //例如重载[]: int& operator [] (int id); id是一个对象，可以作为参数。因此需要特殊处理

    int y = 1000;
    Str m2(&y);
    std::cout << m2->                                 val << std::endl;
    std::cout << m2.operator->/*这是重载的指针*/()   ->/*这个是编译器翻译出来的*/val  /*这是运算符重载函数的全称写法*/ << std::endl;
    //m2.operator->() 表示 m2->，由于m2.operator->()返回类型是指针，所以'val'被翻译为'->val'
    //编译器看到m2->，同时m2是一个Str类型的对象之后。编译器会尝试着找Str的operator->函数，如果找到重载之后，重载函数返
    //回Str对象的**指针**。  Str*，将通过对象的指针来调用val。

    std::cout << ptr.operator*()/*解引用，也可以这么写*/ << std::endl;

    Str3 m3;
    //Str3的对象，访问了Str2的成员
    std::cout << m3->                                                         bla/*Str2的数据成员*/ << std::endl;
    std::cout << m3.operator->()/*Str3的重载*/  .operator->()/*Str2的重载*/   ->bla<< std::endl;
    //编译器看到m3->，同时m3是一个Str3类型的对象之后。编译器会尝试着找Str3的operator->函数，如果找到重载之后，重载函数
    //返回Str3对象，是Str2类型，不是指针类型，会尝试寻找Str2中的operator->函数，直到找到重载函数返回类型为指针为止。
    //递归的操作。可以试着将Str2* 改成其他类型，看看会报什么错
    //所以 operator->() 只能返回两种，一个是当前结构体的指针，一个是另外结构体


    Str4 m4(100111);
    std::cout << m4()/*m4是一个对象，可以用类似函数调用的方式() 调用*/ << std::endl;
    std::cout << m4(1, 3, 412412) << std::endl;
    std::cout << m4(12312312) << std::endl;
    std::cout << m4(123) << std::endl;
    std::cout << fun(123) << std::endl;//但是fun的return 100 < input;中100写死了，比较与Str4，不灵活
    //Str4但是代码过长，所以c11之后引入lambda表达式


    Str5 m5(132300);
    int v = m5;
    std::cout << v << std::endl;
    static_cast<int>(m5);//由于类型转换运算符的重载 Str5 -> int
    static_cast<Str5>(10000);//因为单参数的构造函数导致的类型转化 int -> Str5


    Str5 m6(98123);
//    m6 + 3;//illegal:Use of overloaded operator '+' is ambiguous (with operand types 'Str5' and 'int')
    //没有完美匹配 operator + 。编译器可以将Str5转化为int ，两个int相加；也可以将 3转化为Str5，两个Str5相加。

//    std::cin << 3;//illegal。编译器对类型转化有相应的操作，不允许std::cin有隐式的转化。std::cin可以转化为bool。if(std::cin)
//    经常用。如果std::cin << 3;中cin可以转化为bool，则可以变为 1/0 << 3，输出流就变成了右移运算符，std::cin << 3属于意外的行为
//    m6 + 3;//可以通过explicit来修改，explicit可以添加到单参构造函数或者类型转换上。
    //编译器可以将Str5转化为int ，两个int相加；也可以将 3转化为Str5，两个Str5相加。选其中一个

    Str6 m7(123);
//    std::cout << m7 << std::endl;//explicit operator bool() const 则illegal。Str6没有重载输出流
                                   //         operator bool() const 则legal。Str6被隐式转换为bool，输出

   //但是explicit operator bool() const 。explicit存在时
   auto var = m7 ? 1 : 0;
   std::cout << var << std::endl;
   if (m7) std::cout << "1" << std::endl;
   else std::cout << "0" << std::endl;
   //上述代码合法，仍然存在隐式转换。当作为条件表达式时，会进行隐式转换
    std::cout << "----------------" << std::endl;

    Str7 m8(1000), m9(10000);
    std::cout << (m8 == m9) << std::endl;
    std::cout << (m8 != m9) << std::endl;//c17 illegal. c20 legal:c20 通过重载 == ，编译器自动推导出 !=
    //可以通过cpp insights看出
    // (m8 != m9) 是通过 (!operator==(Str7(m8), Str7(m9))求出
    //但反过来不行，不能通过重载 != 来推断 ==

    std::cout << (m8 == 100)/*按照第二种重载 == ，输入参数的顺序，可以运行*/ << std::endl;
    std::cout << (100 == m8)/*按照第二种重载 == ，输入参数的相反顺序，仍可以运行(c20)。隐式交换操作数。c17又不行*/ << std::endl;
    //也可以两个相结合
    std::cout << (100 != m8) << std::endl;

    std::cout << (m8 < 1000) << std::endl;
    std::cout << (1000 < m8) << std::endl;
    std::cout << (m8 > 1000) << std::endl;
    std::cout << (1000 > m8) << std::endl;
    std::cout << (m8 <= 1000) << std::endl;
    std::cout << (1000 <= m8) << std::endl;
    std::cout << (m8 >= 1000) << std::endl;
    std::cout << (1000 >= m8) << std::endl;


}