#include "sing.h"
#include <memory>
#include <iostream>

MyUniquePtr<Sing> singletonInst;
//不能再这里声明为constinit MyUniquePtr，因为MyUniquePtr的构造函数是运行期运行，而constinit初始化为编译期。系统无法编译
//去修改MyUniquePtr构造函数

Sing::Init::Init() {
    if (!singletonInst) {
        singletonInst.reset(new Sing());
    }
}

static Sing::Init init;