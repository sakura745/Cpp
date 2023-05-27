#include <iostream>

inline/*防止报错重定义*/ void fun() {
    std::cout << "Hello World~" << std::endl;
}

