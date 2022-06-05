#include <iostream>
#include <type_traits>
int main() {
    int x = 3;
    int y = 5;
    +x;
    -x;
    x + y;
    3 + 5 * 7;
    7 * + 3;//先+3（一元），再 7 *
    int a[3] = {1, 2, 3};
    int* ptr = a;
    ptr = ptr + 1;
    ptr = ptr - 1;

    std::cend(a) - std::cbegin(a);
    //std::cend(a) + std::cbegin(a);无意义

    short c = 3;
    auto d = c;
    std::cout << std::is_same_v<decltype(d), short> << std::endl;
    auto e = +c;//integral promotion
    std::cout << std::is_same_v<decltype(e), int> << std::endl;

    //向0取整
    std::cout << 3 / 2 << std::endl;
    std::cout << -3 / 2 << std::endl;

}