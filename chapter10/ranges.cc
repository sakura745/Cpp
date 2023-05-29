#include <iostream>
#include <algorithm>
#include <vector>
#include <ranges>
#include <map>

auto fun() {
    return std::vector<int> {1, 2, 8, 3, 4, 5};
}
int main() {
    std::vector<int> x{1, 2, 8, 3, 4, 5};
    auto it = std::find(x.begin(), x.end(), 3);
    std::cout << *it << std::endl;

    auto it2 = std::ranges::find(x/*用容器*/, 3);
    std::cout << *it2 << std::endl;

    auto it3 = std::ranges::find(fun(), 3);//it3的类型是std::ranges::dangling
//    std::cout << *it3 << std::endl;//illegal

    std::map<int, int> m{{2, 3}};
    auto it4 = std::ranges::find(m, 3, &std::pair<const int, int>::second/*指向第二个元素的指针*/);
    std::cout << it4->first << ' ' << it4->second << std::endl;


}
