#pragma once
#include "sing_temp.h"
#include "sing1.h"

#include <iostream>//std::cout也是单例，对于std::cout来说，就算下面的代码Sing2()和~Sing2()的定义放在对应的源文件*.cpp中
//也要将单例std::cout的头文件<iostream>放到Sing2的头文件中。也就是现在的做法
//要保证std::cout先于Sing2初始化

class Sing2 : public SingTemp<Sing2> {
    friend SingTemp<Sing2>;
    
private:
    Sing2()
        : SingTemp<Sing2>() {
        std::cout << "Sing2 construct\n";
        val = singleton1.val + 1;
    }
    
    ~Sing2() {
        std::cout << "Sing2 destroy\n";
    }
    
public:
    int val;
};

static Sing2::Init sing2Init;
static Sing2& singleton2 = *Sing2::Ptr();//单例Sing2的唯一接口