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

    int* ptr;
    void* v = ptr;

    //error int* ptr2 = v;
    int* ptr2 = static_cast<int*>(v);

    int* pt;
    double* pt2;
    fun(pt, 1);
    fun(pt2, 2);

    const int* p;
    //error: static_cast<int*>(p);
    const_cast<int*>(p);

    int a = 3;
    const int& ref = a;
    int& ref2 = const_cast<int&>(ref);
    ref2 = 4;
    std::cout << a << std::endl;

    //int 改为 const int
    const int b = 3;
    const int& refb = b;
    int& refb2 = const_cast<int&>(refb);
    refb2 = 4;
    std::cout << b << std::endl;//output 3

    int c = 3;
    //error double d = reinterpret_cast<double>(c);
    int* pp = &c;
    double* pp2 = reinterpret_cast<double*>(pp);
    std::cout << *pp2 << std::endl;

    (double)3; 
}