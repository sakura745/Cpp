#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " param1 param2 \n";
        return -1;
    }
    std::cout << "argc = " << argc << '\n';
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << '\n';
    }
}
//可以转到cmake-build-debug中用命令行输出
