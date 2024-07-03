#include "sing.h"
#include <memory>
#include <iostream>

Sing* singletonInst;

//不像第六品中在sing.cpp的这个位置设置std::atomic<unsigned>引用计数变量是因为atomic的缺省构造函数有两个版本，
//在c11-c20之前是平凡的。从c20开始，是值初始化，使用T()初始化，但并不能保证是平凡的。
//如果使用的为c20可能会出现第五品的未定义的行为
//因此要放到类中构造静态成员函数，在函数中构造
Sing::Init::Init() {
    auto& count = Sing::Init::RefCount();
    auto ori = count.fetch_add(1);//fetch_add 原子的加，返回值为旧值，所以下面的if是 == 0
    //auto ori = Sing::Init::RefCount().fetch_add(1);在函数实现起来和上两行代码是等效的，
    //但在性能上会逊于上两行。是因为如果频繁的使用ori，就会频繁的调用RefCount函数
    //但是先将其返回值绑定到一个对象，再对对象操作，会省去调用函数的算力
    if (ori == 0) {
        singletonInst = new Sing();
    }
}

Sing::Init::~Init() {
    auto& count = Sing::Init::RefCount();
    auto ori = count.fetch_sub(1);//fetch_sub 原子的减，返回值为旧值，所以下面的if是 == 1
    if (ori == 1) {
        delete singletonInst;
        singletonInst = nullptr;
    }
}