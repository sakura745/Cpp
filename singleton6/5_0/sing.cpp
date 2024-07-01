#include "sing.h"
#include <memory>
#include <iostream>

constinit/*c20表示强制在编译期初始化*/ std::unique_ptr<Sing> singletonInst;
//不能将constinit换成constexpr，因为修饰变量时，不仅会让其在编译期运行，同时还会给一个const限定符，让其变成常量
//singletonInst.reset就不能修改了

Sing::Init::Init() {
    if (!singletonInst) {
        singletonInst.reset(new Sing());
    }
}

