#pragma once
#include <iostream>

class Sing {
public:
    static const Sing& Instance() {
        static Sing inst;//在c11之后保证的多线程安全，是如何保证的。
        //编译时：加锁，判断是否构造完成，没有：继续构造，构造完成，解锁返回
        //                                有  ：解锁返回
        //则会因为多线程的安全，引入额外成本
        //需要的是构造时多线程的安全，但是调用的时候就没必要了
        return inst;
    }
private:
    Sing() {
        std::cout << "Sing construct\n";
        val = 100;
    }

    ~Sing() {
        std::cout << "Sing destroy\n";
    }

    //放在public也行，反正都是delete
    Sing(const Sing&) = delete;
    Sing& operator=(const Sing&) = delete;
    //没有构造移动构造或者移动赋值时，调用移动操作，系统会默认调用对应的拷贝操作，系统不会生成移动构造或移动赋值

public:
    int val;
};
