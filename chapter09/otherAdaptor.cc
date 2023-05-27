#include <iostream>
#include <vector>
#include <ranges>//引入ranges c20

bool isEven(int i) {
    return i % 2 == 0;
}

int Square(int i) {
    return i * i;
}
int main() {
    std::vector<int> v{1, 2, 3, 4, 5};
    for (auto i: v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl << "-----------------" << std::endl;

    for (auto i: std::ranges::filter_view(v, isEven/*传入自定义的预测器*/)) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    for (auto i: std::views::filter(v, isEven)) {//和结果一样。两种表达方式
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    auto x = std::views::filter(isEven);
    for (auto i: x(v)/*法一*/) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (auto i: v | x/*法二*/) {//'|'用来模拟linux的管道符，前面的输出，作为后面的输入
        std::cout << i << ' ';
    }
    std::cout << std::endl << "-----------------" << std::endl;

    for (auto i: std::ranges::transform_view(v, Square)) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (auto i: std::views::transform(v, Square)) {
        std::cout << i << ' ';
    }
    std::cout << std::endl << "-----------------" << std::endl;

    auto y = std::views::transform(Square);
    for (auto i : v | x | y) {
    //for (auto i : y(x(v)) {//也可以，但是可读性没有pipe高
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    //甚至可以
    auto z = std::views::filter(isEven) | std::views::transform(Square);
    for (auto i : v | z) {
        std::cout << i << ' ';
    }
    std::cout << std::endl << "-----------------" << std::endl;

    //filter 和 transform等都对应了相应的函数在algorithm中
    //为什么c20还要引入呢
    //ranges 表达起来更简单； ranges求值过程是缓式求值。
    //缓式求值是一种评估算法，其中表达式的求值是通过延迟完成的，直到需要它们的结果为止。
    //这种方法主要用于惰性求值和函数式编程中。缓式求值是一种优化技术，它可以减少展开计算中的重复部分和内存占用，
    //从而提高程序的执行效率。当你使用缓存求值时，你可以在需要时生成表达式的值，而不是在最初计算时就生成所有的值。
    //这有助于优化和节省计算资源，特别是在处理大量数据时。


    for (int i : std::ranges::iota_view{1, 10/*类似于迭代器，1是begin()，10是end()*/}) {//因此是1到9不包含10
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (int i : std::views::iota(1, 10)) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (int i : std::views::iota(1)/*没有第二个数，就是无限数组*/ | std::views::take(9)/*接收9个元素*/) {
        std::cout << i << ' ';
    }

}
