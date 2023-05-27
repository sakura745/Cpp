#include <iostream>
#include <vector>
#include <list>//引入list
#include <forward_list>//引入forward_list
#include <deque>//引入deque


std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)//运算符 << 重载，输出list元素
{
    for (auto &i : list)
        ostr << ' ' << i;

    return ostr;
}
int main() {

    //list
    std::list<int> a{1, 2, 3};
    std::vector<int> b{1, 2, 3};
    for (auto ptr = a.begin(); ptr != a.end(); ++ptr) {
        std::cout << *ptr << ' ';
    }
    std::cout << std::endl;
    std::cout << a.size() << std::endl;//list支持size

    b[2];//通过b第一个元素的指针，向后移动两个int大小内存。很容易的访问，随机访问成本较低
    //a[2];//illegal。而对于list 随机访问成本较高


    //为什么提供splice接口，是因为插入对list很容易
    std::list<int> list1 = {1, 2, 3, 4, 5};
    std::list<int> list2 = {10, 20, 30, 40, 50};
    auto it = list1.begin();
    std::advance(it, 2);//it向后移动2位
    list1.splice(it, list2);//拼接到it位置
    std::cout << "list1:" << list1 << '\n';
    std::cout << "list2:" << list2 << '\n';//list2空了


    //forward_list
    std::forward_list<int> c{1, 2, 3};
    for (auto ptr = c.begin(); ptr != c.end(); ++ptr) {
        std::cout << *ptr << ' ';
    }
    std::cout << std::endl;
    //std::cout << c.size() << std::endl;//illegal
    //forward_list支持不size。是因为forward_list目标是成本较低的线性表实现。就特意不实现size
    //pop_back push_back也不支持

    //xxx_after操作，是因为单向的缘故

    //deque 很少使用
    //支持 [] 随机访问

    //basic_string
    //stoi : string to int
    //to_string(int); int to string

}