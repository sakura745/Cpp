#include <iostream>
#include <string>

struct Str {
    int val = 3;
    auto operator () (int y = 3/*只有()可以有缺省参数*/)   {
        return val + y;
    }

//    auto operator + (Str x, Str y) {}//illegal:Overloaded 'operator+' must be a unary or binary operator (has 3 parameters)
    //怎么是三个参数？第一个参数是*this，第二x，第三个y。因为定义为成员函数。修改为
    auto operator + (Str x) {
        return Str(val + x.val);
    }
};

/*auto operator + (Str x, Str y) {
    Str z;
    z.val = x.val + y.val;
    return z;
}*/

//auto operator + (int x, double y) {}//illegal x y至少一个为类 类型
auto operator + (int x, Str y) {}//legal

//auto operator + (int x, Str y = Str{}) {}//illegal。不能定义缺省参数


struct Str1 {
    Str1(int x) : val(x) {}

    auto operator + (Str1 input) {
        std::cout << "Str1's operator + is called.\n";
        return Str1(val + input.val);
    }
    int val;
};

struct Str2 {
    Str2(int x) : val(x) {}

    int val;
};

auto operator + (Str2/*& 可不能加引用&，int转换不成Str2*/ input1, Str2 input2) {
    return Str2(input1.val + input2.val);
}

struct Str3 {
    Str3() = default;
    Str3(int x) : val(x) {}
    friend auto operator + (Str3 input1, Str3 input2) {//友元函数，类内定义典型应用。编译器会通过ADL来确认友元函数
        return Str3(input1.val + input2.val);
    }
    friend auto&/*输出流不支持拷贝，只能返回引用*/ operator << (std::ostream&/*由于ofstream, cout, ostringstream都派
 * 生于ostream，可以用ostream&表示任何输出流*/ ostr, Str3 input) {
        ostr << input.val;
        return ostr;//为了支持类似与cout << x << z;这种串联方式。cout << x 返回cout，再执行cout << z
    }
    Str3& operator= (const Str3& input) {//拷贝赋值函数，也是运算符重载
        val = input.val;
        return *this;
    }
    Str3& operator= (const std::string& input/*只能显式写一个参数，因为=是二元操作符，另一个参数是*this*/) {//重载运算符
        val = static_cast<int>(input.size());
        return *this;
    }
    int& operator [] (int id) {
        return val;
    }
    int operator [] (int id) const{//对于operator[]的又一次重载。重载不能基于返回类型重载。是基于有无const进行重载的
        return val;
    }

    Str3& operator++ () {//前缀自增
        ++val;
        return *this;
    }
    Str3 operator++ (int/*只是为了区分前后缀自增，无其他意义及作用*/) {//后缀自增
        Str3 tmp(*this);
        ++val;
        return tmp;
    }

private:
    int val;
};
/*auto operator + (Str3 input1, Str3 input2) {
    return Str3(input1.val + input2.val);//illegal。成员函数val为私有，所以要将operator + 设置为友元函数
}*/


int main() {
    Str x;
    x.val;
    Str y;
    Str z = x + y;
    std::cout << z.val << std::endl;
    std::cout << x(5) << std::endl;
    std::cout << x() << std::endl;

    Str1 x1 = 3;
    Str1 y1 = 4;//隐式的由int转换为Str1
    Str1 z1 = x1 + y1;
    Str1 z2 = x1 + 3/*隐式的由int转换为Str1*/;
    //+ 是对称运算，也应该支持4 + x1
//    Str1 z3 = 4 + x1;//illegal:Invalid operands to binary expression ('int' and 'Str1'
    // 因为编译器先看到4，再看到+。会直接使用内建类型的+，而不会使用Str1内的成员函数。对称运算符定义为非成员函数

    Str2 x2 = 3;
    Str2 z3 = 4 + x2;

    Str3 x3 = 4;
    Str3 x4 = 5 + x3;
    std::cout << x3 << ' ' << x4 << std::endl;

//    Str3 x5 = "fasdf";//illegal。因为Str3的拷贝构造函数没有修改，修改的是拷贝赋值函数
    Str3 x6;
    x6 = "abcde";
    std::cout << x6 << std::endl;//输出的是string字符串的长度
    std::cout << x6[111]/*用[]读*/ << std::endl;
    x6[11] = 14;//用[]写
    std::cout << x6[111] << std::endl;

    const Str3 x7 = 3;
//    x7[0] = 3;//illegal.const不能写，符合const的行为
    std::cout << x7[0] << std::endl;//illegal。const不能读，这不符合const的行为。通过再次重载[]来修改行为

    Str3 x8(66);
    ++++x8;
    std::cout << x8 << std::endl;

    Str3 x9(55);
    std::cout << x9++ << std::endl;
    std::cout << x9 << std::endl;


}