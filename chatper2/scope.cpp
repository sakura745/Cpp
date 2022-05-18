#include <iostream>
namespace MyNS{
    int x = 4;
    void fun() {

    }
    using MyInt = int;
    //using MyInt = float;
}
using MyInt = float;
void fun() {
    int x = 4;
}
int x = 3;
int main() {
    int x = 4;
    {
        int x = 5;
    }
    std::cout << x << std::endl;
}

