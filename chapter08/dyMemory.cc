#include <iostream>
#include <new>//nothrow new

int* fun() {
    int res;
    return &res;
}
int* fun1() {
    int* res = new int(2);
    return res;
}

int* fun2() {//与fun()一样的危险
    char ch[sizeof(int)];
    int* y = new (ch) int(100);
    return y;
}

struct Str {};
struct alignas(256) Str1 {};//alignas(256)表示Str对应256个字节对齐
struct Str2 {
    ~Str2() {
        std::cout << "~Str2 is called" << std::endl;
    }
};
int main() {

//    int* y/*stack memory*/ = new int(2)/*heap分配了int大小的内存，把2保存到该内存上*/;//new函数返回一个int*，该表达
//    式为复合表达式。
//    std::cout << *y << std::endl;
//
//    //y指针（而不是y）所指向的内存（存在于heap中）一直存在
//    delete y;//不是释放y内存，而是释放 y指针 指向的内存
//
//    int* a = fun();//函数有危险，a指向了被销毁的res内存地址
//    int* b = fun1();//函数安全，b指向了堆的地址

//    fun1();//有问题，返回值没有内存接收。分配内存，但是没有回收 -- 内存泄漏。越使用内存越小，最后内存不足

    //初始化
//    int* a2 = new int{1};//也可以
//    int* a3 = new int;//缺省初始化

    //初始化对象数组
//    int* a3 = new int[5];//a3返回五个int的首地址，缺省初始化数组含有五个int
//    int* a4 = new int[5]{1, 2, 3, 4, 5};//c11之后初始化列表
//    delete a4;//行为不确定
//    delete[] a4;//释放数组


//    //如果内存分配失败，则不会抛出异常，如何区分内存是否分配成功, y 是否为nullptr
//    int* y = new (std::nothrow) int(2);//如果nothrow去掉，则为错误的代码。因为内存开辟了，会执行else 失败了，会
//    抛出异常，处理异常那段一直没用
//    if (y == nullptr) {
//        //.... 处理异常
//    } else {
//        std::cout << *y;
//        delete y;
//    }

//    char ch[sizeof(int)];//ch: char[4]
//
//    int* y = new (ch) int(100);
//    //ch 就是 placement new
//    //ch: char[4] --> char* --> void*. placement new 接收 void* 指针，该指针指向了一块内存。
//    // placement new在该内存上构造对象->int(100)
//    // 表示着将一个整数对象构造在字符数组 ch 的内存位置上
//    //想要placement new有意义，首先ch是(数组，也可以视为)指针类型，其次ch(char sizeof(int))足够大，
//    //[sizeof(int)]确保ch能装下int，如果是ch[3]，则系统未定义
//    //ch是stack的内存，ch是heap中也可以
//    std::cout << *y;

//    int* y = new auto(30);//c11, 基于30自动推导

    //正常编译，没有问题
//    //    Str* y = new Str;
//    //    std::cout << y << std::endl;//注意是y 地址，不是*y
//    Str1* y = new Str1;
//    std::cout << y << std::endl;//多次运行，最后两位一定是00
//    Str1 a;
//    std::cout << &a << std::endl;//也是00。说明对齐和内存是从heap还是stack分配无关，都会是对齐256。为了给cache，
//    //提升速度

    //placement delete对于内建类型来说，不需要delete关键字，自动销毁
    //placement delete对于类来说，通过手动调用析构函数来进行销毁
    char ch[sizeof(Str2)];
    Str2* ptr = new (ch) Str2;
    ptr->~Str2();

    //程序合法，为了简化程序书写
    int* ptr2 = nullptr;
    delete ptr2;//或 delete[] ptr2;
    //delete什么都不做，直接返回

    //代码非法
    int x;
    delete &x;

    //行为不确定
    int* x1 = new int[5];
    delete[] (x1 + 1);


}