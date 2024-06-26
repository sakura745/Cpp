#include <iostream>

int main() {
    //cin cout是以终端来说的。
    int x = 100;//00000000 00000000 00000000 01100100 :int 4 bytes
    std::cout << x << std::endl;//计算机通过输出流cout把二进制的数“格式化”为“1 0 0”三个字符输出

    //假如输入100，计算机通过输入流cin把“1 0 0”三个字符“解析”为二进制的数字
    int y;
    std::cin >> y;

    union {//使用一块内存即表示a也表示b
        int a;
        float b;
    };
    a = 100;//a和b共用同一块内存
    std::cout << a << std::endl;//100所对应的二进制，整型形式
    std::cout << b << std::endl;//100所对应的二进制表示为float 浮点型形式

}