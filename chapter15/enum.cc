#include <iostream>

enum Color_de : int;//无作用域枚举的声明：首先需要指定底层尺寸int，其次，要满足翻译单元的一次定义原则，且不能和定义放在同一翻译单元。
enum class Color_cla;//有作用域枚举的声明，就像函数声明一样。底层尺寸缺省为int
//使用枚举声明而使用对象，是极少数的行为。大多数还是使用定义


//无作用域枚举，继承自C语言。但会造成名称污染，两个不同无作用域枚举中，有相同名称，会冲突。因此提出了有作用域枚举
//枚举的定义
enum Color {
    Red,//枚举项。在底层保存时，枚举项对应整数值
    Green = 40,
    Yellow
};

enum Color_ : char/*指定底层整数的类型*/ {
    Red_,//枚举项。在底层保存时，枚举项对应char
    Green_ ,
    Yellow_
};

//无作用域枚举，作用在ABC名字空间中
namespace ABC {
    enum Color2 {
        Red2,
        Green2,
        Yellow2
    };
}

//无作用域枚举，作用在cla类中
class cla {
public:
    enum Color3 {
        Red3,
        Green3,
        Yellow3
    };
};

//有作用域枚举，作用域为Color_cla。继承自C++
enum class Color_cla {
    Red_cla,
    Blue_cla,
    Yellow_cla
};
void fun(Color_cla a) {

}

//在ABC2名字空间中的有作用域枚举
namespace ABC2 {
    enum class Color_cla2 {
        Red_cla2,
        Blue_cla2,
        Yellow_cla2
    };
}

class A {
public:
    enum {x = 3};//早期的编译期常量
    constexpr static int y = 100;//现在的编译期常量
};

int main() {
    Color x = Red;
    ABC::Color2 x2 = ABC::Red2;
    cla::Color3 x3 = cla::Red3;

    Color_cla x4 = Color_cla::Red_cla;
    //x4的类型不需要作用域

    ABC2::Color_cla2 x5 = ABC2::Color_cla2::Red_cla2;

    std::cout << x << " " << Green << " " << Yellow <<std::endl;
    std::cout << sizeof(x) << std::endl;//底层对应整数的类型为int
    std::cout << sizeof(Red_) << std::endl;//底层对应整数的类型为char

    std::cout << Color::Red << std::endl;//legal 对于无作用域的枚举项可以
//    std::cout << Color_cla::Red_cla << std::endl;//illegal 对于有作用域的枚举项不可以。不安全

//    fun(100);//illegal ：隐式转换不安全
    fun(static_cast<Color_cla>(100));//可以显式转换
    std::cout << static_cast<int>(Color_cla::Red_cla) << std::endl;//可以显式转换



}