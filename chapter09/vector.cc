#include <iostream>
#include <vector>//引入vector
#include <string>

void print(const auto& a) {
    for (auto i : a) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}
int main() {
    std::vector<int> myVector;
    std::cout << "Initial capacity: " << myVector.capacity() << std::endl;

    for (int i = 0; i < 10; ++i) {
        myVector.push_back(i);
        std::cout << "Size: " << myVector.size() << ", Capacity: " << myVector.capacity() << std::endl;
    }
    std::cout << "-------------------" << std::endl;
    std::vector<int> a{1};
    std::vector<int> b{1, -1, 2};
    std::cout << a.size() << ' ' << a.max_size() << std::endl;
    std::cout << (a < b) << std::endl;//无需长度相等，比较是字典序
    //vector的swap也很快，只交换size_t size, size_t cap和T* buffer指针即可

    std::vector<int> c;
    for (int i = 0; i < 1024; ++i) {//没有提前分配空间，自动分配空间会耗时
        c.push_back(i);
    }

    std::vector<int> d;
    d.reserve(1024);//预先分配空间
    for (int i = 0; i < 1024; ++i) {
        d.push_back(i);//d.emplace_back也可以，对于int来说没太大区别
    }

    std::vector<std::string> a1;
    //在结尾出插入元素
    a1.push_back("Hello");//"Hello"构造成string，再把string 加到vector中
    a1.emplace_back("Hello");//直接使用"Hello"，在vector中构造string。相比与push_back少了一次移动，性能更高

    std::vector<int> c1(3, 100);
    print(c1);
    auto it = c1.begin();
    c1.insert(it, 200);
    print(c1);

    c1.emplace(it, 200);//区别与push_back 和 emplace_back区别一样。同时，it迭代器会失效
    //失效的原因是修改了元素的个数，原来的vector可能会重新分配内存，之前迭代器所指的位置会改变
    //修改方法使用之后将返回新的迭代器，修改如下
    //it = c1.insert(it, 200);
    //it = c1.emplace(it, 200);
    //insert和emplace的函数返回值就是为了这个作用

}
