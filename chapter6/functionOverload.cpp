#include <iostream>

int fun(int x) {
    return x + 1;
}
double fun(double x) {
    return x + 1;
}
int main() {
    std::cout << fun(3) << std::endl;
    std::cout << fun(3.5) << std::endl;
}

