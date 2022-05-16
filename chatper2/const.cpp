#include <iostream>
#include <type_traits>
void fun(const int& param) {

}
int main() {
    int x = 3;
    fun(x);
    fun(3);//equal to "const int& x = 3";

    constexpr const int* ptr = nullptr;
    std::cout << std::is_same_v<decltype(ptr), const int* const> << std::endl;//same return true, otherwise false.
}