#include <iostream>

int main() {
    int x = 3;
    while (x) {//while (int x = 3) legal
        std::cout << x << std::endl;
        --x;
    }

    int y = 3;
    do {
        std::cout << y << std::endl;
        --y;
    } while (y);

    int a = 0;
    while (a > 0) {
        std::cout << a << std::endl;
        --a;
    }

    int b = 0;
    do {
        std::cout << b << std::endl;
        --b;
    } while (b > 0);
}
