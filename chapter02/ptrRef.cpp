#include <iostream>
int* ptr;//default initialization pointer, ptr is nullptr
void fun(int) {
    std::cout << "fun(int) is called.\n";
}
void fun(int*) {
    std::cout << "fun(int*) is called.\n";

}
int main() {
    int x = 42;
    int y = 56;

    //指针和数据类型相同：指针存放的是首地址，之后取多大的空间是根据指针类型确定的。
    int*/* 这个*是指针的意思 */ p1 = &x;

    p1 = &y;//指针指向的内存所存取的地址从x的地址变成y的地址
    char z = 'c';
    char* p2 = &z;
    std::cout << sizeof(x) << '\n';
    std::cout << sizeof(z) << '\n';

    //指针存储的内存地址为8位，因为大多数都为64位机
    std::cout << sizeof(p1) << '\n';
    std::cout << sizeof(p2) << '\n';
    std::cout << &x << '\n';//get address
    std::cout << */*这个*是解引用的意思*/p1 << '\n';//Dereference

    try {
        if (ptr) {
            std::cout << *ptr << std::endl;
        } else {
            throw std::runtime_error("Null pointer detected.");//空指针不能被解引用，会造成异常。
            // C++中没有空指针异常机制，因此需要自定义
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "---------------" << std::endl;

    fun(0);//会匹配到int
    int* p = 0;//指针的0是nullptr
    fun(p);//会匹配到int*。
    fun(nullptr);
}

