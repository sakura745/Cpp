#include <iostream>

namespace specialFunction {
    class Base {
    public:
        Base() {
            std::cout << "Base default ctor is called.\n";
        }
        Base(const Base&) {
            std::cout << "Base copy ctor is called.\n";
        }
        Base& operator = (const Base&) {
            std::cout << "Base copy assignment is called.\n";
            return *this;
        }
        ~Base() {
            std::cout << "Base dtor is called.\n";
        }
    };
    class Derive final : public Base {
    public:
        Derive() = default;
        Derive(const Derive&) = default;
        Derive& operator = (const Derive&) = default;

        //无论派生析构被编译器合成与否，都会调用基类析构。调用顺序当然后调用基类：先构造，后销毁
        ~Derive()
//                = default;
        {
            std::cout << "Derive dtor is called.\n";
        }
    };

    class Base2 {
    public:
        Base2() {
            std::cout << "Base2 default ctor is called.\n";
        }
        Base2(int) {
            std::cout << "Base2 ctor 2 is called.\n";
        }
        Base2(const Base2&) {
            std::cout << "Base2 copy ctor is called.\n";
        }
        Base2& operator = (const Base2&) {
            std::cout << "Base2 copy assignment is called.\n";
            return *this;
        }
    };
    class Derive2 final : public Base2 {
    public:
        Derive2() = default;
        Derive2(int) {}
        Derive2(const Derive2&) {}
    };

    class Base3 {
    public:
        Base3() {
            std::cout << "Base3 default ctor is called.\n";
        }
        Base3(int) {
            std::cout << "Base3 ctor 2 is called.\n";
        }
        Base3(const Base3&) {
            std::cout << "Base3 copy ctor is called.\n";
        }
        Base3& operator = (const Base3&) {
            std::cout << "Base3 copy assignment is called.\n";
            return *this;
        }

    };
    class Derive3 final : public Base3 {
    public:
        Derive3()
            : Base3(0)//基类单参构造
        {}

        Derive3(const Derive3& input)
            : Base3(input)//基类拷贝构造
        {}

        Derive3& operator = (const Derive3& val) {
            Base3::operator = (val);
            return *this;
        }
    };

    class Base4 {
    public:
        Base4() {
            std::cout << "Base4 default ctor is called.\n";
        }
        Base4(int) {
            std::cout << "Base4 ctor 2 is called.\n";
        }
        Base4(const Base4&) {
            std::cout << "Base4 copy ctor is called.\n";
        }
        Base4& operator = (const Base4&) {
            std::cout << "Base4 copy assignment is called.\n";
            return *this;
        }
    };
    class Derive4 final : public Base4 {
    public:
        Derive4()
            : Base4()
            , val(1010)
        {}

        int val = 100;
    };
}

using namespace specialFunction;

int main() {
    Derive d;//缺省构造：派生没有给出缺省构造，编译器合成缺省构造，先调用基类的缺省构造，再调用派生的缺省构造
    Derive x(d);//拷贝构造：派生没有给出拷贝构造，编译器合成拷贝构造，先调用基类的拷贝构造，再调用派生的拷贝构造
    x = d;//拷贝赋值：派生没有给出拷贝赋值，编译器合成拷贝赋值，先调用基类的拷贝赋值，再调用派生的拷贝赋值
    ///编译器合成的派生类，隐式的给了相应的初始化列表，因此会隐式调用相应的函数
    std::cout << "-----------------------" << std::endl;
    Derive2 d2(3);//输出：Base2 default ctor is called. 而不是 Base2 ctor 2 is called.
    //派生类的其他构造函数将隐式调用基类的 **缺省** 构造函数。特殊（非其他）函数：缺省、拷贝、赋值和析构
    //因为特殊函数就是为了建立对象、拷贝对象、赋值对象和销毁对象，是有明确的意义的，对所有类型，函数的意义都是类似的
    //换句话说，特殊函数的更具有一般性。派生类的调用会调用基类对应的函数。
    //编译器不能根据派生类的单参构造的行为来推断基类单参构造的行为，所以只能调用基类的缺省构造
    ///派生类定义的单参构造，没有显式定义初始化列表，因此会隐式调用基类的缺省构造。
    std::cout << "-----------------------" << std::endl;
    Derive2 d3;
    Derive2 d4(d3);//输出Base2 default ctor is called. 而不是 Base2 copy ctor is called.
    //因为编译器合成的拷贝构造，才会调用基类的。Derive2是自定义的，所以也会调用基类缺省构造。
    //因为派生类的拷贝构造是自定义的，编译器不能根据派生类的行为来推断基类拷贝构造的行为，因此只能调用基类的缺省构造
    ///派生类自定义的函数，没有显式定义初始化列表，因此会隐式调用基类的缺省构造。
    std::cout << "-----------------------" << std::endl;
    Derive3 d5;//派生缺省构造显式定义
    Derive3 d6(d5);//派生拷贝构造显式定义
    d6 = d5;//派生拷贝赋值显式定义
    //派生类函数是自定义的，编译器不能根据行为推断到基类缺省构造上，但是可以显式定义到基类对应的函数上。
    ///派生类自定义的函数，显式定义初始化列表，因此会显式调用基类的相应函数。
    std::cout << "-----------------------" << std::endl;
    Derive4 d7;

    std::cout << "-----------------------" << std::endl;
}