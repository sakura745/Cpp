#include <iostream>

struct Str {};
void f1() {
    //栈展开：异常产生后，对局部对象进行销毁，先构建后销毁的顺序。
    int x;
    Str obj;

    std::cout << "Blabla1.\n";
    throw/*抛出异常*/ 1123;
    std::cout << "Blabla2.\n";//抛出异常后的代码不会被执行
}
void f2() {
    //从f1的异常产生f1栈展开后，对f2进行栈展开
    //对局部对象进行销毁，先构建后销毁的顺序。
    int x2;
    Str obj2;
    try {
        f1();
    } catch (int/*异常对象*/ e) {
        std::cout << "Exception is caught in f2(): " << e << std::endl;
    }
    std::cout << "Other logic in f2().\n";
}
void f3() {
    f2();
}


void f11() {
    throw 1;
}
void f22() {
    int x2;
    Str obj2;
    f11();
}
void f33() {
    try {
        f22();
    } catch (double) {
        std::cout << "Exception double is caught in f33().\n";
    } catch (int) {
        std::cout << "Exception int is caught in f33().\n";
    }

    std::cout << "Other logic in f33().\n";
}

struct Base{};
struct Derive : Base{};

void f111() {
    throw Derive{};
}
void f222() {
    try {
        f111();
    } catch(Base& e) {//输出Base exception is caught in f222.
        std::cout << "Base exception is caught in f222.\n";
    } catch(Derive& e) {
        std::cout << "Derive exception is caught in f222.\n";
    }

//如果想输出Derive exception is caught in f222.需要将Derive& 放到上面，如下：
//    catch(Derive& e) {
//        std::cout << "Derive exception is caught in f222.\n";
//    } catch(Base& e) {
//        std::cout << "Base exception is caught in f222.\n";
//    }

    //throw出的类型，不会考虑类型转化被catch捕获：只有throw int ，catch const int
    //                                                throw int[], catch int*
    //                                                throw Derive, catch Base
    //只有这三种可以匹配

    catch(...)/*可以匹配任意异常*/ {
        std::cout << "Exception is caught in f222().\n";
    }
}

void f1111() {
    throw Str{};
}
void f2222() {
    try {
        f1111();
    } catch(.../*捕获任意类型的异常*/) {//通常置于多个catch语句块的最后
        std::cout << "Exception is caught in f2222.\n";
        throw;//表示抛出接收到的异常对象。只能在catch中使用
    }
}
void f3333() {
    try {
        f2222();
    } catch (Str) {
        std::cout << "Str exception is caught in f3333.\n";
    }
}

//程序会崩溃：调用terminate。因为throw123; 抛出异常时，栈展开会产生对对象Str2的销毁，因此又抛出throw 100异常。
struct Str2 {
    ~Str2() {
        throw 100;
    }
};
void f11111() {
    Str2 obj;
    throw 123;
}
void f22222() {
    try {
        f11111();
    } catch(...) {
        std::cout << "Exception is caught in f22222.\n";
    }
}

int main() {
    try {
        f3();
    } catch (int) {
        std::cout << "Exception is occurred f3.\n";
    }
    //f1抛出异常，f1进行栈展开。执行到f2中的f1，发现位于try中，try会根catch子句，由于抛出的异常为1，int型。因此被catch(int)
    //捕获，执行Exception is caught in f2().已经抓住了异常，栈展开停止，后续没有异常会继续执行后续代码，输出Other logic in f2()，
    //之后f2函数执行完毕，返回到f3。再返回到main，执行主函数的try，没有异常，因此不会执行主函数中的catch。

    std::cout << "---------------------------------" << std::endl;
    try {
        f33();
    } catch (int) {
        std::cout << "Exception is occurred f33.\n";
    }
    std::cout << "---------------------------------" << std::endl;

    f222();
    std::cout << "---------------------------------" << std::endl;

    f3333();
    std::cout << "---------------------------------" << std::endl;

    f22222();
}