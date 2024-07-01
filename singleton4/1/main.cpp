#include "sing.h"

auto singletonInst2 = singletonInst.val;//singletonInst2 和 singletonInst初始化的顺序

//auto singletonInst3 = Sing::Instance().val;//则不会出现问题，因为singletonInst和singletonInst3都是调用的同一个
//全局对象
int main(int argc, char** argv) {
    std::cout << "get value: " << singletonInst2 << '\n';
}
