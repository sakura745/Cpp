#pragma once
#include <atomic>
//#include "sing1.h"//不用写，为什么在Init()和~Init()使用到T()和~T()，还不用写出T所在的头文件
//因为SingTemp是模板，实例化之前是声明，不需要知道具体实现细节。退一步讲，如果都需要补上T所在的头文件
//那这样的设计方式也有问题，还有实时的修改模板所在的头文件
///单例逻辑
template <typename T>
class SingTemp {
public:
    struct Init {
        Init() {//改为类内定义
            auto&/*不能去掉&，因为atomic对象没有copy ctor*/ count = RefCount();
            auto ori = count.fetch_add(1);
            if (ori == 0) {
                T* ptr = SingTemp::Ptr();
                new (ptr) T();//属于基类调用派生类，但是没有构造virtual。是因为使用了CRTP
            }            
        }

        ~Init() {
            auto& count = RefCount();
            auto ori = count.fetch_sub(1);
            if (ori == 1) {
                T* ptr = SingTemp::Ptr();
                ptr->~T();//属于基类调用派生类，但是没有构造virtual。是因为使用了CRTP
            }
        }

        static auto& RefCount() {
            static std::atomic<unsigned> count{0};
            return count;
        }
        
        Init(const Init&) = delete;
        Init& operator=(const Init&) = delete;
    };
    
protected:
    SingTemp() = default;
    ~SingTemp() = default;
    SingTemp(const SingTemp&) = delete;
    SingTemp& operator=(const SingTemp&) = delete;
    
public:
    static T* Ptr() {
        alignas(T) static char singBuf[sizeof(T)];//放在静态函数里，首次访问静态函数，才首次构造变量
        //不会导致static initialization order fiasco
        return reinterpret_cast<T*>(singBuf);
    }
};
