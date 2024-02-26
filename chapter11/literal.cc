#include <iostream>
#include <string>
namespace literal {
    class Str {
    public:
        constexpr/*既可以是编译期，也可以是运行期常量*/ /*consteval只能是编译期常量*/ Str(int val) : x(val) {}

        ~Str() = default;//legal 析构函数是平凡的
    //    ~Str() {};//illegal析构函数不是平凡的
        //平凡就是编译器自定义

        Str(double val2) : x(val2) {}

        constexpr/*consteval*/ int fun() const {
            return x + 1;
        }

    private:
        int/*int是字面值*/ x;
    //    std::string/*string不是字面值，编译器不知道在编译期如何处理string。所以有string，不能将Str构造成字面值类*/ abc;
    };

    constexpr Str a(3);

    class Str2 {
    public:
        constexpr Str2(int val) : x(val) {}

        //c14起取消了constexpr 成员函数缺省为const成员函数。是为了当字面值类的类型定义时：Str2 x(10)，可以在编译期
        //通过函数inc()改变其中间状态。在编译期不想改变的函数read()，在显式定义为 const成员函数。如MyFun()
        constexpr void inc() {
            x = x + 1;
        }

        constexpr int read() const {
            return x;
        }

    private:
        int x;
    };

    constexpr int MyFun() {
        Str2 x(10);
        x.inc();
        x.inc();
        x.inc();
        return x.read();
    }
}
using namespace literal;
int main() {
    int x;
    Str b(x);//constexpr，该语句是合法，consteval该语句非法

    std::cout << a.fun() << std::endl;

    Str c(3.0);
    c.fun();//constexpr，该语句是合法，consteval该语句非法

    std::cout << MyFun() << std::endl;
}