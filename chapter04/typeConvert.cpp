#include <iostream>
void fun(void* par, int t) {
    if (t == 1) {
        int* ptr = static_cast<int*>(par);
        // ...
    }
    else if (t == 2) {
        double* ptr = static_cast<double*>(par);
        // ...
    }
}//C 处理形式 C++重载



int main() {
    std::cout << 3 + 0.5 << std::endl;
    //error: "abcde" + 0.5;

    static_cast<double>(3) + 0.5;
    //error: static_cast<double>("abcde") + 0.5;

    std::cout << (3 / 4) << std::endl;
    std::cout << (3 / 4.0) << std::endl;
    int x = 3;
    int y = 4;
    std::cout << (x / y) << std::endl;
    std::cout << (x / static_cast<double>(y)) << std::endl;
    std::cout << (static_cast<double>(x) / y) << std::endl;
    std::cout << (static_cast<double>(x / y)) << std::endl;//error

    int* ptr = nullptr;
    void* v = ptr;

//    int* ptr2 = v;//error
    int* ptr2 = static_cast<int*>(v);

    int* pt = nullptr;
    double* pt2 = nullptr;
    fun(pt, 1);
    fun(pt2, 2);

    const int* p = nullptr;
//    static_cast<int*>(p);//error
    const_cast<int*>(p);

    int a = 3;
    const int& ref = a;
    int& ref2 = const_cast<int&>(ref);
    ref2 = 4;
    std::cout << a << std::endl;//ref ref2都绑定到a上

    //int 改为 const int，可以编译，但行为有不确定性
    const int b = 3;
    const int& refb = b;
    int& refb2 = const_cast<int&>(refb);
    refb2 = 4;
    std::cout << b << std::endl;//output 3

    int c = 3;
//    double d = reinterpret_cast<double>(c);//error
    int* pp = &c;
    double* pp2 = reinterpret_cast<double*>(pp);
    std::cout << *pp2 << std::endl;//输出的值不为c，是int强行转换为double类型的值。字节数不同，

    (double)3;
}