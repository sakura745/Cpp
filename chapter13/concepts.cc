#include <iostream>
#include <vector>
#include <type_traits>

//一个模板参数
template <typename T>
concept isIntOrFloat = std::is_same_v<T, int> || std::is_same_v<T, float>;//编译期谓词
//编译期谓词 (Compile-time Predicate) 是一种编程概念，通常出现在模板元编程中。它指的是使用布尔表达式对模板类型参数进行编
// 译时判断的方法。在模板元编程中，需要对数据类型在编译期进行操作和判断，这通常是通过模板来实现的。编译期谓词允许在模板
// 参数被实例化之前，对参数进行约束和限制。这可以用于编写更加泛化和模板化的代码，提高程序的性能和可靠性。例如，可以定义
// 使用编译期谓词来实现对类型的静态检查。如果类型不符合某个特定的要求，例如不能调用特定的函数或者不满足特定的接口，则编
// 译器会在编译期间产生错误。这样可以避免在运行时产生不必要的错误或异常。

template <typename T>
//引入一个约束
    requires isIntOrFloat<T>//requires从句
void fun(T input) {}

//也可以这样
//template <typename T>
//void fun(T input) requires isIntOrFloat<T> {}

template <isIntOrFloat/*也可以这样使用谓词*/ T>
void fun1(T input) {}
//包含一个模板参数

//多个模板参数
template <typename T1, typename T2>
concept isAvail = std::is_same_v<T1, T2>;

template <typename T1, typename T2>
concept isAvail2 = !std::is_same_v<T1, T2>;

template <typename T1, typename T2>
    requires isAvail2<T1, T2>
void fun2(T1 input1, T2 input2) {}

template <typename T1>
    requires isAvail2<T1, int>//只对一个模板形参进行限制。也可修改为单模板参数
void fun3(T1 input1) {}

template <isAvail2<int> T1>//等价于 isAvail2<T1, int>. T1一定是第一个参数
void fun4(T1 input1) {}

//说明模板参数的位置的先后是有用的
template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

template <typename T>
concept Addable = requires/*requires表达式，简单表达式，类似于lambda表达式*/ (T a, T b) {
    a + b;//说明是T类型是可以相加的
};

template <typename T>
    requires Addable<T>//requires从句
T add(T a, T b) {
    return a + b;
}

template <typename T>
    requires/*从句关键词*/ requires/*表达式关键词*/ (T x) {
        x + x;
    }
T add(T a, T b) {
    return a + b;
}

template <Addable T>
auto fun5(T x, T y) {
   return x + y;
}

template <typename T>
concept Avail = requires /*requires表达式，类型表达式*/{
    typename T::inter;//表明传入类型必须有inter的定义
};
template <Avail T>
auto fun6(T x) {}
struct Str{
    using inter = int;
};

template <typename T>
concept Avail2 = requires/*requires表达式，复合表达式*/ (T x) {
    {x + 1} -> std::same_as<int>;//表明x可以+1，同时int类型合法，且满足x+1是int类型
};
template <Avail2 T>
auto fun7(T x) {}

template <typename T>
    requires std::is_same_v<T, int>
void fun8(T x) {
    std::cout << "Int is called.\n";
}

template <typename T>
    requires std::is_same_v<T, float>
void fun8(T x) {
    std::cout << "Float is called.\n";
}

template <typename T>
concept C = std::is_same_v<T, int>;

template <typename T>
concept C2 = std::is_same_v<T, int> || std::is_same_v<T, float>;

template <C T>
void fun9(T) {
    std::cout << "Int type\n";
}

template <C2 T>
void fun9(T) {
    std::cout << "Int or Float type\n";
}


template <typename T>
class B;

template <>
class B<int> {};

template <>
class B<float> {};
//希望B只支持int和float型，其他型会直接报错


template <typename T>
    requires std::is_same_v<T, int> || std::is_same_v<T, float>
class B2;

template <>
class B2<int> {};

template <>
class B2<float> {};

int main() {
    std::cout << isIntOrFloat<int> << std::endl;
    std::cout << isIntOrFloat<char> << std::endl;
    fun(3);//满足require从句的要求（谓词返回为true）
//    fun("a");//illegal:use of function ‘void fun(T) [with T = const char*]’ with unsatisfied constraints.不满足约束，编译器报错误

    std::cout << isAvail<int, char> << std::endl;
    std::cout << isAvail2<int, char> << std::endl;

    fun2(3, 1.4);
//    fun2(3, 3);//illegal: use of function ‘void fun2(T1, T2) [with T1 = int; T2 = int]’ with unsatisfied constraints

    fun3(3.3);
//    fun3(3);//illegal:use of function ‘void fun3(T1) [with T1 = int]’ with unsatisfied constraints

    fun5(3, 5);
//    fun5(Str{}, Str{});//illegal:use of function ‘auto fun5(T, T) [with T = Str]’ with unsatisfied constraints

//    fun6(3);//illegal
    fun6(Str{});//因为在Str中定义了inter类型名称，所以legal

//    fun7(Str{});//illegal
    fun7(3);

    fun8(3);//输出Int is called.fun8()的重载，选取了对应的版本。表明requires语句参与了重载解析
    fun8(3.1f);//输出Float is called.

//    fun9(1);//cpp标准是说会选取更严格的标准，但是有的编译器会说有歧义

    B<int> x;
//    B<double> x2;//illegal:aggregate ‘B<double> x2’ has incomplete type and cannot be defined
    //因为除了int和float型都是没有定义，只有声明的，incomplete type

//    B2<double> x3;//illegal:template constraint failure。这个错误共容易读懂

}