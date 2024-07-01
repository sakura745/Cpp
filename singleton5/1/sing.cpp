#include "sing.h"
#include <memory>
#include <iostream>

//std::unique_ptr<Sing> singletonInst;
//对于unique_ptr来说，其构造函数是constexpr。对于当前环境来讲，使用的是常量初始化。

MyUniquePtr<Sing> singletonInst;
//其构造函数没有constexpr，表示在运行期调用。因此系统会走零初始化+缺省初始化

Sing::Init::Init() {
    if (!singletonInst) {
        singletonInst.reset(new Sing());
    }
}

static Sing::Init init;