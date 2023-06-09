#include <iostream>
#include <type_traits>

//函数模板的声明
template <typename T>
void fun(T);

template <class/*class也可以，与typename没区别*/ T>
void fun(T);

//函数模板的定义
template <typename T/*模板形参，表明一种类型*/>
void fun(T input/*函数形参*/) {
    std::cout << input << std::endl;
}
struct Str{};

//函数模板的重载。函数名称相同，形参列表不同
template <typename T1, typename T2/*模板的形参列表*/>
void fun(T1 input1, T2 input2) {
    std::cout << input1 << std::endl;
    std::cout << input2 << std::endl;
}

//也是函数模板的重载
template <typename T>
void fun(T* input) {
    std::cout << *input << std::endl;
}

template<typename T>
void fun2(T& input) {
    std::cout << input << std::endl;
}

template<typename T>
void fun3(T&&/*很像右值引用，但是在这里是万能引用*/ input) {//如果T类型被确定下来了，是右值引用。如int&&。万能引用可以引用左值也可以引用右值
    std::cout << input << std::endl;
}

template <typename T>
void fun4(T input1, T input2) {
    std::cout << input1 << std::endl;
    std::cout << input2 << std::endl;
}

template <typename T, typename Res>
Res fun5(T input1) {
    return Res{};
}

template <typename T>
void fun6(unsigned input1 = sizeof(T)) {
}

template <typename T>
void fun7(typename std::remove_reference/*去掉引用*/<T>::type/*T去掉引用后的结果*/ input1) {
}

template <typename T = int/*缺省模板实参*/>
void fun8(typename std::remove_reference<T>::type input1) {
}
template <typename T = int>
void fun9(unsigned input1 = sizeof(T)) {
}
template <typename T, typename Res = int>
Res fun10(T input1) {
    return Res{};
}
template <typename T = int>
void fun11(T input1, T input2) {
}
template <typename T1, typename Res = int, typename T2>//模板缺省实参的位置和函数缺省实参不一样，函数只能最右的缺省实参
Res fun12(T1 x, T2 y) {
    return Res{};
}

template <typename Res, typename T>
Res fun13(T input1) {
    return Res{};
}


template <typename T1, typename T2>
void fun14(T1 x, T2 y) {
    std::cout << "Template is called.\n";
}
void fun14(int x, double y) {
    std::cout << "Function is called.\n";
}


template <typename T1, typename T2>
void fun15(T1 x, T2 y) {
    std::cout << "'T1 T2' is called.\n";
}
template <typename T1>
void fun15(T1 x, float y) {
    std::cout << "'T1 float' is called.\n";
}

template <typename T>
void fun16(T x) {
    std::cout << "T is called.\n";
}
template <typename T>
void fun16(T* x) {
    std::cout << "T* is called.\n";
}

