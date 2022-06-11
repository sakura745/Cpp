#include <iostream>
#include <vector>

int main() {
    int x = 3;
    while (x) {//while (int x = 3) legal
        std::cout << x << std::endl;
        --x;
    }

    int y = 3;
    do {
        std::cout << y << std::endl;
        --y;
    } while (y);

    int a = 0;
    while (a > 0) {
        std::cout << a << std::endl;
        --a;
    }

    int b = 0;
    do {
        std::cout << b << std::endl;
        --b;
    } while (b > 0);

    for (int c = 0; c < 5; ++c) {
        std::cout << c << std::endl;
    }

    std::vector<int> arr{1, 2, 3, 4, 5};
    for (int v : arr) {//读取arr中元素
        std::cout << v << '\n';
    }

    std::vector<std::string> arr2{"H", "E", "L"};
    //for (std::string v : arr2) {//读取arr2中元素，相当于再construct 一个 v，然后再 deconstruct
    //for (const std::string& v : arr2) {//改为常量引用，更有效
    for (auto& v : arr2) {//系统自动推导
        std::cout << v << '\n';
    }

    std::vector<int> arr3{1, 2, 3, 4, 5};
    for (auto& v : arr3) {//对arr3中元素进行修改，写操作
        v = v + 1;
    }
    for (auto v : arr3) {
        std::cout << v << '\n';
    }

    std::vector<bool> arr4{true, false, true};
    //for (auto& v : arr4) {//error 是因为bool内部逻辑问题
    for (auto&& v : arr4) {//legal 使用万能引用 universal reference
        v = false;
    }

}
