#include <iostream>

#include <cstdio>//引入printf

int main() {
    std::cout << "Hello World" << std::endl;
    printf("Hello WOLRD\n");

    int x = 10;
    std::cout << "I have " << x << " pens\n";
    printf("I have %d pens\n", x);
}
