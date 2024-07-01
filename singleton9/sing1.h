#pragma once
#include "sing_temp.h"
#include <iostream>

///功能逻辑
class Sing1 : public SingTemp<Sing1> {//两个Sing1，有递归的嫌疑。但是没有，被称之为奇特的递归模版式CRTP
    friend SingTemp<Sing1>;//声明友元，是为了SingTemp中的placement new/delete的功能。SingTemp<Sing1>调用Sing1的私有成员
    //这也是之前提到过的模板类型友元的声明
    
private:
    Sing1()
        : SingTemp<Sing1>() {
        std::cout << "Sing1 construct\n";
        val = 100;
    }
    
    ~Sing1() {
        std::cout << "Sing1 destroy\n";
    }
    
public:
    int val;
};

static Sing1::Init sing1Init;
static Sing1& singleton1 = *Sing1::Ptr();//单例Sing1的唯一接口