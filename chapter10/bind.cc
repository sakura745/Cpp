#include <iostream>
#include <vector>
#include <functional>//引入bind bind1st bind2nd
#include <memory>

bool myPredict(int val) {
    return val > 3;
}
bool myPredict2(int val1, int val2) {
    return val1 > val2;
}

bool myAnd(bool val1, bool val2) {
    return val1 && val2;
}

void myProc(int* ptr) {}
auto fun() {
    int x;
    return std::bind(myProc, &x);
}

void myProc1(std::shared_ptr<int> ptr) {}
auto fun1() {
    std::shared_ptr<int> x(new int());
    return std::bind(myProc1, x);
}

void Proc(int& x) {
    ++x;
}
int main() {
    std::vector<int> x{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> y1;
    std::vector<int> y2;
    std::vector<int> y3;
    std::vector<int> y4;
    std::copy_if(x.begin(), x.end(), std::back_inserter(y1), myPredict/*函数指针*/);

    //bind_1st bind_2nd是c11之前给出的，现已舍弃
    std::copy_if(x.begin(), x.end(), std::back_inserter(y2),
                 std::bind2nd(std::greater<int>(), 3)/*bind2nd*/);
                 ///上式表示 把 greater 和 3 绑定（bind）到一起
                 //bind2nd 是固定greater第二个参数为3
    std::copy_if(x.begin(), x.end(), std::back_inserter(y3),
                 std::bind1st(std::greater<int>(), 3)/*bind1st*/);
                  //bind1st 固定greater第一个参数为3
    for (auto i: y1) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (auto i: y2) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    for (auto i: y3) {
        std::cout << i << ' ';
    }
    std::cout << std::endl << "-------------------------" << std::endl;

//    std::copy_if(x.begin(), x.end(), std::back_inserter(y3), std::bind1st(myPredict2, 3));//illegal功能有限

    //引入bind
    using namespace std::placeholders;//用于在函数模板中指定占位符参数：bind中 _1 需要引入
    std::copy_if(x.begin(), x.end(), std::back_inserter(y4), std::bind(myPredict2, _1, 3));
    //_1中的1表示的是copy_if中d_first的第1个参数（当然，d_first只有一个参数），而不是表示bind中的第1个

    for (auto i: y4) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    auto a = std::bind(myPredict2, _1, 3);
    a(50);
    //_1 表示 a 中的第一个参数。a(50)第一个参数是50。而不是表示myPredict2 的第一个参数是 50
    std::cout << a(50) << std::endl;//50 > 3 。输出 true
    //bind绑定的函数复制给的函数至少有多少个参数，取决于_n的n的个数。如a至少有一个参数

    auto b = std::bind(myPredict2, 3, _1);
    b(50);
    //就是说std::bind(myPredict2, par1, par2)中par1、par2分别对应myPredict2的两个参数
    //_1 对应b(par1)中的par1
    std::cout << b(50) << std::endl;//3 > 50 。输出 false

    auto c = std::bind(myPredict2, _2, 3);
    std::cout << c("asdf", 50) << std::endl;//50 > 3 。输出 true
    //_2 对应c(par1, par2)中的par2

    auto d = std::bind(myPredict2, _2, _1);
    std::cout << d(4, 50) << std::endl;//50 > 4 。输出 true

    auto xx1 = std::bind(myPredict2, _1, 3);
    auto xx2 = std::bind(myPredict2, 10, _1);
    auto xx3 = std::bind(myAnd, xx1, xx2);
    std::cout << xx3(5) << std::endl;// 5 > 3 && 10 > 5，就是5是否在(3, 10)区间内。输出true
    std::cout << xx3(51) << std::endl;// 51 > 3 && 10 > 51，就是51是否在(3, 10)区间内。输出false
    std::cout << "-------------------------" << std::endl;
    //传入参数会被复制，如xx1中的3是被复制到xx1对象

    auto ptr = fun();
    //fun()返回了一个可调用对象，该对象是由bind绑定构造的。该对象内部包含了一个int*，
    //该指针指向了一个局部对象。局部对象的指针会被复制到bind构造的对象当中。局部对象的指针已经被销毁了
    ptr();//则ptr行为未定义。

    //为了解决上述问题，考虑使用智能指针。
    auto ptr1 = fun1();
    ptr1();

    int xxx = 0;
    Proc(xxx);
    std::cout << xxx << std::endl;
    auto yyy = std::bind(Proc, xxx);
    yyy();
    //xxx被拷贝到bind绑定构造的对象中，yyy()是对拷贝的对象进行Proc操作，而本身的xxx没有修改
    std::cout << xxx << std::endl;//输出是1，而不是2
    auto zzz = std::bind(Proc, std::ref(xxx)/*避免被复制*/);//传引用给复制到对象
    zzz();
    std::cout << xxx << std::endl;//输出是2

    auto q = std::bind_front(myPredict2, 3);//把 3 绑定到了myPredict2的第一个参数
    std::cout << q(2) << std::endl;//3 > 2 。输出 true
}

