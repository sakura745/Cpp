#include <iostream>
#include <utility>//引入forward

void g(int&) {
    std::cout << "L-reference.\n";
}
void g(int&&) {
    std::cout << "R-reference.\n";
}

template <typename T>
void fun(T input) {
    g(input);
}

template <typename T>
void fun2(T&& input) {
    g(input);
}

template <typename T>
void fun3(T&& input) {
    g(std::forward<T>/*c11 完美转发*/(input));
}

template <typename T>
void fun4(T input) {
    g(std::forward<T>(input));
}

template <typename... T>
void fun5(T&&... input) {
    g(std::forward<T>(input)...);
}

int main() {
    int x = 3;
    g(x);//输出：L-reference.
    g(3);//输出：R-reference.

    fun(x);//输出：L-reference.
    fun(3);//输出：L-reference.
    //因为T被推导为int，input是左值

    fun2(x);//输出：L-reference.
    fun2(3);//输出：L-reference.
    //T改为万能引用。虽然当input为右值3时，T被推导为int&& 右值引用，但是 右值引用作为表达式时为左值

    //引入std::forward()函数，与万能引用结合使用
    fun3(x);//输出：L-reference.
    fun3(3);//输出：R-reference.

    //forward单独使用，都将视为右值。因为属于拷贝，就相当于传入一个副本，都是int变量，通过forward会变成右值
    fun4(x);//输出：R-reference.
    fun4(3);//输出：R-reference.

    //包展开
    fun5(x);//输出：L-reference.
    fun5(3);//输出：R-reference.


    //c20 lambda模板表达式
    auto lambda = []<class T> (T a, auto&&/*万能引用*/ b) {
        return a + b;
    };

    auto lambda2 = []<typename... Ts> (Ts&&... ts) {
        //...
    };
}