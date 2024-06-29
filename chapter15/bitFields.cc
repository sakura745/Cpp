#include <iostream>

struct A {
    bool b1;
    bool b2;
};

struct A1 {//多个位域对象可能被打包存取
    bool b1 : 1/*位域：表示b1只占1位，1bit。1也可以写成2到8其中一个*/;
    bool b2 : 1;
};
struct A2 {
    bool b1 : 1;
    bool b2 : 1;
    bool b3 : 8;
    int x;
    int y : 10;//表示y的范围为2^10
    char ch : 10;//通常char占一个字节:8位。超过之后，取值受类型（char）的影响。
};
struct A3 {
    char b : 1000;//1000 / 8 = 125 -> 128(二的次幂)
};
int main() {
    std::cout << sizeof(A) << std::endl;//输出为2，每个bool使用一个字节
    std::cout << sizeof(A1) << std::endl;//输出为1，每个bool使用一个比特

    A2 obj;
    &obj.x;
//    bool& ref = obj.b1;//illegal 不能对位域的对象取地址（因为已经打破字节为最小单位，变成位了），非 常量引用等

    const bool& ref2 = obj.b1;//legal 可以用常量引用：ref2本质是绑定在一个临时量上，其类型是位域的类型，并以该位域的值
    //复制初始化到临时量上

    obj.ch = 1024;
    std::cout << static_cast<int>(obj.ch) << std::endl;

    std::cout << sizeof(A3) << std::endl;//输出128
}