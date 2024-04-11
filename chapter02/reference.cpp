#include <iostream>
int& fun() {
    int x;
    return x;
}
int main() {
    int x = 3, y = 4;
    int &ref = x;//reference
    ref = y;//不表示引用的重新绑定，表示为把y赋值给ref/x
    std::cout << ref << '\n';
    ref = ref + 1;
    std::cout << x << '\n';

    int& ref2 = fun();//x的生命周期为在fun()内，指向了一个被销毁的对象x

    int* ptr = &x;
    int*& ref_p = ptr;//指针的引用

}

