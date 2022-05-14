#include <iostream>

int main() {
    float x = 1.3;//type from double to float
    float y = 1.3f;//type from float to float

    long double z = 1.3;//type promotion
    int w = 'c';//type promotion

    unsigned a = -1;
    std::cout << a << '\n';

    bool b = 3;
    int c = b;
    std::cout << b << '\n';
    std::cout << c << '\n';
    if (4)// int to bool
        {}
    int q = -1;
    unsigned p = 3;
    std::cout << (q < p) << std::endl;

}