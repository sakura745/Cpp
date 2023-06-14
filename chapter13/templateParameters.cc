#include <vector>

template <int a/*数值作为模板参数*/>
int fun(int x) {
    return x + a;
}

template <typename T, T a>
auto fun2(T x) {
    return static_cast<T>(x + a);
}

template <auto a/*c17*/>
void fun3() {
}

template <typename T>
class C{};

template <template <typename T> class/*模板作为模板参数*/ T2>//T没用：该行表示当前模板的模板参数为类模板，该类模板的模板参数是T。
//template <template <typename> typename T2>//legal。T可以省略，c17之后 class可以替换成typename
void fun4() {
    T2<int> tmp;
}

template <typename T1, typename T2>
class C2{};

template <template <typename, typename> typename T2>
void fun5() {
}


template <typename T1, typename T2 = int>
class C3{};

template <template <typename/*缺省模板实参*/> typename T2>
void fun6() {
}

template<>
void fun6<C3>() {

}

int main() {
    fun<3>(5);
///    fun2<float, 3.1f>(5.1f);//gcc11支持

    fun3<3>();
    fun3<false>();

    fun4<C>();
    fun4<std::vector>();

    fun5<C2>();


}