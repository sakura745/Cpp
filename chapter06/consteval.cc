#include <iostream>

//只能在编译期
consteval int fun(int x) {
    return x + 1;
}

int main() {
    constexpr int x = fun(3);

    //illegal
//    int y;
//    std::cin >> y;
//    return fun(y);
}