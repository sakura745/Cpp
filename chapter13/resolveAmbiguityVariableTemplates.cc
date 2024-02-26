#include "iostream"

struct Str {
    inline const static int internal = 3;
};

int p = 5;
template <typename T>
void fun() {
    T::internal* p;//一种理解是T所关联的类型，声明类型的指针(*) p是变量名称，另一种理解是internal是T所关联的静态数据成
    // 员，与p相乘(*)。编译器会选择第二种。
}

struct Str2 {
    using internal2 = int;
};
int p2 = 4;
template <typename T>
void fun2() {
//    T::internal2* p2;//没有定义p2，有error:‘p2’ was not declared in this scope
                    //定义    p2，有error:dependent-name ‘T::internal’ is parsed as a non-type, but instantiation yields a type
       //是根据internal类型是根据T来定的，所以是会报dependent-name错，但是T是模板形参，不确定T的类型，因此编译器会选择第二种
}

struct Str3 {
    using internal3 = int;
};

template <typename T>
void fun3() {
    typename/*消除歧义*/ T::internal3* p3;//编译器会认为是第一种
    Str3::internal3* p4;//T给定为Str3，没有歧义
}

struct Str4 {
    template <class T>
    static void internal4() {
    }

    template <class T>
    void internal5() {
    }
};

template <typename T>
void fun4() {
//    T::internal4<int>();//第一种 : internal5是T内部的模板；第二种是<int> <是个小于号，编译器可以这么理解.error :
    // expected primary-expression before ‘int’
    //修改为
    T::template/*消除歧义*/ internal4<int>();
    //和上一个歧义同理，如果T为具体类型，则不会有歧义
    Str4::internal4<int>();

    T obj;
//    obj.internal5<int>();//当函数为非静态函数。同样，internal5依赖T，同样修改
    obj.template internal5<int>();
}

//c14 变量模板
template <typename T>
T pi = (T)3.1415926;


template <typename T>
unsigned mySize = sizeof(T);

template <typename T, unsigned v>
unsigned mySize2 = (sizeof(T) == v);

//is_same_v典型的变量模板（在is_same中能查到）
//template< class T, class U >
//inline constexpr bool is_same_v = is_same<T, U>::value;

int main() {
    fun<Str>();
    fun2<Str2>();
    fun3<Str3>();
    fun4<Str4>();

    std::cout << pi<float> << std::endl;
    std::cout << pi<int> << std::endl;

    std::cout << mySize<float> << std::endl;
    std::cout << mySize<int> << std::endl;

    std::cout << mySize2<float, 1> << std::endl;
    std::cout << mySize2<int, 4> << std::endl;


}