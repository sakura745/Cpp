#include <iostream>

int main() {
    int x = 3, y = 4;
    int &ref = x;//reference
    ref = y;//不表示引用的重新绑定，表示为把y赋值给ref(x)
    std::cout << ref << '\n';
    ref = ref + 1;
    std::cout << x << '\n';
}

