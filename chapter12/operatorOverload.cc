#include <iostream>
#include <string>
namespace operatorOverload {
    struct Str {
        int val = 3;
        auto operator()(int y = 8/*只有operator()可以有缺省参数*/) {
            return val + y;
        }

//        auto operator+(Str x, Str y) {}//illegal:Overloaded 'operator+' must be a unary or binary operator (has 3 parameters)
        //怎么是三个参数？第一个参数是*this，第二x，第三个y。因为定义为成员函数。修改为
        auto operator+(Str x) {
            return Str(val + x.val);
        }
    };

/*
    //legal
    auto operator+(Str x, Str y) {
        Str z;
        z.val = x.val + y.val;
        return z;
    }
*/

//    auto operator+(int x, double y) {}//illegal x y至少一个为类 类型
    auto operator+(int x, Str y) {}//legal

//    auto operator+(int x, Str y = Str{}) {}//illegal。不能定义缺省参数

    struct Str2 {
        Str2(int par) : val(par) {}

        auto operator+(Str2 input) {
            std::cout << "Str2's operator+ is called.\n";
            return Str2(val + input.val);
        }//成员函数
        int val;
    };

    struct Str3 {
        Str3(int x) : val(x) {}

        int val;
    };

    //非成员函数
    auto operator+(Str3/*不能加引用&，int转换不成Str3*/ input1, Str3 input2) {
        return Str3(input1.val + input2.val);
    }

    struct Str4 {
        Str4() = default;
        Str4(int x) : val(x) {}

        //友元函数，类内定义典型应用。编译器会通过ADL来确认友元函数
        friend auto operator+(Str4 input1, Str4 input2) {
            return Str4(input1.val + input2.val);
        }

        //下述实现，维持了ostr << input的顺序，左侧参数在<<的左侧，右侧参数在<<的右侧
        friend auto&/*输出流不支持拷贝，只能返回引用*/ operator<<(std::ostream&/*由于ofstream, cout, ostringstream都派
        生自ostream，可以用ostream&表示任何输出流*/ ostr, Str4 input) {
            ostr << input.val;
            return ostr;//为了支持类似与cout << x << z;这种串联方式。cout << x 返回cout，再执行cout << z
        }
        Str4& operator=(const Str4& input) {//拷贝赋值函数，也是运算符重载
            val = input.val;
            return *this;
        }
        Str4& operator=(const std::string& input/*只能显式写一个参数，因为=是二元操作符，另一个参数是*this*/) {//重载运算符
            val = static_cast<int>(input.size());
            return *this;
        }
        int&/*使用&的原因是[]是可读可写的*/ operator[](int id) {
            return val;
        }
        int operator[](int id) const {//对于operator[]的又一次重载。重载不能基于返回类型重载。是基于有无const进行重载的
            //对于上一个operator[]的参数来说，第一个是this指针，类型为Str4*，
            //该函数来说第一个参数是const this指针，类型为const Str4*
            //但不会出现Str4* const这种类型的this指针
            return val;
        }

        //前后缀返回类型不同，为了保持++(++x)的特性，前缀函数返回类型为引用。没有(x++)++的特性，因此后缀返回非引用
        Str4& operator++() {//前缀自增
            ++val;
            return *this;
        }
        Str4 operator++(int/*只是为了区分前后缀自增，无其他意义及作用*/) {//后缀自增
            Str4 tmp(*this);
            ++val;
            return tmp;
        }

    private:
        int val;
    };
    /*auto operator+(Str4 input1, Str4 input2) {
        return Str4(input1.val + input2.val);//illegal。成员函数val为私有，所以要将operator + 设置为友元函数
    }*/
}
using namespace operatorOverload;
int main() {
    Str x;
    x.val;
    Str y;
    Str z = x + y;
    std::cout << z.val << std::endl;
    std::cout << x(5) << std::endl;
    std::cout << x() << std::endl;
    std::cout << "--------------" << std::endl;

    Str2 x1 = 3;
    Str2 y1 = 4;//隐式的由int转换为Str2
    Str2 z1 = x1 + y1;
    Str2 z2 = x1 + 3/*隐式的由int转换为Str2*/;
    //+ 是对称运算，也应该支持4 + x1
//    Str2 z3 = 4 + x1;//illegal:Invalid operands to binary expression ('int' and 'Str2'
    //因为编译器先看到4，再看到+。会直接使用内建类型的+，而不会使用Str2内的成员函数。
    ///对称运算符应该定义为非成员函数
    std::cout << "--------------" << std::endl;

    Str3 x2 = 3;
    Str3 z4 = 4 + x2;
    std::cout << "--------------" << std::endl;

    Str4 x3 = 4;
    Str4 x4 = 5 + x3;
    std::cout << x3 << ' ' << x4 << std::endl;

//    Str4 x5 = "fasdf";//illegal。因为Str4的拷贝构造函数没有修改，修改的是拷贝赋值函数
    Str4 x6;
    x6 = "abcde";
    std::cout << x6 << std::endl;//输出的是string字符串的长度
    std::cout << x6[111]/*用[]读*/ << std::endl;
    x6[11] = 14;//用[]写
    std::cout << x6[111] << std::endl;

    const Str4 x7 = 3;
//    x7[0] = 3;//illegal.const不能写，符合const的行为
    std::cout << x7[0] << std::endl;//illegal。const不能读，这不符合const的行为。通过再次重载[]来修改行为

    Str4 x8(66);
    ++++x8;
    std::cout << x8 << std::endl;

    Str4 x9(55);
    std::cout << x9++ << std::endl;
    std::cout << x9 << std::endl;

}