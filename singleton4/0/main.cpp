#include "sing.h"

int main(int argc, char** argv) {
    std::cout << "get value: " << singletonInst.val << '\n';
    //输出为
//    Sing construct
//    get value: 100
//    Sing destroy

    //singletonInst的构造（初始化）在sing.cpp中
    //调用和初始化分开了
}
