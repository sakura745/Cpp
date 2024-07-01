#include "sing.h"
#include <memory>
#include <iostream>

static/*更安全，当然没有也行*/ unsigned singletonCount;
//为什么不会有static initialization order fiasco？
//因为singletonCount的类型是unsigned，为内建类型，零初始化后的缺省初始化是平凡的

Sing* singletonInst;
//选择使用Sing*来初始化singletonInst，因为Sing*指针是平凡的（无论类的构造是什么，类类型的指针都是平凡的）
//但为什么之前选用智能指针？是因为智能指针可以自己执行delete
//引入引用计数来控制销毁
//类似于shared_ptr的计数原理

Sing::Init::Init() {
    ++singletonCount;
    if (singletonCount == 1) {
        singletonInst = new Sing();
    }
}

Sing::Init::~Init() {
    --singletonCount;
    if (singletonCount == 0) {
        delete singletonInst;
        singletonInst = nullptr;//可有可无
    }
}