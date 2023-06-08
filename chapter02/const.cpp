#include <iostream>
#include <type_traits>
void fun(const int& param) {

}
int main() {
    int x = 3;
    int y = 4;

    const/*底层，就是值*/ int* p1 = &x;// *p1's type is "const" int. 指向 常量的指针。
    int const* p3 = &x;//p1&p3 have a same type.
    p1 = &y;//legal
    //*p1 = y;//illegal

    int* const/*顶层，就是地址*/ p2 = &x;// const p2's type is int*. 指向 常量指针。
    //p2 = &y;//illegal
    *p2 = y;//legal

    //常量引用，防止被非本意地修改，为了节省空间。
    fun(x);
    fun(3);//equal to "const int& x = 3";

    constexpr int* ptr = nullptr;//constexpr修饰ptr而不是int* 区别于const int* ptr
    std::cout << std::is_same_v<decltype(p1), const int*> << std::endl;//same return true, otherwise false.
    std::cout << std::is_same_v<decltype(ptr), const int*> << std::endl;
    std::cout << std::is_same_v<decltype(ptr), int* const> << std::endl;
    constexpr const int* ptr2 = nullptr;
    std::cout << std::is_same_v<decltype(ptr2), const int* const> << std::endl;

}