#include <iostream>
#include <cmath>
int main() {
    3 < 5;
    5 < 3;
    int a[3];
    auto ptr1 = std::begin(a);
    auto ptr2 = std::end(a);
    ptr1 != ptr2;

    true && true;
    3 && true;
    int x = 4;
    3 && x;

    //a && b; a false, a && b false，不用考虑b
    int* ptr = nullptr;
    if (ptr && (*ptr == 3)) {

    }

    // a || b; a true, a||b true, 不考虑b
    // a || b && c -> a || (b && c)   建议加上括号

    int d = 4, e = 5, f = 6;
    std::cout << (f > e > d) << std::endl;//f > e > d ->  true > d -> 1 > 3 -> 0
    std::cout << ((f > e) && (e > d)) << std::endl;

    if (d == true) {//d == true -> d == 1

    }

    /* C++standard 20
     * auto res = (d <=> f);
     * if (res > 0) { }
     * else if (res < 0) {}
     * else if (res == 0) {}
     */
    std::cout << sqrt(-1) << std::endl;//nan is not a number.
}