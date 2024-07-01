#pragma once
#include <iostream>

class Sing {
public:
    Sing() {
        std::cout << "Sing construct\n";
        val = 100;//不使用初始化列表，用此方式赋值。符合读取配置文件的方式
    }
    ~Sing() {
        std::cout << "Sing destroy\n";
    }
    
    int val;
};

extern Sing singletonInst;
//没有extern的Sing singletonInst表示为定义一个全局（该翻译单元）变量
//使用extern之后，变成声明了一个供其他翻译单元使用的全局变量
//如果extern Sing singletonInst = Sing{};给定一个初始化的值，则又变成定义
