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
}//C风格处理下的C++重载

int main() {
    std::cout << 3 + 0.5 << std::endl;
//    "abcde" + 0.5;//illegal

    static_cast<double>(3) + 0.5;
//    static_cast<double>("abcde") + 0.5;//illegal

    std::cout << (3 / 4) << std::endl;
    std::cout << (3 / 4.0) << std::endl;
    int x = 3;
    int y = 4;
    std::cout << (x / y) << std::endl;
    std::cout << (x / static_cast<double>(y)) << std::endl;
    std::cout << (static_cast<double>(x) / y) << std::endl;
    std::cout << (static_cast<double>(x / y)) << std::endl;//可能会丢失精度
    std::cout << "----------------" << std::endl;

    int* ptr = nullptr;
    void* v = ptr;
//    int* ptr2 = v;//illegal
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
    //试图修改b的值
    const int& refb = b;
    int& refb2 = const_cast<int&>(refb);
    refb2 = 4;

    std::cout << b << std::endl;//没有试图修改b的值，编译器直接输出3，因为是编译器常量。
    //但是现在通过显示转换，试图修改b的值，因此行为不确定。
	//因此使用 const_cast 要注意去掉或增加const限定符时，要确定是否绑定在常量上


    int c = 3;
//    double d = reinterpret_cast<double>(c);//error，多用于指针
    int* pp = &c;
    double* pp2 = reinterpret_cast<double*>(pp);
    std::cout << *pp2 << std::endl;//输出的值不为c，是int强行转换为double类型的值且字节数不同，int的四个字节和double的
    //八个字节之间的转换，会将int相比于double少的四个字节补上
    //如何证明字节数问题，将double换成int，多次执行，pp2的值不确定，pp3的值不变
    float* pp3 = reinterpret_cast<float*>(pp);
    std::cout << *pp3 << std::endl;

    (double)3;//c风格类型的转换
    //c++风格的显式类型转换写起来很麻烦，这是c++标准有意为之，不建议使用显示转换
}