template <typename T1, typename T2>
void fun17(T1* x, T2 y) {
}
template <typename T1, typename T2>
void fun17(T1 x, T2* y) {
}
int main() {
    //对函数模板实例化才能调用
    fun<int/*int为模板实参*/>(3/*3为函数实参*/);//显式实例化
    //模板形参在编译期要赋予实参，就可以把函数模板实例化为一个函数
    //函数实参是在运行期调用的

//    fun<Str>(Str{});//会导致fun中的"<<"非法。当然了，因为结构体中没有重载 << 操作符。这个错误是模板编译期的第二个阶段
    //发现的。就是实例化的阶段发现的

    int x = 5;
    fun<int>(&x);//调用void fun(T* input)

    fun(38);//隐式实例化

    int y = 12312;
    fun2(y);
    int& y2 = y;
    fun2(y2);//通过y2类型：int& 推导，先忽略&；用T& 和 int匹配，所以T -> int
    auto& a = y2;//通过y2类型：int&推导，先忽略&；用auto& 和 int匹配，所以 auto -> int


    int&&/*右值引用*/ x2 = 3/*右值*/;
    fun3(3);//3为右值，所以T被推导为去掉引用的右值的基本类型：T -> int（T&& 和 int&& 匹配）

    fun3(y);//y为左值，所以T被推导为左值的引用：T -> int&，所以T&& -> int&（int& && 通过引用折叠变为 int&）
    fun3(y2);//y2为左值引用，也是T&& -> int&

    fun(3);//先去掉引用：int，不包含引用；再忽略顶层const，没有const；最后数组、函数转化为相应的指针类型，没有。最后T -> int
    fun(y2);//先去掉引用：int& -> int；再忽略顶层const，没有const；最后数组、函数转化为相应的指针类型，没有。最后T -> int
    const int& y3 = y;
    fun(y3);//先去掉引用：const int& -> const int；再忽略顶层const，const int -> int；最后数组、函数转化为相应的指针类型，没有。最后T -> int

    const/*底层*/ int* const/*顶层*/ ptr = &x;
    fun(ptr);//先去掉引用：const int* const，不包含引用；
                    // 再忽略顶层const，const int* const -> const int*；
                    // 最后数组、函数转化为相应的指针类型，没有。最后T -> const int*

    int z[3];
    fun(z);//T -> int*。模板和auto一样，int [3]退化为int*

    fun(3, 5);//自行推导
    fun<int/*匹配第一个模板形参，匹配T1*/>(3, 5);//T1显式实例化，T2隐式实例化

    fun4<int>(3, 5.0);//T为int，因为显式给出类型。不管5.0是什么类型
//    fun4(3, 5.0);//illegal. 系统尝试进行推导，但不知道听谁的
    fun4(3,(int)5.0);

//    fun5(3);//illegal 模板形参 Res 与函数形参无关，无法推导
//    fun6(3);//illegal  相关，也不一定能推导成功，无法推导
//    fun7(3);//illegal  相关，也不一定能推导成功，无法推导
//    fun4(3, 5.0);//illegal. 进行推导，但会产生歧义

    fun8(3);
    fun9(3);
    fun10(3);
    //缺省实参处理的是 无法推导 的情况。而不是推导产生歧义的情况
//    fun11(3, 5.0);//illegal 产生歧义，模板缺省实参也不行

    fun12(3, 4);
    fun12<int, int, double/*按照模板形参的顺序显式指定*/>(3, 4);
    fun12<int, int/*按照模板形参的顺序部分显式指定*/>(3, 4);
    fun5<int, std::string>(1);//想要指定Res类型，必须要指定T类型。因为是按照顺序指定。可以将模板中Res和T调换顺序
    fun13<std::string>(1);//少写了个实参类型。意思就是应该将最需要显式指定实参的放到最左侧


    //SFINAE (Substitution Failure Is Not An Error) 指的是模板元编程中的一种技巧。它表示当一个模板被实例化时，
    // 如果出现了模板参数不满足模板条件的情况，编译器不会给出错误提示，而是直接忽略该实例化并继续寻找合适的候选者。
    // 这使得模板更加灵活，可以适应更广泛的使用场景。

//    fun4(3, 1.0);//这个错误是因为函数本身的错误，而不是模板类型的错误。当编译器发现fun4(3, 1.0)，与所给fun4模板匹配失败，
    //不会马上报错，会再去找合适的候选者，没有找到之后才会报错。这个错误是在SFINAE之后，才会报错
    //error:candidate template ignored: deduced conflicting types for parameter 'T' ('int' vs. 'double')

    fun14(1, 2.0);//输出 Function is called. 调用的是函数而不是模板.当模板和函数一样，会调用函数
    fun14(1, 2.0f);//输出 Template is called. 函数不是完美匹配，需要类型转换。模板不需要，因为编译器根据函数实参隐式推导
    // 模板实参，所以使用模板

    fun15(1, 13.0f);//输出 'T1 float' is called.编译器会选择特殊的版本
    fun16(&x);//输出 T* is called.编译器会选择特殊的版本
    //如何判断特殊： 假设 fun16(T x)的T类型为 A     fun16(T* x)的T*类型为 B*   A,B为具体类型
    //                      T 能匹配 B* 吗             T* 能匹配 A 吗
    //                            能                        不能
    //所以 fun16(T* x) 比 fun16(T x) 特殊

//    fun17(&x, &x);//illegal:Call to 'fun17' is ambiguous. 比较不出哪个特殊。

}