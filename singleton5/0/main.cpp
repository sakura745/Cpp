#include "sing.h"
static Sing::Init init;//为了控制初始化的顺序。该翻译单元中，一定会先初始化init全局变量，
// 再初始化singletonInst等其他的全局变量
//先初始化init，会调用init初始化构造函数，然后定义singletonInst。

//定义为static是为了确保当多个翻译单元使用init时，没有重定义

auto singletonInst2 = singletonInst->val;

int main(int argc, char** argv) {
    std::cout << "get value: " << singletonInst2 << '\n';
}
