#include <iostream>
#include <cmath>
#include <compare>

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

    // a || b; a true, a || b true, 不考虑b
    // a || b && c -> a || (b && c)   建议加上括号

    int d = 4, e = 5, f = 6;
    std::cout << (f > e > d) << std::endl;//(f > e > d) ->  (true > d) -> (1 > 3) -> 0
    std::cout << ((f > e) && (e > d)) << std::endl;

    if (d == true) {//(d == true) -> (d == 1)，只会将bool类型转换为int型，不会反过来转换。
    }

     //C20
     auto res = (d <=> f);//res -> strong_ordering
     if (res == std::strong_ordering::greater/* 等价于res > 0 */ ) {}
     else if (res == std::strong_ordering::less/*res < 0*/) {}
     else if (res == std::strong_ordering::equal/*res == 0*/) {}
    //strong_ordering : 有四种状态 greater less equivalent equal      ，其中equal相等 equivalent等价 程度不一样
    //比如比较面积 长3高5 和 长5高3 的面积都是15，但是却不是equal的，只能说是equivalent。
    //weak_ordering : 有三种状态 greater less equivalent            ，其中equivalent等价

    auto res1 = (3.0 <=> 4.0);//res1 -> partial_ordering
    //partial_ordering : 有四种状态 greater less equivalent unordered  ，其中unordered不可比较的

    std::cout << sqrt(-1) << std::endl;//Not a Number(NaN).
    //nan不能比较，因此引入了partial_ordering
    auto res2 = (sqrt(-1) <=> 3.0);
    std::cout << (res2 > 0) << std::endl;
    std::cout << (res2 < 0) << std::endl;
    std::cout << (res2 == 0) << std::endl;
    //上三个输出全是0
    std::cout << (res2 == std::partial_ordering::unordered) << std::endl;//输出1

}