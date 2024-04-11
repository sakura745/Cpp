#include <iostream>
int* ptr;//default initialization pointer, ptr is nullptr
void fun(int) {
    std::cout << "fun3(int) is called.\n";
}
void fun2(int*) {
    std::cout << "fun3(int*) is called.\n";
}

void fun3(void* param) {
    std::cout << (param + 1) << '\n';//illegal 指针是void* 不能进行增加和减少操作
}

void fun4(int* param) {
    if (param) {
        *param = *param + 1;
    } else {
        try {
            throw std::runtime_error("Null pointer exception.");
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

struct Str {
    //...
};
void fun5(Str) {}
void fun5(Str*) {}
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
        if (!ptr) {
            throw std::runtime_error("Null pointer detected.");//空指针不能被解引用，会造成异常。
            // C++中没有空指针异常机制，因此需要自定义异常
        }
        std::cout << *ptr << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "---------------" << std::endl;

    fun(0);//会匹配到int
    int* p = 0;//指针的0表示的是nullptr。意思是int隐式转化为nullptr，但nullptr不能隐式转换为int
    fun2(p);//会匹配到int*。
    fun2(nullptr);
    std::cout << "---------------" << std::endl;

    int x2 = 52;
    int* pp = &x2;
    *pp;//dereference
    std::cout << pp << '\n';
    pp = pp - 1;//decrease address with type size. such as int, p's address - 4(int)
    std::cout << pp << '\n';
    pp = pp + 1;//increase address with type size. such as int, p's address + 4(int)
    std::cout << pp << '\n';
    int* q = &x2;
    std::cout << (pp == q) << '\n';

    int y2 = 42;
    int* ptr2 = &y2;
    char* ptr3 = nullptr;

    std::cout << ptr2 << '\n';
    std::cout << (ptr2 + 1) << '\n';

    fun3(ptr2);
    fun3(ptr3);
    //指针类型为void*时，对其指针进行增加和减少。虽然编译器不会在编译时报错，但结果未定义，可能会导致程序出现意外行为。
    //void*作为指针万金油，可以和任何指针类型进行转换，因此可以作为占位符，对指针信息的保护。

    int* ptr4 = nullptr;
    fun4(ptr4);//空指针异常

    Str obj;
    Str* ptrStr = &obj;
    fun5(obj);
    fun5(ptrStr);//等价于fun5(&obj);
    //传地址的开销远小于传值。传值会有额外的内存复制操作，函数内的操作在额外复制的空间上进行操作。
}

