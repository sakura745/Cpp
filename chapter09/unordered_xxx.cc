#include <iostream>
#include <unordered_set>//引入unordered_set
#include <set>

struct Str {
    int x;
};
size_t myHash(const Str& val) {
    return val.x;
}
bool myEqual(const Str& lhs, const Str& rhs) {
    return lhs.x == rhs.x;
}
class myHashFunction {
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
    //支持判等是因为根据元素哈希值的异同，来选择将其元素放入对应的bucket list中
    std::unordered_set<int> s3{3, 1, 5, 4, 1, 8};
    std::cout << (s != s3) << std::endl;
    //std::cout << (s < s3) << std::endl;//illegal

    //自定义hash与判等函数
    std::unordered_set<Str, decltype(&myHash), decltype(&myEqual)> ss(1, myHash, myEqual);
    ss.emplace(3);//// 应该是合法的，gcc从9升到10解决了
    ss.insert(Str{3});

    std::unordered_set<Str, myHashFunction> sss;
    myHashFunction mf;
    mf(Str{3});//返回hash值

    myHash(Str{3});//返回hash值
    //decltype(&myHash) 对应的类型是函数指针： size_t (*)(const Str& val)
    //不能用缺省值
    using myPtr = size_t (*)(const Str& val);
    myPtr ptr = myPtr();//结构类似于 int* ptr = int();
    //(*ptr)(Str{3});//illegal 不能对空指针解引用
    //所以在用decltype(&myHash)构造hash函数时，不能使用缺省，需要传入myHash函数指针

}