#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

int main() {
//    //cin绑定到cout上了
//    std::cout << "What's your name\n";//缺省状态下会有缓冲区
//    std::cerr << "What's your name\n";//缺省状态下是unitbuf
//    std::string name;
//    std::cin >> name;
//    std::cout << "---------------" << std::endl;

    std::ios::sync_with_stdio(false);
    std::cout << "a\n";
    std::printf("b\n");
    std::cout << "c\n";
    //输出结果是可能的输出，能确保的是ac的顺序，不能确保b在哪个位置
}