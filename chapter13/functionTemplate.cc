#include <iostream>

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



}