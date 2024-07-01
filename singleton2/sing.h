#pragma once
#include <iostream>

class Sing {
public:
    static const Sing& Instance() {//使用静态成员变量：首先，要构造对象才能调用，但是如果可以直接构造对象
        //那又会出现第一品那样的不是唯一的对象。因此使用静态成员函数，通过调用静态成员函数来构造对象

        static Sing inst;//为static，也就是单例强调的存在的唯一对象
        return inst;
    }
    //将静态成员函数Instance作为全局访问点
private:
    Sing() {
        std::cout << "Sing construct\n";
        val = 100;
    }
    ~Sing() {
        std::cout << "Sing destroy\n";
    }
    
public:
    int val;
};

//对比于第一品的在类下声明对象。静态对象直接定义，因此需要再声明