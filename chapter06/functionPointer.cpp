#include <iostream>
#include <vector>
#include <algorithm>

int inc(int x) { //fun的函数类型: int(int)
    return x + 1;
}
int dec(int x) { //fun的函数类型: int(int)
    return x - 1;
}

//类比于数组
using K1 = int(int);
K1 fun;//函数别名-声明函数，不能为函数引入定义，但数组可以
//int(int) fun;//illegal
using K2 = int(int);
K2* fun2;//不是函数声明，构造了一个变量。该变量是一个指针，指针可以接受一个int类型的形参，返回一个int类型的数值的函数

//函数指针用于高阶函数
int Twice(K2* fun, int x) {
    int tmp = (*fun)(x);
    return tmp * 2;
}

void Demo(int a[3]) {}
void Demo2(K2 input) {}

void fun4(int) {}
void fun4(int, int) {}

auto fun5(bool input) {
    if (input)
        return inc;
    else
        return dec;
}

int main() {
    using K = int[3];
    K a;//数组别名
//    int[3] a;//illegal
    K a1 = {1, 2, 3};//数组聚合初始化
    K* b;//b首先是个指针(*b)，指针类型为K，指向了包含三个int类型的数组，等价于int(*b)[3]。数组的指针

    K2* fun = nullptr;
    K2* fun2 = &inc;
    std::cout << inc(100) << std::endl;
    std::cout << (*fun2)(100) << std::endl;
    std::cout << Twice(&inc, 100) << std::endl;
    std::cout << Twice(&dec, 100) << std::endl;
    std::cout << "----------" << std::endl;

    std::vector<int> c{1, 2, 3, 4, 5};
    std::transform(c.begin(), c.end(), c.begin(), &inc);//泛型算法函数
    for (int i = 0; i < 5; ++i) {
        std::cout << c[i] << " ";
    }
    std::cout << std::endl << "----------" << std::endl;

    auto fun3 = inc;//类型退化，fun3为函数指针类型，而非函数类型。类比于数组的类型退化
    //类型是 int(*)(int)

    int d[3];
    Demo(d);//Demo接收的不是数组d-int[3]，因为数组不能复制，接收的是指针int*，指向d[0]
    Demo2(inc);//Demo2接收的不是函数inc，函数也不能复制,接收的同样是指针，inc函数指针
    Demo2(&inc);//默认体现出接收的指针，因为有地址符号
    //将void Demo2(K2 input) 改为void Demo2(K2* input)也可以

//    auto z = fun4; //error fun4有两个类型，不能使用auto构造函数指针
    using K3 = void(int, int);//只能显式的给定类型
    K3* fun4;

    std::cout << (*fun5(true))(100) << std::endl;
    std::cout << (*fun5(false))(100) << std::endl;

}