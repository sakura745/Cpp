#include <iostream>

void fun(int a, int /*b*/) {

}

int main() {
    std::cout << /* "*/" /* "/*" */ << std::endl;//输出  /*
}