#include <iostream>
#include <type_traits>
int main() {
    int x1 = 3;
    int& ref = x1;//x1 type int, ref type int&
    auto ref2 = ref;//ref type int.ref作为右值，类型退化。因此ref2类型为int
    std::cout << std::is_same_v<decltype(ref2), int&> << std::endl;
    std::cout << std::is_same_v<decltype(ref2), int> << std::endl;

    const auto y = 3;
    std::cout << std::is_same_v<decltype(y), const int> << std::endl;

    constexpr auto y1 = 3;
    std::cout << std::is_same_v<decltype(y1), const int> << std::endl;

    const auto& y2 = 3;
    std::cout << std::is_same_v<decltype(y2), const int&> << std::endl;

    const int z = 4;//z type is const int
    const auto z2 = z;//z作为右值，类型退化为int，z2有const，compiler为了达到完美的匹配，z2类型为const int
    std::cout << std::is_same_v<decltype(z2), const int> << std::endl;

    const int z3 = 4;//z3 type is const int
    auto z4 = z3;//z3作为右值，类型退化为int，z4类型为int
    std::cout << std::is_same_v<decltype(z4), int> << std::endl;

    const int z5 = 4;//z5 type is const int
    auto& z6 = z5;//z5作为右值，有&，不会类型退化为int，z6类型为const int&
    std::cout << std::is_same_v<decltype(z6), const int&> << std::endl;

    const int& z7 = 4;
    auto& z8 = z7;
    std::cout << std::is_same_v<decltype(z8), const int&> << std::endl;
}