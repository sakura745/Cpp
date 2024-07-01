#pragma once
#include <atomic>
#include <iostream>

class Sing {
public:
    struct Init {
        Init();
        Init(const Init&) = delete;
        Init& operator=(const Init&) = delete;
        ~Init();
        
        static std::atomic<unsigned>& RefCount() {//与第三品的构造的实例类似
        //好处是可以精准控制singletonCount的构造时机，在第一次调用RefCount函数时构造
        //atomic:保证加减、读写等操作是原子的（也就是不受其他影响）
            static std::atomic<unsigned> singletonCount{0};
            return singletonCount;
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

extern Sing* singletonInst;