#include <iostream>
#include <type_traits>
#include <limits>

typedef int MyInt;//98 standard
using MyInt = int;//11 standard


using IntPtr = int*;

int main() {
    int x = 3;
    int y = 5;
    const int* ptr = &x;
    ptr = &y;

    const IntPtr ptr2 = &x;
    //ptr2 = &y; 类比与ptr,将会出错。
    *ptr2 = 3;//是正确的。表示使用别名后，const修饰的整个整体，等价于 int* const ptr2 = &x;

}