#include "sing.h"
static Sing::Init init;

auto singletonInst2 = singletonInst->val;

int main(int argc, char** argv) {
    Sing::Init init;//这么写没问题
    //但是假设用户在多个函数中写了多个代码，会导致数据竞争，导致多线程不安全
    
    std::cout << "get value: " << singletonInst2 << '\n';
    std::cout << singletonInst << std::endl;
    std::cout << singletonInst->val << std::endl;
}
