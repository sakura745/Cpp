#include <iostream>
#include <string>
namespace ctordtor3 {
    struct Str {
        Str() = default;

        Str(const Str&) = default;

        Str(Str&&) noexcept = default;

        Str&/*void也不是不行。&可以避免构建临时对象而产生的额外开销*/ operator=(const Str& x) {//拷贝赋值函数
            //处理给自身赋值的情况
            if (&x == this) {
                return *this;
            }
            std::cout << "Str's copy assignment is called." << std::endl;
            val = x.val;//赋值操作
            a = x.a;
            return *this;
        }

        Str& operator=(Str&& x) {//移动赋值函数
            //处理移动自身的情况
            if (&x == this) {
                std::cout << "Dummy assignment" << std::endl;
                std::cout << "Str's move assignment is called." << std::endl;
                return *this;
            }
            std::cout << "Real assignment" << std::endl;

            //释放旧资源
            delete ptr;//如果不给ptr初始化，delete ptr则会报错

            //移动新资源
            ptr = x.ptr;
            x.ptr = nullptr;

            std::cout << "Str's move assignment is called." << std::endl;
            val = x.val;//赋值操作
            a = std::move(x.a);
            return *this;
        }

        ~Str() {//析构函数:释放资源
            std::cout << val << ' ' << a << ' ' << ptr << std::endl;
            //析构函数执行的过程中，数据成员还存在。
            //内存回收是在调用完析构函数才进行的。
            //析构函数和内存回收是两个概念

            //内存分配 -> 构造对象 -> 析构对象 -> 内存回收。按照此顺序，四个步骤
            std::cout << "Str's destructor is called." << std::endl;
        }

        int val = 3;
        std::string a = "abc";
        int *ptr = nullptr;//给自身赋值会出现问题的地方
    };

    struct Str2 {
        Str2() {
            std::cout << "Str2's constructor is called." << std::endl;
        }

        ~Str2() {
            std::cout << "Str2's destructor is called." << std::endl;
        }

        int val = 3;
        std::string a = "abc";
        int *ptr = nullptr;
    };
}
using namespace ctordtor3;
int main() {
    Str m;
    Str m3 = m;//调用拷贝 构造
    Str m2 = std::move(m);//调用移动 构造

    Str m4;
    m4 = m3;//不是构造的过程，是赋值。就会调用拷贝 赋值operator =
    Str m5;
    m5 = std::move(m4);//调用移动 赋值operator =

    Str m6;
    m6 = std::move(m6);//给自身赋值
    m6 = m6;
    std::cout << "-------------------" << std::endl;
    //Str2的移动赋值和拷贝赋值函数编译器自动合成了
    Str2 m7, m8;
    m7 = m8;
    m7 = m7;
    m8 = std::move(m8);
    m7 = std::move(m8);

    //上述对象，编译器会隐式的进行内存分配和内存销毁。

    //显式的内存分配和销毁
    Str2* m9 = new Str2();
    delete m9;//如果不使用delete显式销毁，不会调用析构函数
    std::cout << "-------------------" << std::endl;

}