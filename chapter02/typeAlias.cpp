#include <iostream>
#include <type_traits>
#include <limits>

typedef int MyInt;//c98
using MyInt = int;//c11

//对于同一个类型char[4]的别名，using可读性更高
typedef char MyCharArr[4];
using MyCharrArr2 = char[4];

using IntPtr = int*;

int main() {
    int x = 3;
    int y = 5;
    const int* ptr = &x;
    ptr = &y;//legal
//    *ptr = 4;//illegal

    const IntPtr ptr2 = &x;
    //ptr2 = &y;//illegal ptr2类比与ptr,将会出错。
    *ptr2 = 3;//legal 表示使用别名后，const修饰的是顶层，等价于 int* const ptr2 = &x;
}