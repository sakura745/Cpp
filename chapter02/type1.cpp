#include <iostream>
#include <limits>

struct Str {
    char b;
    int x;
};
int main() {

    int x = 10;
    char y = 'a';

    std::cout << "sizeof:" << std::endl;
    std::cout << sizeof(x) << '\n';
    std::cout << sizeof(int) << '\n';
    std::cout << sizeof(y) << '\n';
    std::cout << sizeof(char) << '\n';
    std::cout << "---------" << std::endl;

    std::cout << "min max:" << std::endl;
    std::cout << std::numeric_limits<int>::min() << std::endl;
    std::cout << std::numeric_limits<int>::max() << std::endl;
    std::cout << std::numeric_limits<unsigned int>::min() << std::endl;
    std::cout << std::numeric_limits<unsigned int>::max() << std::endl;
    std::cout << "---------" << std::endl;

    unsigned int z = std::numeric_limits<unsigned int>::max();
    z = z + 1;
    std::cout << z << std::endl;
    int w = std::numeric_limits<int>::max();
    w = w + 1;
    std::cout << w << std::endl;
    std::cout << "---------" << std::endl;

    std::cout << "alignof:" << std::endl;
    std::cout << alignof(int) << std::endl;
    std::cout << alignof(char) << std::endl;
    std::cout << sizeof(Str) << std::endl;


}

