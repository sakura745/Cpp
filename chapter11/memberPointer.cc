#include <iostream>
#include <type_traits>
#include <functional>

class Str;//Str声明
/*class Str {//Str定义

};*/
class Str2 {
public:
    int x;
    int y;
    inline static int z;
    void fun() {}
    void fun(double) {}
    void fun1(double val) {
        std::cout << val << std::endl;
    }
};


int main() {
    int Str::* ptr;//数据成员指针。* ptr:ptr是一个指针；Str::表示Str域的成员；该成员的类型是int。ptr是Str域内的int成员的指针。
    //ptr类型为int Str::*，全是它的类型信息。
    std::cout << std::is_same_v<decltype(ptr), int Str::*> << std::endl;
    int Str2::* ptr2;
    std::cout << std::is_same_v<decltype(ptr), decltype(ptr2)> << std::endl;//输出为0。因为Str和Str2不是同一类

    void (Str::* ptr_fun)();//函数成员指针。ptr_fun是一个Str域内，接受零个参数(),返回类型为void的函数的指针。
    //Str有声明即可。虽然Str没有包含任何int类型数据成员和没有任何void ()的函数，但是可以声明这样的指针
    double* y;//同理于 可以声明了一个double* 的指针，但是没有包含double的对象

    int Str2::* ptr3 = &Str2::x;//类中的x是声明，但是ptr3仍可以指向声明。成员指针的特殊之处
    int Str2::* ptr4 = &Str2::y;
//    ptr4 - ptr3;//illegal 成员指针不能相减。正常指针可以相减，继承于C语言，C语言用指针相减来求数组的长度

    //为了减少类型的书写长度，可以使用auto
    auto ptr5 = &Str2::x;
    void (Str2::* ptr_fun2)() = &Str2::fun;

//    auto ptr_fun3 = &Str2::fun;//illegal 因为函数成员指针的类型信息也包括函数的参数，使用auto不能区分出函数fun重载
//    int Str2::* ptr6 = &(Str2::x);//illegal。虽然域操作符的优先级高于取址操作符，但是 &(Str2::x) 这样写就修改了原本的含义
    //&(Str2::x)表示(Str2::x)有定义，然后对其取地址。为什么(Str2::x)没有定义，因为类中的x是声明。声明并没有为其分配内存
    //可以将int x改成 static int x;
//    int Str2::* ptr6 = &(Str2::z);//illegal.。静态成员的指针就是单纯的int*类型
    int* ptr7 = &(Str2::z);//still illegal.因为静态变量z没有定义，添加关键字 inline即可

//    *ptr3;//illegal 因为ptr3没有指向真实的地址。Str2中的x只是声明，所以不能解引用

    Str2 obj;
    obj.x = 3;
    Str2 obj2;
    obj2.x = 5;
    std::cout << obj.*ptr3 << std::endl;
    std::cout << obj2.*ptr3 << std::endl;
//    obj2.(*ptr3);//illegal 说明什么？ 说明 .* 是一个整体。.*是一种操作符 : Pointer-to-member

    Str2* ptr_obj = &obj;
    std::cout << ptr_obj->x<< std::endl;
    ptr_obj->x = 30;
    std::cout << ptr_obj->x<< std::endl;
    std::cout << ptr_obj->*ptr3/* ->是ptr_obj的，*是ptr3的。*/ << std::endl;


    //bind
    auto ptr8 = &Str2::fun1;//成员函数指针
    Str2 obj3;
    (obj3.*ptr8)(100);//obj3.*ptr8(100)illegal。因为 .* 是一个整体，要先结合

//    auto x = std::bind(ptr8, 100.0);//illegal 因为不能单独使用成员函数指针，要结合对象一起使用
//    x();
    auto xx = std::bind(ptr8, obj3, 100.0);//引入类的对象作为第二个参数
    xx();

    auto ptr9 = &Str2::x;//数据成员指针
    obj3.*ptr9 = 344;
    auto yy = std::bind(ptr9, obj3);
    std::cout << yy()/*可调用对象，要给一个显式的调用 yy后加()*/ << std::endl;

}