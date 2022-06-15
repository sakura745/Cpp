#include <iostream>
#include "header.h"

extern "C"
//define
int Add(int x, int y) {
    return x + y;
}
int Sub(int x, int y) {
    return x - y;
}
int main() {
    int z = Add(2, 3);
    std::cout << z << std::endl;
    z = Sub(2, 3);
    std::cout << z << std::endl;
}

