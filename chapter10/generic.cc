#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

int main() {
    std::vector<int> x(100);
    std::sort(std::begin(x), std::end(x));//sort是算法，独立于类
    std::sort(x.begin(), x.end());//begin end是方法，获取迭代器。但是对于容器可以通过方法来或缺迭代器。
    // 内建类型没有方法，只能通过算法来获取迭代器

    std::list<int> a;
    a.sort();//sort是方法，在类里面定义。不是算法

    int y[100];//内建类型不支持方法 没有y.sort()
    std::sort(std::begin(y), std::end(y));//也可以运行
    //对于vector 来说 begin end属于迭代器。
    //对于y[100]来说，begin end属于指针，也是迭代器。迭代器是模拟指针的，更广泛的一种指针。


    //unique需要是有序的。unique是删除连续的元素
    std::vector<int> v{1, 2, 2, 3, 4, 4, 5};
    // 使用 std::unique 函数去除重复元素
    auto last = std::unique(v.begin(), v.end());
    // 输出去重后
    for (auto it = v.begin(); it != last; ++it) {
        std::cout << *it << " ";//1 2 3 4 5
    }
    std::cout << std::endl;
    // 输出去重后的整体
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";//1 2 3 4 5 4 5 就意味着前几位是排序好，去重之后。剩余的元素不动，留下了 4，5
    }
    std::cout << std::endl;
}
