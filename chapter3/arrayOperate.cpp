#include <iostream>
#include <type_traits>
#include <typeinfo>


int main() {

    int a[15];//a is array
    std::cout << sizeof(a) / sizeof(int) << std::endl;
    std::cout << std::size(a) << std::endl;
    std::cout << std::end(a) - std::begin(a) << std::endl;
    std::cout << std::cend(a) - std::cbegin(a) << std::endl;//只涉及读，建议用cend

    auto b = a;//b is pointer
    //illegal
//    std::cout << sizeof(b) / sizeof(int) << std::endl;
//    std::cout << std::size(b) << std::endl;
//    std::cout << std::end(b) - std::begin(b) << std::endl;
//    std::cout << std::cend(b) - std::cbegin(b) << std::endl;

    int c[4] = {2, 3, 5, 7};
    //traverse 1
    size_t index = 0;
    while (index < std::size(c)) {
        std::cout << c[index] << ' ';
        index = index + 1;
    }
    std::cout << std::endl;

    //traverse 2
    auto ptr = std::cbegin(c);
    while (ptr != std::cend(c)) {
    //while (ptr < std::cend(c)) {
        std::cout << *ptr << ' ';
        ptr = ptr + 1;
    }
    std::cout << std::endl;

    //traverse 3
    for (int x : c) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

}
