#include "sing.h"
#include <memory>
#include <iostream>

//声明了一块内存，零初始化 + 平凡的初始化
//在该内存上构造singletonInst
alignas(Sing)/*按照Sing对齐内存*/ char singBuf[sizeof(Sing)];

Sing::Init::Init() {
    auto& count = RefCount();
    auto ori = count.fetch_add(1);
    if (ori == 0) {
        Sing* ptr = reinterpret_cast<Sing*>(singBuf);
        new (ptr) Sing();//placement new
    }
}

Sing::Init::~Init() {
    auto& count = RefCount();
    auto ori = count.fetch_sub(1);
    if (ori == 1) {
        Sing* ptr = reinterpret_cast<Sing*>(singBuf);
        ptr->~Sing();//placement delete
    }
}
