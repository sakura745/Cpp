#include <iostream>

int main() {
    int x = 3;
    int &ref = x;//reference
    std::cout << ref << '\n';
    ref = ref + 1;
    std::cout << x << '\n';
}

