#include "sing.h"//通过该头文件，间接的引入了singletonInst的声明

int main(int argc, char* argv[]) {
    std::cout << "get value: " << singletonInst.val << '\n';
    Sing sing2;//该行代码可以运行，没有禁止构造其他对象
}
