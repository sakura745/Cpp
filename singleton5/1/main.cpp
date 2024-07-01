#include "sing.h"

static Sing::Init init;
auto singletonInst2 = singletonInst->val;

//Type X; 全局对象如何初始化：
//情况一：X可以在编译期被求值的同时，编译器决定在编译期对其求值时，系统会在编译时计算初始值，初始值等相关信息会保留在可执行
//程序里，在操作系统加载可执行程序时，将其中的数值放到一块内存里，再将内存和X相关联 ———— 常量初始化
//情况二：不能在编译期求值。在编译完成之后，运行之前的这段期间，不能对X的初始值有任何的假设。系统会记录X的尺寸，将和其他
//尺寸类似的变量组织到一起，计算到底多大后，将尺寸信息置于可执行程序中。操作系统按照尺寸开辟内存空间，将开辟的空间中的数据
//都设置为0，空间交给程序使用，将该组织到一起的内存映射给各个对象。 ———— 零初始化
//零初始化是第一步，还会对其进行按照翻译单元的初始化内容进行初始化
//缺省初始化：如果是抽象数据类型，则调用构造函数；如果是内建类型，则啥也不干


int main(int argc, char** argv) {
    std::cout << "get value: " << singletonInst2 << '\n';
    std::cout << singletonInst.get() << std::endl;
    std::cout << singletonInst->val << std::endl;
}
