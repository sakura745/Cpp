#include <iostream>
#include <type_traits>

//元函数
template <typename T>
struct Fun {
    using RemRef = typename std::remove_reference<T>::type;
    using type = typename std::add_const<RemRef>::type;
};


//类型和数字作为输入， value作为输出
template <typename T, unsigned S>
struct Fun2 {
private:
    using RemRef = typename std::remove_reference<T>::type;//相当于函数的中间变量，不想暴露在类外
public:
    constexpr static bool value = (sizeof(T) == S);
};

template <typename T, int S>
constexpr auto Fun2_ = Fun2<T, S>::value;

int main() {
    Fun<int&>::type x = 3;// const int x = 3;

    constexpr bool res = Fun2<int&, 4>::value;
    std::cout << res << std::endl;
    std::cout << Fun2<float&, 8>::value << std::endl;

//    Fun2<int&, 5>::RemRef y = 5;//illegal

    std::cout << Fun2_<float&, 8>/*别名模板*/ << std::endl;
}