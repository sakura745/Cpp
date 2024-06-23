#include <iostream>
#include <string>
namespace ctordtor4 {
    class Str {
    public:
        Str() : ptr(new int()) {}

        ~Str() { delete ptr; }

        //修改：添加拷贝构造函数 -- 改用深拷贝
        Str(const Str& val) : ptr(new int(*(val.ptr))) /*又开辟了一块新内存*/{}

        //修改：添加拷贝赋值函数
        Str& operator=(const Str& val) {
            *ptr = *(val.ptr);
            return *this;
        }

        Str(Str&& val) noexcept
                : ptr(val.ptr) {
            val.ptr = nullptr;
        }

        int& Data() {
            return *ptr;
        }

    private:
        int *ptr;
    };

    void fun(int) = delete;

    void fun(double a) {
        std::cout << "fun(double) is called." << std::endl;
    }

    class Str2 {
    public:
        Str2() = default;

        Str2(const Str2& val) = default;

        Str2(Str2&& val) noexcept = delete;
    };

    void fun1(Str2 val) {}
}
using namespace ctordtor4;
int main() {
    Str a;
    a.Data() = 3;
    std::cout << a.Data() << std::endl;

    Str b(a);//会出现double free 错误。
    //是因为 &(a.ptr) = 1234, a.ptr = 5678 执行的拷贝构造时，&(b.ptr) = 2345, b.ptr = a.ptr = 5678.
    //相当于浅拷贝
    //执行析构函数时，先销毁b 执行delete b。但是b和a指向的是同一块内存，再销毁a，delete a就相当于二次销毁
    //修改 : 定义拷贝构造（将其改为深拷贝），不用默认的

    Str c;
    c = a;//又会出现double free 错误。和拷贝构造一样原因的拷贝赋值错误。修改 ： 定义拷贝赋值，不用默认的

    Str d = std::move(a);//相比于拷贝构造资源的消耗，移动构造会速度加快。相对安全。需要定义拷贝构造，
    // 也要考虑构造移动构造

    //但是对于Str这个类，拷贝赋值函数和移动赋值函数在性能上区别不大。是因为这个类太简单，就一个这指针。

//    fun(3);//illegal:函数对名字重载解析，查找函数时，不会考虑delete。是因为重载解析只会对函数名，形参进行解析
    //对于两个重载函数fun来说，fun(int)是完美匹配
    //fun(double)还需要隐式转换，
    //因此选用fun(int)，但是fun(int) 是delete ，所以会报错
    //但如果fun(int)未被声明，则会直接调用fun(double)
    ///所以说，如果不想让fun()的参数为int，想让参数为double类型，可以使用 void fun(int) = delete;

    fun1(Str2{});//c11会报错 c17以上不会报错。因为c17对临时对象引入了named RVO

}