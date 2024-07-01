#include "sing.h"
#include <memory>
int main(int argc, char* argv[]) {
    std::cout << "get value: " << Sing::Instance().val << '\n';
    //输出为
//    get value: Sing construct
//    100
//    Sing destroy

    //先输出get value，然后再构造
    //说明什么？说明对象的构造由第一品的在main函数之外构造变成了在main函数之内构造对象
    //这是Cpp标准规定，任何函数如果内部声明了静态对象，该静态对象会被首次访问时构造
    //由于是调用Instance函数构造的静态对象，多线程的角度来说，可能多个线程都是首次调用
    //但c11标准解决了

//    Sing singg;//illegal

    //但这么可以
    Sing* sing2 = new Sing(Sing::Instance());
    //Sing(Sing::Instance())相当于使用了拷贝构造函数，Sing::Instance()返回了一个Sing对象
    //类没有定义拷贝构造函数，因此编译器会生成一个public的拷贝构造
    //但
//    Sing(Sing::Instance());//illegal
    //是因为这是上一行代码是构造临时对象在栈上，销毁时会引用析构函数，所以会报错
    //所以说定义在堆上不报错是因为没有给出delete sing2;
//    auto ptr = std::make_shared<Sing>(Sing::Instance());//illegal
}
