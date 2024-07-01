#include "sing.h"
static Sing::Init init;
auto singletonInst2 = singletonInst->val;

int main(int argc, char** argv) {
    std::cout << "get value: " << singletonInst2 << '\n';
    std::cout << singletonInst << std::endl;
//    singletonInst = nullptr;//有这一行，系统仍可以编译，但是运行会系统崩溃
    //singletonInst是单例的入口，有被修改的风险

    std::cout << singletonInst->val << std::endl;
}
