#include <iostream>
#include <string>
namespace ctordtor {
    class Str {
    public:
        Str() {//c98写法
            std::cout << "Constructor is called!" << std::endl;
        }

        //构造函数的重载
        Str(int input) {//c98写法
            x = input;
            std::cout << x << std::endl;
        }

    private:
        int x;
    };

    class Str1 {
    public:
    /*    Str1() {
        x = 3;
    }
    Str1(int input) {
        x = input;
    }*/ //代码显得重复有两个方法修改
        //法一：可修改为构建缺省实参。只有形参列表中最后的才能构造缺省实参
        Str1(int input = 3) {
            x = input;
        }

    private:
        int x;
    };

    class Str2 {
    public:
        Str2() : Str2(3)/*法二，代理构造函数c11写法*/ {//先执行代理构造函数，再执行本身的构造函数的函数体
            std::cout << "here1" << std::endl;
        }

        Str2(int input) {
            std::cout << "here2" << std::endl;
            x = input;
        }

        void fun() {
            std::cout << x << std::endl;
        }

    private:
        int x;
    };

    class Str3 {
    public:
        Str3(const std::string& val) {
            x = val;//是赋值，不是初始化
        }

        void fun() {
            std::cout << x << std::endl;
        }

    private:
        std::string x;
    };

    class Str4 {
    public:
        Str4(const std::string& val) {
            std::cout << "Pre-assignment: " << x << std::endl;//这一行没有报错，说明x已经被初始化了。
            //使用缺省初始化已经构造了，构造为空字符串
            x = val;//赋值
            std::cout << "Post-assignment: " << x << std::endl;
        }//性能不是很好，没有直接初始化为指定字符串。先通过缺省初始化，再赋值。等价于std::string x; x = "abc";
    private:
        std::string x;
    };

    class Str5 {
    public:
        Str5(const std::string& val,
             int&/*要加&，否则ref绑定在p_i形参上。构造函数结束后，p_i将被销毁，ref变成非法引用*/ p_i)
                : x(val), y(0)/*初始化列表。对于x使用val初始化，y用0初始化，z缺省初始化*/
                , ref(p_i) {
            std::cout << "Pre-assignment: " << x << std::endl;
            std::cout << "Post-assignment: " << x << std::endl;
            ref = 16;
        }

    private:
        std::string x;
        int y;
        int z;
        int& ref;//引用在初始化时，要给定引用对象。因此只能使用初始化列表来初始化。因为函数体中的是属于赋值行为
    };

    class Str6 {
    public:
        Str6(const std::string& val)
                : /*x(val), y(x.size())*//*即使调换初始化顺序也合法*/ y(x.size()), x(val) {
            //是按照声明的顺序，初始化顺序无所谓，是为了让销毁的顺序不变。
            //否则需要额外的操作来存储构造顺序，用来保证销毁顺序不变，影响性能。
            //为了可读性，也要保证初始化列表顺序和声明顺序相同。
            std::cout << x << ' ' << y << std::endl;
        }

    private:
        //声明的顺序
        std::string x;
        size_t y;
    };

    class Str7 {
    public:
        Str7() {}//缺省构造函数。不提供任何参数来构造
        Str7(int input = 3) {}//也是缺省构造函数，不提供任何参数来构造

    private:
        std::string x;
        size_t y;
    };

    struct Str8 {
        size_t x;
        size_t y;
    };

    struct Str9 {
        Str9(int input) {}

        size_t x;
        size_t y;
    };

    struct Str10 {
        size_t x;
        size_t y;
        int &ref;
    };
    struct Str11 {
        //内建类型，缺省初始化为随机值
        size_t x;
        size_t y;

        //抽象数据类型，用缺省构造函数来进行缺省初始化
        std::string s;
    };

    struct Str12 {
        Str12() = default;//意思是这个缺省构造函数的逻辑和编译器自动合成的缺省构造函数的逻辑是一样的。编译器什么逻辑：
        // 使用缺省初始化来初始化数据成员
        //为什么要写。因为不写，编译器不会生成缺省初始化。如果我们需要一个缺省初始化，不自己定义，就可以这么写。

        Str12(const std::string& input)
                : x(input) {}

        std::string x;
    };
}
using namespace ctordtor;
int main() {
    std::cout << "Str:" << std::endl;
    Str m;
    Str m1(3);

    std::cout << "----------------\n" << "Str1:" << std::endl;
    Str1 m2;//legal
    Str1 m3(30);//legal

    std::cout << "----------------\n" << "Str2:" << std::endl;
    Str2 m5(30);
    m5.fun();

    Str2 m4;
    m4.fun();//输出为3。缺省构造函数有个代理构造函数，代理给Str(3)。Str(3)是有参数的构造函数，因此输出3

    std::cout << "----------------\n" << "Str3:" << std::endl;
    Str3 m6("abc");
    m6.fun();

    std::cout << "----------------\n" << "Str4:" << std::endl;
    Str4 m7("abc");

    std::cout << "----------------\n" << "Str5:" << std::endl;
    int val;
    Str5 m8("abc", val);
    std::cout << val << std::endl;

    std::cout << "----------------\n" << "Str6:" << std::endl;
    Str6 m9("salkdflaskdf");

    std::cout << "----------------\n" << "Str8:" << std::endl;
    Str8 m10;//legal是因为编译器合成了一个缺省构造函数
//   Str9 m11;//illegal 提供了构造函数，编译器不会自动合成缺省构造函数，因此error
//   Str10 m12;//illegal 条件不允许。因为有个引用，引用需要初始化是绑定其他对象，缺省初始化不行，因此error

    std::cout << "----------------\n" << "Str11:" << std::endl;
    Str11 m13;//缺省初始化
    std::cout << m13.x << '#' << m13.y << '#' << m13.s << "#####" << std::endl;

//    Str11 m14()/*不要加()变成函数声明了。Most vexing parse*/;
//    std::cout << m14.x << std::endl;//illegal

    Str11 m15{}/*花括号可以*/;

    std::cout << "----------------\n" << "Str12:" << std::endl;
    Str12 m16;
}