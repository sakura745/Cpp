#include <iostream>
#include <map>//引入map
#include <set>//引入set

struct Str {};
struct Str1 {
    int x;
};

bool MyCmp(const Str1& lhs, const Str1& rhs) {
    return lhs.x < rhs.x;
}

int main() {
    std::map<char, int> m{{'a', 3}, {'b', 4}};//把'a'和3关联起来了
    std::cout << m['a'] << std::endl;

    std::set<int> s{100, 3, 7, 56};
    std::set<int> s2{3, 100, 7, 56};
    //set的键是通过int来定义的，任意的int值。set的值是bool值，键在set中，返回true，否则false
    //从数学角度来看，set是集合，集合里的元素顺序不重要。s和s2是一样的。
    std::set<int> s3{100, 100, 3, 7, 56};
    std::cout << s3.size() << std::endl;//size为4，重复元素不算。
    for (auto ptr = s.begin(); ptr != s.end(); ++ptr) {//遍历set
        std::cout << *ptr << ' ';//输出是有序的。因为set底层是红黑树，所以是中序遍历
    }
    std::cout << std::endl;

    std::set<Str> s4;//legal
    //std::set<Str> s5{Str{}};//illegal set赋值就报错。Str类型不能使用 < 。不能比较大小
    //set有个缺省的比较函数std::less

    std::set<int, std::greater<>> s6{100, 3, 7, 56};
    for (auto ptr = s6.begin(); ptr != s6.end(); ++ptr) {
        std::cout << *ptr << ' ';
    }
    std::cout << std::endl;

    std::set<Str1, decltype(&MyCmp)/*自定义比较器*/> s7({Str1{3}, Str1{5}}/*初始化列表*/, MyCmp/*函数指针*/);
    s7.insert(Str1{100});
    s7.emplace(4);///4直接赋给Str1中的x，避免构造。 gcc从9升到10解决了

    s7.erase(s7.begin());

    std::set<int> s8{1, 3, 5};
    auto ptr = s8.find(100);//find如果找到，指向该迭代器。找不到，则指向end迭代器
    if (ptr != s8.end()) {
        std::cout << *ptr << std::endl;
    }

    std::cout << s8.contains(50)/*c20*/ << std::endl;//返回一个bool值
    std::cout << s8.contains(1) << std::endl;

    std::cout << *s8.begin() << std::endl;//迭代器可以读
//    *s8.begin() = 100;//illegal 但是不能写
    //因为set迭代器指向的对象是const，维持数据结构

    //由于set中的元素是const类型，因此在extract出现之前（c17），想要修改set中的元素，只能先删除再插入
    //extract见cppreference
}