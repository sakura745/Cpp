#include <iostream>

void fun() {
//    goto label2;//不能跨函数跳转
}
int main() {
    int x;
    x = 3;//保留的副作用为：把3赋予给x

    {//复合语句: 域
        int x = 4;
        x += 1;
        std::cout << x << std::endl;
    }

    //顺序语句
    int y = 0;
    ++y;
    int z = 3;
    --z;

    /* 无逻辑区别，编译器可优化
    int y = 0;
    int z = 3;
    ++y;
    --z;
    */

    int a = 3;
    if (a) goto label;//非顺序语句
    a = a + 1;
label:
    std::cout << "Goto label\n";


    fun();
label2:
    return 1;


}
