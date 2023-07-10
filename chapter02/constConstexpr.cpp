#include <iostream>
#include <type_traits>
void fun(const int& param) {

}
int main() {
    int x = 3;
    int y = 4;

    if (x == 3) {
        //...
    }//为了防止写出if(x = 3)这类错误，可以赋给x限定符const
    const int x2 = 3;
//    if (x2 = 3) {} //illegal 会直接报错

    int y2 = x + 1;
    int y3 = x2 + 1;
    //由于x不是const，因此在对y2通过x初始化时，会先读x，再读取x + 1，再将x + 1赋给y2
    //而x2是const，则对编译期来说，y3直接初始化为3 + 1 = 4。减少了内存读取过程。

    const/*底层，地址指向的值*/ int* p1 = &x;//指向 常量的指针。
    //p1的类型是 const int* 是int*(&x)到const int*(p1)的隐式转换

    //const int* -> int* 不能隐式转换
    //illegal
//    const int x3 = 4;
//    int* ptr3 = &x3;

    std::cout << std::is_same_v<decltype(p1), const int*> << std::endl;
    int const* p3 = &x;//p1 p3 类型相同
    std::cout << std::is_same_v<decltype(p3), int const*> << std::endl;
    std::cout << std::is_same_v<decltype(p3), const int*> << std::endl;
    p1 = &y;//legal
    //*p1 = y;//illegal

    int* const/*顶层，指针指向的内存地址*/ p2 = &x;// const p2's type is int*. 指向 常量指针。
    //p2 = &y;//illegal
    *p2 = y;//legal



    //常量引用，防止被非本意地修改和节省空间。
    fun(x);
    const int& ref3 = 3;//特殊规定，可以绑定字面值
    fun(3);//用于绑定字面值。等价于"const int& x = 3";

    int a;
    std::cin >> a;
    const int b = a;
//    constexpr int b2 = a;//illegal constexpr只能用常量进行初始化
    constexpr int b3 = 3;//legal

    constexpr int* ptr = nullptr;//constexpr修饰的是顶层：ptr，区别于const int* ptr
    std::cout << std::is_same_v<decltype(ptr), const int*> << std::endl;
    std::cout << std::is_same_v<decltype(ptr), int* const> << std::endl;
    constexpr const int* ptr2 = nullptr;//等价于const int* const ptr2;
    std::cout << std::is_same_v<decltype(ptr2), const int* const> << std::endl;

}