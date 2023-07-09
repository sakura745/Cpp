#include <iostream>
#include <stdexcept>
#include <memory>
#include <fstream>

void fun() {
    throw std::runtime_error("Invalid input");
}

void fun2() {
    int* ptr = new int [3];
    throw 11;
    delete []ptr;
}//不是 异常安全 的代码，因为在通过栈展开销毁的ptr，只是销毁了ptr的指针，没有销毁ptr所指向的内存，也就是int [3]的内存存在泄漏
//可以通过使用智能指针来保证代码属于 异常安全

void fun3() {
    std::unique_ptr<int> ptr = std::make_unique<int>(3);//通过调用智能指针的析构函数来进行内存销毁
    throw 11;
}

//文件的书写，使用c++风格而不是c风格，来代码是 异常安全 的
void fun4() {
    std::ofstream of;
    //...
    throw 11;
}
//通过使用类的方式，来让代码向 异常安全 更进一步。

int main() {
    try {
        fun();
        fun2();
        fun3();
        fun4();
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (std::bad_alloc& e) {
        std::cout << e.what() << std::endl;
    }

}