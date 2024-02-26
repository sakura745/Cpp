#include <iostream>
#include <type_traits>
#include <typeinfo>
#include "definitionArray.cpp"

void fun();
//extern int array[4];//declaration
//extern int* array;//error
extern int array[]/*incomplete type*/;//Unknown bounded array
int main() {
    int a[3] = {3, 5, 7};
    std::cout << a[0] << std::endl;

    const int x = 1;
    std::cout << std::is_same_v<decltype((x)), const int&> << std::endl;//(x) is locator value.

    std::cout << std::is_same_v<decltype((a)), int(&)[3]> << std::endl;
    std::cout << std::is_same_v<decltype(a), int [3]> << std::endl;
    std::cout << "-------------" << std::endl;

    auto b = a;//b type decay from int [3] to int*
    auto& b2 = a;//通过使用引用来避免数组到指针的隐式转换而导致的退化
    std::cout << std::is_same_v<decltype(b), int*> << std::endl;
    std::cout << *b << std::endl;
    std::cout << b << std::endl;
    std::cout << &(a[0]) << std::endl;
    std::cout << b[1] << std::endl;//[]不是数组转有的，对于指针来说也可以
    std::cout << a[100] << std::endl;//a[100]超出界限，可以通过编译，但是行为不确定。
    std::cout << "-------------" << std::endl;

    int y = 100;
    int* ptr = &y;
    std::cout << *ptr << '\n';
    //x[y] == *(x + y)  '*' means dereference. 每个y都为int所占字节数
    std::cout << ptr[0] << '\n';//ptr[0] == *(ptr + 0)
    std::cout << 0[ptr] << '\n';//0[ptr] == *(0 + ptr)

    std::cout << sizeof(a) << '\n';//No decay.
    std::cout << "-------------" << std::endl;

    fun();
    std::cout << array << std::endl;

    //begin address
    std::cout << &(a[0]) << '\n';//begin array address
    std::cout << a << '\n';//begin array address
    std::cout << std::begin(a) << '\n';//begin array address
    std::cout << std::cbegin(a) << '\n';//begin array address. c = const

    //end address
    //a+3是结尾指针，a[3]只有a,a+1,a+2三个元素
    //所以说a的范围是[begin, end) 左闭右开区间
    std::cout << &(a[3]) << '\n';//end array address
    std::cout << a + 3 << '\n';//end array address
    std::cout << std::end(a) << '\n';//end array address
    std::cout << std::cend(a) << '\n';//end array address. c = const
    std::cout << "-------------" << std::endl;

    b = b + 1;//increase
    auto b1 = b - 1;//decrease
    std::cout << (b1 == b) << '\n';//compare
    std::cout << b - b1 << '\n';//distance. (b address - b1 address) / type_length 多少个int长度的字节
}
