#include <iostream>
#include <type_traits>
#include <typeinfo>


int main() {

    int a[15];//a 是数组
    std::cout << sizeof(a) /*C方法*// sizeof(int) << std::endl;
    std::cout << std::size(a)/*c++*/ << std::endl;
    std::cout << std::end(a) - std::begin(a) << std::endl;
    std::cout << std::cend(a) - std::cbegin(a) << std::endl;//只涉及读，建议用cend
    std::cout << "-------------" << std::endl;

//    auto b = a;//b is pointer
//    //illegal
//    std::cout << sizeof(b) / sizeof(int) << std::endl;
//    std::cout << std::size(b) << std::endl;
//    std::cout << std::end(b) - std::begin(b) << std::endl;
//    std::cout << std::cend(b) - std::cbegin(b) << std::endl;

    int c[4] = {2, 3, 5, 7};
    //traversal 1
    size_t index = 0;
    while (index != std::size(c)) {
        std::cout << c[index++] << ' ';
    }
    std::cout << std::endl;

    //traversal 2
    auto ptr = std::cbegin(c);
    while (ptr < std::cend(c)) {
        std::cout << *(ptr++) << ' ';
    }
    std::cout << std::endl;

    //traversal 3
    for (int x : c) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

}
