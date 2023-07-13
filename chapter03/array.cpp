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
    int c[x];
    //int[x] 属于类型信息，而类型信息是编译器关心的，对于运行器无关。对于c++标准来说，会报错。
    //属于variable length array c++ 问题。但是在IDE上可以运行，属于编译器的扩展。不建议使用，可移植性差。
*/
    constexpr short y = 3;
    int d[y];//legal.y是常量，而不是变量

    int e[3];//default initialization
    int f[3] = {1, 2, 3};//aggregate initialization
    int f1[3] = {1, 2};//f1[2]为缺省初始化
    int f2[3] = {};//f2缺省初始化为0
    int g[] = {1, 2, 3};//aggregate initialization
    int h[] {1, 2, 3};//aggregate initialization
    //int i[2] = {1, 2, 3};//error

    auto j = {1, 2, 3};//j type is not int[3]
    std::cout << typeid(j).name() << std::endl;//using demangling: `./array | c++filt -t`
    std::cout << std::is_same_v<decltype(j), std::initializer_list<int>> << '\n';

//    int k[3] = f; //illegal. Array cannot copy.
    auto l = f;//f type decay from int[3] to int*
    std::cout << std::is_same_v<decltype(l), int*> << '\n';
    auto& m = f;
    std::cout << std::is_same_v<decltype(m), int(&)[3]> << '\n';

    char str[] = "hello";//'\0'表示字符串的结束
    //等价于    char str3[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    char str2[] = {'h', 'e', 'l', 'l', 'o'};
    std::cout << std::is_same_v<decltype(str), char[6]> << '\n';
    std::cout << std::is_same_v<decltype(str2), char[5]> << '\n';

}
