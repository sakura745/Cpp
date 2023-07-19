#include <iostream>
#include <vector>

int main() {
    std::vector<int> x;//default constructor. zero element.
    std::vector<int> x1 = {1, 2, 3};//aggregate initialization.
    //x1 = x;//legal. array cannot copy, vector can
    std::vector<int> x2(3);//initialization numbers is 3 and elements are 0.
    std::vector<int> x3(3, 1);//initialization numbers is 3 and elements are 1.
    std::vector<int> x4{1, 2, 3};//initialization list.Same as x1.

    std::vector<float> y;

    std::cout << x4.size() << std::endl;
    std::cout << x.empty() << std::endl;//return bool value
    std::cout << x4.empty() << std::endl;
    x4.push_back(2);
    std::cout << x4.size() << std::endl;
    x4.pop_back();
    std::cout << x4.size() << std::endl;
    //按照字典序进行比较
    std::cout << (x4 > x1) << std::endl;
    std::cout << (x4 == x1) << std::endl;


    std::cout << x4[2] << std::endl;//if it overflowed, don't output  exception
    std::cout << x4.at(2) << std::endl;//if it overflowed, output exception
    std::begin(x4);//函数
    x4.begin();//方法

    //traversal 1
    auto a = x4.begin();
    while (a != x4.end()) {
        std::cout << *a << ' ';
        a = a + 1;
    }
    std::cout << std::endl;
    //traversal 2
    for (auto val : x4) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;
    //multi-dimension vector
    std::vector<std::vector<int>> z;
    z.push_back(std::vector<int>());
    z[0].push_back(1);
    std::cout << z[0][0] << std::endl;


    std::cout << x1.size() << std::endl;//.
    std::vector<int>* p = &x1;
    std::cout << (*p).size() << std::endl;//.
    std::cout << p->size() << std::endl;//->

}
