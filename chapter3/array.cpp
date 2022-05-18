#include <iostream>
#include <type_traits>
#include <typeinfo>
int main() {
    int a;
    int b[10];//b type is int[10]
    std::cout << std::is_same_v<decltype(b), int[10]> << '\n';
/*
    int x;
    std::cin >> x;
    int c[x];//illegal. Not recommended!
*/
    constexpr short y = 3;
    int d[y];//legal. Because y is constant or not variable.

    int e[3];//default initialization
    int f[3] = {1, 2, 3};//aggregate initialization
    int g[] = {1, 2, 3};//aggregate initialization
    int h[]  {1, 2, 3};//aggregate initialization
    //int i[2] = {1, 2, 3};//error

    auto j = {1, 2, 3};//j type is not int[3]
    std::cout << typeid(j).name() << std::endl;//using demangling: `./array | c++filt -t`
    std::cout << std::is_same_v<decltype(j), std::initializer_list<int>> << '\n';

    //int k[3] = f; error. Array cannot copy.
    auto l = f;//f type degenerate from int[3] to int*
    auto& m = f;
    std::cout << std::is_same_v<decltype(l), int*> << '\n';
    std::cout << std::is_same_v<decltype(m), int(&)[3]> << '\n';

    char str[] = "hello";//'\0'表示字符串的结束
    //等价于    char str2[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    char str2[] = {'h', 'e', 'l', 'l', 'o'};
    std::cout << std::is_same_v<decltype(str), char[6]> << '\n';
    std::cout << std::is_same_v<decltype(str2), char[5]> << '\n';

}
