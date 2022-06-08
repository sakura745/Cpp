#include <iostream>

struct Str {
    int x;
};

void fun(int x1, int x2) {

}
int main() {
    int a = 3;
    ++a;//等价a += 1;
    int x = 3;
    int y;
    int z;
    y = x++;//返回运算之前的值
    z = ++x;//返回运算之后的值
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    std::cout << z << std::endl;

    ++++x;//legal，但可读性低
    //(x++)++;//illegal 返回值为右值，右值不能++
    //x++++;//illegal

    Str s;
    s.x;
    Str* ptr = &s;
    (*ptr).x;//繁琐
    //*ptr.x; error 优先级不对
    ptr->x;//等价于(*ptr).x

    std::cout << (true ? 3 : 5) << std::endl;
    int w = 1;
    int e = 2;
    false ? (++w) : (++e);
    std::cout << w << std::endl << e << std::endl;
    //false ? 1 : "Hello"; type is not same

    int score = 100;
    int res = (score > 0) ? 1 : (score == 0) ? 0 : -1;//右结合：先算score == 0,再算score > 0,可读性较低，不建议这么写
    std::cout << res << std::endl;

    std::cout << (2, 3, 4, 5) << std::endl;

    fun(2, 3);//不是逗号表达式

    sizeof(int);
    sizeof(x);
    sizeof x;//合法，没有括号，但不建议这么写
}