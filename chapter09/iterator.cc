#include <iostream>
#include <vector>

int main() {
    std::vector<int> a{1, 2, 3};
    auto b = a.begin();
    auto e = a.end();
    for (auto ptr = b; ptr < e; ++ptr) {
        std::cout << *ptr << ' ';
    }
    std::cout << std::endl;

    auto f = a.rbegin();//reverse
    auto g = a.rend();
    for (auto ptr = f; ptr < g; ++ptr) {
        std::cout << *ptr << ' ';
    }
    std::cout << std::endl;

    std::vector<int> a1{1, 2, 3};
    auto b1 = a1.cbegin();
    auto e1 = a1.cend();
    for (auto ptr = b1; ptr < e1; ++ptr) {
//        *ptr = 3;//illegal:迭代器只读
        std::cout << *ptr << ' ';
    }
    std::cout << std::endl;

    const std::vector<int> a2{1, 2, 3};
    auto b2 = a2.begin();
    auto e2 = a2.end();
    for (auto ptr = b1; ptr < e1; ++ptr) {
        //*ptr = 3;//illegal。常量数组，只读
    }

}