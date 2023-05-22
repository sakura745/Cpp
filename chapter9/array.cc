#include <iostream>
#include <array>//引入array
#include <type_traits>

void fun(int* ){

}
void print(std::array<int, 3>& a) {
    for (auto i: a) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}
int main() {
    std::array<int, 3> a;//缺省初始化，可能导致值是乱的
    std::array<int, 3> b = a;//提供了复制操作
    std::cout << std::is_same_v<std::array<int, 3>::value_type, int> << std::endl;

    std::array<int, 3> a1 = {1, 2, 3};//aggregate initialization
    std::cout << a1[100] << std::endl;//乱值
//    std::cout << a1.at(100) << std::endl;//系统崩溃
    std::cout << a1.front() << std::endl;//第一个
    std::cout << a1.back() << std::endl;//最后一个
    fun(a1.data()/*返回int* 指向数组第一个元素*/);

    std::cout << a1.empty() << std::endl;//0
    std::cout << a1.size() << std::endl;//3
    std::cout << a1.max_size() << std::endl;//a1中最多包含多少个元素，3

    a1.fill(100);//填充
    std::cout << a1[0] << ' '
              << a1[1] << ' '
              << a1[2] << ' ' << std::endl;

    std::array<int, 3> x{1, 2, 3}, y{4, 5, 6};
    print(x);
    print(y);
    x.swap(y);//交换，很慢
    print(x);
    print(y);

    //比较操作类型要一样，
    std::array<int, 3> a2;
    std::array<int, 4> b2;
    //a2 < b2;//illegal
    //如何比较，字典序：先比较两个数组第一个元素，如果两个元素相等，则比较第二个元素。如果不相等，则直接出结果。



}