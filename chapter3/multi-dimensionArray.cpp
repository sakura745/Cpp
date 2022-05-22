#include <iostream>
#include <type_traits>
#include <typeinfo>

using A = int[4];
using A2 = int[3][4];
int main() {
    int x1[3];

    int x2[3][4] = {};//x2[3],三个元素。每个元素类型都为int [4]
    //A x2[3];->int[4] x2[3],注意维度
    x2[0];//it's type is int [4]
    std::cout << sizeof(int) << '\n';
    std::cout << sizeof(x2[0]) << '\n';
    std::cout << std::is_same_v<decltype(x2[0]), int(&)[4]> << '\n';//locator value with reference.
    std::cout << typeid(x2[0]).name() << std::endl;
    /*
     *  x2[0] ->int [4]
     *  x2[3][4]:
     *  int int int int | int int int int | int int int int
     *  x3[4][3]:
     *  int int int | int int int | int int int | int int int
     */
    int y[3][4] = {1, 2, 3, 4, 5};//int:1 int:2 int:3 int:4 | int:5 int:0 int:0 int:0 | int:0 int:0 int:0 int:0
    int y2[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}};//int:1 int:2 int:3 int:4 | int:5 int:6 int:7 int:8 | int:0 int:0 int:0 int:0
    int y3[3][4] = {{1, 2, 3}, {5, 6, 7}};//int:1 int:2 int:3 int:0 | int:5 int:6 int:7 int:0 | int:0 int:0 int:0 int:0
    int y4[3][4] = {{1, 2, 3}, {4, 5, 6, 7}};//int:1 int:2 int:3 int:0 | int:4 int:5 int:6 int:7 | int:0 int:0 int:0 int:0
    //int y5[][] = {1, 2, 3, 4}; error
    int y6[][2] = {1, 2, 3, 4};//legal
    int y7[][3] = {1, 2, 3, 4};
    std::cout << sizeof(y7) << ' ' << sizeof(int) << '\n';
    std::cout << std::is_same_v<decltype(y7), int[2][3]> << '\n';
    //int y8[][] = {{1, 2, 3, 6}, {4, 5, 6, 7}};error
    //int y9[][] = {{1, 2, 3}, {4, 5, 6, 7}};error
    int y10[][3][4] = {1, 2, 3};//legal
    //int y10[3][][4] = {1, 2, 3};error

    //multi dimension array traverse 1
    for (auto& p : y) {//& 通过c++insights
        for (auto q : p) {
            std::cout << q << ' ';
        }
        std::cout << '\n';
    }

    //multi dimension array traverse 2
    size_t index0 = 0;
    while (index0 < std::size(y)) {
        size_t index1 = 0;
        while (index1 < std::size(y[0])) {
            std:: cout << y[index0][index1] << ' ';
            index1 = index1 + 1;
        }
        std::cout << std::endl;
        index0 = index0 + 1;
    }


    auto ptr = y;//int (*ptr)[4] = y;

    auto ptr2 = y10;
    //int (*ptr2)[3][4] = y10;
    //A2 *ptr2 = y10;
    auto ptr3 = ptr2[0];//int (*ptr3)[4] = ptr2[0];

    //traverse with pointer
    auto pt = std::begin(x2);
    while (pt != std::end(x2)) {
        auto pt2 = std::begin(*pt);
        while (pt2 != std::end(*pt)) {
            std::cout << *pt2 << ' ';
            pt2 = pt2 + 1;
        }
        pt = pt + 1;
        std::cout << std::endl;
    }


}
