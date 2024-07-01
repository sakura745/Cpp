#pragma once
#include <iostream>
#include <memory>

class Sing {
public:
    struct Init {
        Init();
        Init(const Init&) = delete;
        Init& operator=(const Init&) = delete;
    };
    
public://不用担心像第一品出现的可以构造其他单例，因为缺省构造、拷贝构造（赋值）已经设置为private
    ~Sing() {
        std::cout << "Sing destroy\n";
    }

//    friend std::unique_ptr<Sing>;
    //public ~Sing()和 friend std::unique_ptr<Sing> 选其一


private:
    Sing() {
        std::cout << "Sing construct\n";
        val = 100;
    }

    Sing(const Sing&) = delete;
    Sing& operator=(const Sing&) = delete;
public:
    int val;
};

extern std::unique_ptr<Sing> singletonInst;