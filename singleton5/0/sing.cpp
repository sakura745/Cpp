#include "sing.h"
#include <memory>
#include <iostream>

std::unique_ptr<Sing> singletonInst;//当unique_ptr释放时，需要调用Sing的析构函数，因此需要将析构函数设置为public
//或者可以在sing.h中将std::unique_ptr<Sing> singletonInst;设置为Sing的友元

Sing::Init::Init() {//Init的构造函数，用来构造singletonInst的对象
    if (!singletonInst) {//保证singletonInst不为空
        singletonInst.reset(new Sing());
    }
}

