#include <iostream>
#include <type_traits>
#include <typeinfo>

int main() {
    int x1;
    int x2;
    int x3;
    int* a[3] = {&x1, &x2, &x3};//指针数组：a是数组。指针数组，类比于正常的int数组。
    std::cout << std::is_same_v<decltype(a), int*[3]> << '\n';

    int c[3];
//    int (*b)[3] = {&x1, &x2, &x3};//error. b is pointer, cannot initialize through aggregate initialization.
    int (*b)[3] = &c;//数组的指针. Using array by initialization。(*b)是一个整体. int[3] *b
    std::cout << std::is_same_v<decltype(*b), int(&)[3]> << '\n';//decltype(rval)左值+引用。
    std::cout << typeid(*b).name() << '\n';//实际上，*b的类型为int [3]
    std::cout << std::is_same_v<decltype(b), int(*)[3]> << '\n';//表示*修饰的是对象，即为b，而不是修饰int
    std::cout << std::is_same_v<decltype(b), int*[3]> << '\n';//结果是0

    int f[3];
    int (&d)[3] = f;//数组的引用
    std::cout << std::is_same_v<decltype(d), int(&)[3]> << '\n';

    //int& e[3] = {x1, x2, x3}; error没有引用的数组

}
