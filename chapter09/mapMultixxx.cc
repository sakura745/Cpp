#include <iostream>
#include <map>//引入map
#include <set>//引入multiset

std::pair<const int, bool> fun() {
    //....
    return {};
}

void fun1(const std::map<int, bool>& m) {
//    m[3];//illegal 因为函数是编译期运行的，不能保证m中的key存在3
//改为
    auto ptr = m.find(3);
    if (ptr != m.end()) {
        ptr->second;
    }
}
int main() {
    std::map<int, bool> m{{3, true}, {2, true}, {1, true}};

    for (auto rbTreeIterator = m.begin(); rbTreeIterator != m.end(); ++rbTreeIterator) {
        auto p = *rbTreeIterator;//p类型是 std::pair<const int, bool>
        std::cout << p.first << ' ' << p.second << std::endl;
    }
    std::cout << "------------------" << std::endl;

    for (auto& item: m) {
        std::cout << item.first << ' ' << item.second << std::endl;
    }
    std::cout << "------------------" << std::endl;

    auto res = fun();
    auto [res1, res2] = fun();//绑定。res1 res2与item一样
    //可修改为
    for (auto& [k, v] : m) {//map通常使用的方式
        std::cout << k << ' ' << v << std::endl;
    }
    std::cout << "------------------" << std::endl;

    m.insert(std::pair<const/*const可有可无：没有，系统隐式转换*/ int, bool>(5, true));
    m.emplace(4, true);//不需要pair

    m.erase(3);//给一个key就行或者是迭代器

    auto ptr = m.find(2);//给一个key
    std::cout << ptr->first << ' ' << ptr->second << std::endl;

    std::cout << m[2] << std::endl;//元素访问
    std::cout << m.at(2) << std::endl;//元素访问
    //对于[]访问来说，如果访问的元素不在map中，则会新建该节点。m[100]会新建，100对应的value呢，会选择零初始化
    std::cout << m[100] << std::endl;//输出int() 也就是0

    fun1(m);
    std::cout << "------------------" << std::endl;

    std::set<int> s{1, 3, 1};
    for (auto& i: s) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    std::multiset<int> s1{1, 3, 1};//允许重复的键
    for (auto& i: s1) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    auto ptr2 = s1.find(1);//迭代器指向首个
    ++ptr2;

    std::cout << s.count(1) << std::endl;//元素个数 输出0或者1
    std::cout << s1.count(1) << std::endl;//元素个数 输出0 或者1，2，3...

    //寻找1的区间
    auto a = s1.lower_bound(1);
    auto b = s1.upper_bound(1);

    for (auto p = a; p != b; ++p) {
        std::cout << *p << ' ';
    }
    std::cout << std::endl;

    //区间需要两行代码，麻烦
    auto c = s1.equal_range(1);//返回pair
    auto [e, f] = s1.equal_range(1);//bind
    for (auto p = c.first; p != c.second; ++p) {
        std::cout << *p << ' ';
    }
    std::cout << std::endl;
    for (auto p = e; p != f; ++p) {
        std::cout << *p << ' ';
    }
    std::cout << std::endl;

}
