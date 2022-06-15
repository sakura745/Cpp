#include <iostream>
#include <initializer_list>

void fun(int x, int y) {
    std::cout << y << std::endl;
}

struct Str {
    Str() = default;
    Str(const Str&) {
        std::cout << "Copy constructor is called.\n";
    }
};

void fun(Str par) {

}

void fun1(int par) {
    ++par;
}
void fun1(int* par) {
    ++(*par);
}
void fun2(int& par) {
    ++par;
}
void fun3(int* par){

}
void fun4(int par[]){//等价于(int par[3])但不建议这么写，容易出错。

}
void fun5(int (*par)[4]) {//等价于(int par[3][4])但不建议这么写，容易出错。

}
void fun6(int (&par)[3]) {

}

void fun7(std::initializer_list<int> par){

}

std::initializer_list<int> fun8() {
    return {1, 2, 3, 4};
}

void fun9(int x = 0) {//缺省实参

}
void funa(int x = 0, int y = 0){//legal
    std::cout << x + y << std::endl;
}
//void funa(int x = 0, int y ){//illegal
//  std::cout << x + y << std::endl;
//}

//void funb(int x, int y = 2, int z = 3);//funb的声明，y、z缺省实参的定义

//void funb(int x, int y , int z = 3);
//void funb(int x, int y = 2, int z );//是合法的，但注意要先定义最右边的z，再定义y

void funb(int x, int y, int z) {//y、z不能再定义一次
//void funb(int x, int y = 2, int z = 3) {illegal
//funb declare中y、z定义去掉，可以在funb定义上添加yz定义（实参定义优先级声明高于定义 ）
    std::cout << x + y + z << std::endl;
}

int x = 3;
void func(int y = x) {//缺省实参为变量x，而非字面值3。但不建议这么写，可读性差。
    std::cout << y << '\n';
}

int main() {
    fun(1, int{});//int{}为临时对象，c++17会省略
    Str val;
    fun(val);
    fun(Str());//没有输出copy constructor 被省略

    int arg = 3;
    fun1(arg);//传值
    std::cout << arg << std::endl;
    /*等价于
     int par = arg;
     ++par;
     std::cout << arg << std::endl;
     */

    int arg2 = 3;
    fun1(&arg2);//传址
    std::cout << arg2 << std::endl;
    /*等价于
     int *par = &arg2;
     ++(*par);
     std::cout << arg2 << std::endl;
     */

    int arg3 = 3;
    fun2(arg3);//传引用
    std::cout << arg3 << std::endl;
    /*等价于
     int& par = arg3;
     ++arg3;
     std::cout << arg3 << std::endl;
     */

    int a[3];
    auto b = a;//拷贝初始化类型引起的退化 a->int [3]  b->int*
    fun3(a);//可以用a来拷贝初始化par
    /*等价于
    int* par = a;
    */
    fun4(a);//fun4中int par[] 等价于int* par
    fun6(a);//避免类型退化

    int c[3][4] = {};
    fun5(c);//实参可以拷贝初始化到对应的形参

    fun7({1, 2, 3, 4});
    auto e = fun8();//该函数虽然合法，但很危险。初始化列表的原理是包含首、尾两个指针。在函数内变量被销毁时，会引起指针的非法使用

    fun9(1);//x = 1
    fun9();//x = 0，缺省实参
    funa(1);

    func();//没给实参时，编译器会将func()解释为func(x)，而不是func(3).输出为3

    x = 5;//注意不是int x = 5;全局变量和局部变量的区别
    func();//输出为5
}

