#include <iostream>
#include <type_traits>
int main() {
    int x1 = 3;
    int& ref = x1;//x1 type int, ref type int&
    auto ref2 = ref;//ref type int&。ref作为右值，类型退化。因此ref2类型为int
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

    int w[3] = {1,2,3};
    auto w1 = w;
    std::cout << std::is_same_v<decltype(w1), int*> << std::endl;

    int w2[3] = {1,2,3};
    auto &w3 = w2;
    std::cout << std::is_same_v<decltype(w3), int(&)[3]> << std::endl;

    std::cout << "Decltype" << std::endl;
    int& q1 = x1;
    auto q2 = q1;
    decltype(q1) q3 = q1;
    std::cout << std::is_same_v<decltype(q2), int> << std::endl;
    std::cout << std::is_same_v<decltype(q3), int&> << std::endl;

    int* ptr = &x1;
    std::cout << std::is_same_v<decltype(*ptr), int&> << std::endl;
    std::cout << std::is_same_v<decltype(ptr), int*> << std::endl;
    std::cout << std::is_same_v<decltype((ptr)), int*&> << std::endl;

    auto x = 3.5 + 15l;
    decltype(3.5 + 15l) a = 3.5 + 15l;//太麻烦
    decltype(auto) a1 = 3.5 + 15l;
    std::cout << std::is_same_v<decltype(x), double> << std::endl;
    std::cout << std::is_same_v<decltype(a), double> << std::endl;
    std::cout << std::is_same_v<decltype(a1), double> << std::endl;

}