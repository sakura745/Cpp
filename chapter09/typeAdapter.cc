#include <iostream>
#include <string>
#include <string_view>//引入string_view c17
#include <span>//引入span c20
#include <vector>

void fun(const char* str) {

}

void fun1(const std::string& str) {

}
void fun2(std::string_view str) {//string_view推荐作为函数形参，不推荐作为函数返回类型
    if (!str.empty()) {
        std::cout << str[0] << std::endl;
        //str[1] = 'v';//illegal 不能写操作
    }
}

std::string_view fun3(){//作为函数返回类型有风险
    std::string s = "1234";
    return s;
}
//但可以写成
std::string_view fun4(std::string_view input) {
    return input.substr(0, 3);//指针指向同一个input
}

void fun5(std::span<int> input) {//也是两个迭代器，与string_view类似，支持非字符串类型
    input[0] = 3;//支持可写的
    for (auto p : input) {
        std::cout << p << ' ';
    }
    std::cout << std::endl;
}
int main() {
    std::string s = "123456";
//    fun(s);//illegal string不能转化为char*
    fun(s.c_str());
    char* ss = "12345";
    fun1(ss);//char* 可以转化为string，但是效率很低

    //c风格字符串和c++风格字符串相互转化耗时等缺点
    //c17引入了basic_string_view

    fun2("123445");//c风格字符串
    fun2(std::string("123445"));//c++风格字符串
    //这两个风格字符都可以转化为string_view类型
    //且string_view也具有string类型相同的成员函数等
    //注意fun2的形参不是引用，而是单纯的string_view类型，因为该类型构造很容易。
    std::cout << sizeof(std::string_view) << std::endl;//16个字节只包含了字符串开头和结尾的两个迭代器
    //string_view不包含原有字符串的所有权，只是在原有字符串的基础上开了一个窗口，让fun2看到字符串


    //甚至可以传入迭代器
    fun2(std::string_view(s.begin(), s.begin() + 3));//// gcc从9升到10解决了

    auto res = fun4(s);
    std::cout << res << std::endl;
    auto res2 = fun4(std::string("98798798"));//又有风险，因为调用是临时变量，该语句结束后，临时对象会被销毁
    std::cout << res2 << std::endl;

    //span也是两个迭代器，与string_view类似
    std::vector<int> s4{1, 2, 4};
    int s5[6] = {1, 3, 4, 5, 6, 7};
    fun5(s4);
    fun5(s5);

}