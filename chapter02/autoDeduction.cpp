#include <iostream>
#include <type_traits>
int main() {
    int x1 = 3;
    int& ref = x1;//x1 type int, ref type int&
    auto ref2 = ref;//auto导致类型退化，ref2从ref的int&退化到int
    std::cout << std::is_same_v<decltype(ref2), int> << std::endl;

    const auto y = 3;
    std::cout << std::is_same_v<decltype(y), const int> << std::endl;
    constexpr auto y1 = 3;
    std::cout << std::is_same_v<decltype(y1), const int> << std::endl;

    //虽然不会产生退化，但会引入&类型。
    const auto& y2 = 3;
    std::cout << std::is_same_v<decltype(y2), const int&> << std::endl;

    const int z = 4;//z type is const int
    auto z4 = z;//z作为右值，类型退化为int，z4类型为int
    std::cout << std::is_same_v<decltype(z4), int> << std::endl;
    //auto 推导在此过程中会忽略顶层 const 限定符，但保留底层 const 限定符（用于指向常量的指针或引用）。
    //因此，当 auto 推导类型时，z 被看作是右值（rvalue）。右值是指表达式的值，而不是存储它的内存位置。

    const auto z2 = z;//z作为右值，类型退化为int，z2有const，compiler为了达到完美的匹配，z2类型为const int
    std::cout << std::is_same_v<decltype(z2), const int> << std::endl;

    auto& z6 = z;//首先，z6是&类型，因此一定会推导出&。其次，当编译器看到auto&，z就不会退化
   	//z6类型为const int&
    std::cout << std::is_same_v<decltype(z6), const int&> << std::endl;

    const int& z7 = 4;
    auto& z8 = z7;
    std::cout << std::is_same_v<decltype(z8), const int&> << std::endl;
    auto z9 = z7;//const和&都退化掉了
    std::cout << std::is_same_v<decltype(z9), int> << std::endl;

    int w[3] = {1,2,3};
    auto w1 = w;
    std::cout << std::is_same_v<decltype(w1), int*> << std::endl;
    auto& w3 = w;
    std::cout << std::is_same_v<decltype(w3), int(&)[3]> << std::endl;

    std::cout << std::endl << "Decltype:" << std::endl;
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
    decltype(auto) a1 = 3.5 + 15l;//c14
    std::cout << std::is_same_v<decltype(x), double> << std::endl;
    std::cout << std::is_same_v<decltype(a), double> << std::endl;
    std::cout << std::is_same_v<decltype(a1), double> << std::endl;
    std::cout << "------------------------" << std::endl;

    //给定一个类型为 const int 的变量，想要根据自动推导的类型也获得const int型，只能通过decltype来获得
    //因为auto 会有类型退化，auto& 会引入&
    const int val = x1;
    auto val2 = val;
    std::cout << std::is_same_v<decltype(val2), int> << std::endl;
    auto& val3 = val;
    std::cout << std::is_same_v<decltype(val3), const int&> << std::endl;
    decltype(auto) val4 = val;
    decltype(val) val5 = val;
    std::cout << std::is_same_v<decltype(val4), const int> << std::endl;
    std::cout << std::is_same_v<decltype(val5), const int> << std::endl;

}