#include <iostream>
#include <cstring>

int main() {
    char str[] = "Hello";//char [6] null-terminated string 建议
    char str2[] = {'H', 'e', 'l', 'l', 'o'};//char [5] 不建议
    char str3[] = {'H', 'e', 'l', 'l', 'o', '\0'};//char [5] 建议
    std::cout << strlen(str) << std::endl;
    std::cout << strlen(str2) << std::endl;//找到'\0'才会计算长度，输出结果不一定是多少
    std::cout << strlen(str3) << std::endl;

    auto ptr = str;
    auto ptr2 = str2;
    auto ptr3 = str3;

    //strlen是接收指针作为参数
    std::cout << strlen(ptr) << std::endl;
    std::cout << strlen(ptr2) << std::endl;
    std::cout << strlen(ptr3) << std::endl;
}
