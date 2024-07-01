#pragma once
#include <iostream>
#include <atomic>

class Sing {
public:
    struct Init {
        Init();
        Init(const Init&) = delete;
        Init& operator=(const Init&) = delete;
        ~Init();
        static auto& RefCount() {
            static std::atomic<unsigned> count{0};
            return count;
        }
    };
    
private:
    Sing() {
        std::cout << "Sing construct\n";
        val = 100;
    }

    ~Sing() {
        std::cout << "Sing destroy\n";
    }

    Sing(const Sing&) = delete;
    Sing& operator=(const Sing&) = delete;

public:
    int val;
};
//可以将Sing分为两部分
//第一部分是确保单例的**单**，只能构造一个对象的唯一性：第一个public和第一个private的部分。
//该部分可以单独封装，便于其他情况使用单例的性质
//第二部分是单例的成员，第二个public部分

//对于sing.h和sing.cpp希望放到一个文件当中

//这两个static是防止重定义
static Sing::Init init;
extern char singBuf[sizeof(Sing)];
static Sing& singletonInst = *(reinterpret_cast<Sing*>(singBuf));//将SingBuf从char*类型转化为Sing*