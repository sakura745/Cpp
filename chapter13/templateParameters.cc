#include <vector>
#include <iostream>

template <int a/*数值作为模板参数*/>
int fun(int x) {
    return x + a;
}

template <typename T, T a>
auto fun2(T x) {
    return static_cast<T>(x + a);
}

template <auto a/*c17*/>
void fun3() {}

//c20之后才可以对浮点数进行数据模板
template <float x>
void funf() {}


template <typename T>
class C {};

template <template <typename T> class/*模板作为模板参数*/ T2>//T没用：该行表示当前模板的模板参数为类模板，该类模板的模板参数是T。
//template <template <typename> typename T2>//legal。T可以省略，class可以替换成typename
void fun4() {
    T2<int> tmp;
}

template <typename T1, typename T2>
class C2 {};

template <template <typename, typename> typename T2>
void fun5() {}

//c17开始支持
template <typename T1, typename T2 = int>
class C3 {};

template <template <typename/*缺省模板实参*/> typename T2>
void fun6() {}

template<>
void fun6<C3>() {}

int main() {
    std::cout << fun<3>(5) << std::endl;
    std::cout << fun2<float, 3.1f>(5.1f) << std::endl;//gcc11支持

    //编译器auto自行推导
    fun3<3>();
    fun3<false>();

    funf<3.14f>();
    constexpr/*编译期常量*/ float f = 10000000 - 10000000 + 3.14f;
    constexpr float f2 = 10000000 + 3.14f - 10000000;
    funf<f>();
    funf<f2>();
    //在数学角度，当然f = f2 = 3.14f，但是在计算机来说，就不完全相等。f和f2可能是3.13999999999999和3.14000000000001
    //那上述三个数值模板浮点数的实现会有不同，在c20才支持浮点数，使其相同

    //c17
    fun4<C>();
    fun4<std::vector>();//因为vector中有两个模板参数，其中第二个参数为缺省，因此可以匹配到template<typename>
    //一个模板参数的形式

    fun5<C2>();
    //C2也是两个模板形参，正好匹配上fun5()


}