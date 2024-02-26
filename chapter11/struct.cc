#include <iostream>
namespace structSpace {
    struct Str;//结构体的声明

    struct Str {//结构体的定义
        int x;//成员的声明
        int y;//成员的声明
        decltype(3) z;//用decltype声明其类型
//    auto w;//illegal
        decltype(3) z1 = 3;//legal 还是声明。不会分配内存。
//    auto w1 = 3;//illegal 还是声明
        const int x1 = 30;//使用const 等限定，还是声明。

        mutable int ww = 0;//对于Str对象，如果该对象用const限制符修饰，则mutable对象可写，不是只读

        static/*c98 声明 静态数据成员*/ int www;//生命周期是程序启动就有，生命周期与程序生命周期相同
        const static/*c98 const静态成员类内初始化*/ int www2 = 100;
        inline static/*c17 内联静态成员类内初始化*/ int www3 = 100;
        inline static/*静态成员可以使用auto自动推导*/ auto www4 = 100;
    };//必须以分号表示结构体的结束，函数就不用
    int Str::/*::是域操作符，结构体构成了一个域*/www;//c98 静态数据成员的类外定义

    typedef/*c语言用法*/ struct Str2 {
        int x;
        int y;
    } MStr2;//分号宣布结构体结束

    struct Str1;//不完全类型 incomplete type.只有声明，没有定义

    int x;//变量x的定义
    extern int y;//变量y的声明
    extern int z = 0;//变量z的定义，不推荐使用extern int z = 0;初始化，直接使用int z = 0;初始化就行

    struct Str3 {
//    Str3 x;//illegal 编译器无法分配内存

        /*inline*/ static Str3/*类型Str3*/ y;//legal 静态成员不属于某一个对象，（如果属于，某个对象被销毁时，该静态也被销
        // 毁，那其他怎么访问静态成员）
        //也就是说，编译器会单独为静态成员开辟一块内存，不同于结构体定义的不同对象，静态对象与定义的不同对象不存在包含关系
        //相当于Str3内没有对象，属于不完全类型 incomplete type.只有声明，没有定义
    };
//Str3 Str3::y;
    inline Str3 Str3::y;
}
using namespace structSpace;
int main() {
    Str m_str;
    m_str.x = 3;
    std::cout << m_str.x << std::endl;

    MStr2 m_str2;
//    Str1 m;//illegal 编译器不知道具体类型，不能使用
    Str1* ptr;//legal 编译器知道指针类型，可以使用。所有指针类型都是一样的

    //结构体的定义内，包含数据成员的声明。数据成员的定义是隐式的。
    Str m_str3;//结构体的对象的定义，同时隐式定义了数据成员（定义了一般数据成员，静态数据成员没有定义）
    std::cout << m_str.z1/*类内成员初始化 Member Initialization within Class*/ << std::endl;

    Str m_str4{1, 3}; //聚合初始化
    std::cout << m_str4.x << ' ' << m_str4.z/*与聚合初始化数组一样，没有初始化的就默认为0*/ << std::endl;

    Str m_str5{.x = 1, .y = 3};//初始化器c20。为了防止修改结构体内数据成员声明而出现的错误匹配。
    //初始化器属于聚合初始化，聚合初始化不能用在非聚合类型上。聚合类型的定义包含其中之一：没有用户定义的构造函数，
    //所有成员是公有的，没有基类，没有虚函数。

    const Str m_str6{};
//    m_str6.x = 3;//illegal
    m_str6.ww = 5;//结构体中的ww设置为mutable（可修改的），就可以修改

    Str m_str7;
    Str m_str8;
    m_str7.x = 100;
    m_str7.www = 100;
    std::cout << m_str8.x << std::endl;//输出为0
    std::cout << m_str8./*.访问静态数据成员*/www << std::endl;//输出为100，因为www是静态数据成员，共享数据

    Str* ptr1 = &m_str;
    std::cout << ptr1->/*->访问静态数据成员*/www << std::endl;
    std::cout << Str::/*::特有的访问静态数据成员*/www << std::endl;

    Str3 m_str9;
    //对于静态成员的地址来说(相当于运行期问题）：
    std::cout << &(m_str9.y) << std::endl;//illegal 链接错误，没有定义Str3::y。在结构体外添加定义Str3 Str3::y;即可
    //如果对静态成员使用类内内联初始化呢 inline static Str3 y;也会出错，但inline static int y可以。
    //因为编译器解析到inline时，会认为y有明确的定义，会对y的类型Str3有个全面的了解，但是Str3这个结构体没有明确的类型。
    //报错incomplete type
    //可以在结构体外添加定义 inline Str3 Str3::y;这个和Str3 Str3::y;的区别是什么？就是inline的区别
    //即在头文件中构造结构体，在多个编译单元中使用头文件，如果不是inline会出现重定义。

    //因此，对于类内声明静态的类类型的对象，需要在类外使用初始化。类外初始化是否声明为inline都行
}
