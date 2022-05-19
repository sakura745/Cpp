#include <iostream>
#include <type_traits>
#include <typeinfo>

int main() {
    int a[3] = {3, 5, 7};
    std::cout << a[0] << std::endl;

    const int x = 1;
    std::cout << std::is_same_v<decltype((x)), const int&> << std::endl;//(x) is locator value.

    std::cout << std::is_same_v<decltype((a)), int(&)[3]> << std::endl;
    std::cout << std::is_same_v<decltype(a), int [3]> << std::endl;

    auto b = a;//b type degenerate from int [3] to int*
    std::cout << std::is_same_v<decltype(b), int*> << std::endl;
    std::cout << *b << std::endl;
    std::cout << b << std::endl;
    std::cout << &(a[0]) << std::endl;
    std::cout << b[1] << std::endl;//[]不是数组转有的，对于指针来说也可以

    int y = 100;
    int* ptr = &y;
    std::cout << *ptr << '\n';
    //x[y] == *(x + y)  '*' means dereference.
    std::cout << ptr[0] << '\n';//ptr[0] == *(ptr + 0)
    std::cout << 0[ptr] << '\n';//0[ptr] == *(0 + ptr)

}
