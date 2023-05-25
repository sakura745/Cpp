#include <iostream>
#include <unordered_set>//引入unordered_set
#include <set>

struct Str {
    int x;
};
size_t MyHash(const Str& val) {
    return val.x;
}
bool MyEqual(const Str& val1, const Str& val2) {
    return val1.x == val2.x;
}
class MyHashFunction {
public:
    size_t operator()(const Str& t) const{//返回hash值
        return t.x;
    }
};
int main() {
    std::unordered_set<int> s{3, 1, 5, 4, 1};//hash表提供了int转为hash值的操作，和int支持判等
    for (auto& i : s){
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    std::set<int> s1{3, 1, 4, 5};
    std::set<int> s2{3, 1, 4};
    s1 < s2;//set支持比较操作

    //unordered_set/map 不支持比较操作，支持判等操作，但速度比较慢
    std::unordered_set<int> s3{3, 1, 5, 4, 1, 8};
    std::cout << (s != s3) << std::endl;
    //std::cout << (s < s3) << std::endl;//illegal

    //自定义hash与判等函数
    std::unordered_set<Str, decltype(&MyHash), decltype(&MyEqual)> ss(1, MyHash, MyEqual);
    ss.emplace(3);
    ss.insert(Str{3});

    std::unordered_set<Str, MyHashFunction> sss;
    MyHashFunction mf;
    mf(Str{3});//返回hash值

    MyHash(Str{3});//返回hash值
    //decltype(&MyHash) 对应的类型是函数指针： size_t (*)(const Str& val)
    //不能用缺省值
    using MyPtr = size_t (*)(const Str& val);
    MyPtr ptr = MyPtr();
    //(*ptr)(Str{3});//illegal 不能对空指针解引用
    //所以在用decltype(&MyHash)构造hash函数时，不能使用缺省，需要传入MyHash函数指针

}