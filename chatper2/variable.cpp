#include <iostream>
#include "variable2.cpp"
extern int g_x;//declaration
//extern int g_x = 10; it means from declaration to definition

int main() {
    int x;//default initialized value is anything
    std::cout << g_x << std::endl;
    std::cout << x << std::endl;
    int y = 10;//copy initialization
    int z(10);//directly initialization1
    int w{10};//directly initialization2
}

