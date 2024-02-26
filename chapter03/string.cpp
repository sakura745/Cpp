#include <iostream>
#include <string>

int main() {
    std::string x("Hello World");//标准库字符串
    std::string y = x;
    y = y + "!";
    std::cout << x << '\n' << y << std::endl;
    std::string x2 (3, 'a');
    std::cout << x2 << std::endl;
    std::cout << (y == x) << std::endl;
    y = "New String";//赋值.内建字符串
    y = y + "String";//拼接

    //y = "Hello" + "Hello String" + x;//error
    y = std::string("Hello") + "Hello String" + x; //legal.说明先给出一个string，在string基础上可以拼接
    y = "Hello String" + std::string("Hello") + x; //legal.说明先给出一个string，在string基础上可以拼接

    auto ptr = y.c_str();//转换为C风格字符串  ptr type is const char*.
    std::cout << ptr << std::endl;//C风格会输出直到遇到/0停止

}
