#include "sing.h"

int main(int argc, char** argv) {
    std::cout << "get value: " << Sing::Instance().val << '\n';

//    Sing* s = new Sing(Sing::Instance());//illegal
//    Sing* s2 = new Sing(std::move(Sing::Instance()));//illegal

/*
    size_t res = 0;
    for (unsigned i = 0; i < 999999999; ++i) {
        res += Sing::Instance().val + i;// + i 是为了防止系统引入优化
    }
    return res;
*/
    //循环非常耗时，就是因为在构造对象的时候，不断加锁 解锁
}
