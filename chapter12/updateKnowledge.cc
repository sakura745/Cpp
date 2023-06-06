#include <iostream>
#include <vector>
#include <memory>

namespace updateKnowledge {
   class Base {
   public:
       int x;
   private:
       int y;
   protected:
       int z;
   };
    class Derive_public : public /* **是一个** 的行为*/ Base {//99%的程序都是public继承
    public:
    //        int  x;//x 在 Derive_public 还是public权限
    protected:
    //        int z;//z 在 Derive_public 还是protected权限
    };
    class Derive_private : private /* **根据基类实现出** 的行为*/ Base {
    private:
        //        int x;//x 在 Derive_public 是private权限
        //        int z;//z 在 Derive_public 是private权限
    };
    class Derive_protected : protected /*没人用*/ Base {
    protected:
    //        int x;//x 在 Derive_public 是protected权限
    //        int z;//z 在 Derive_public 是protected权限
    };

    class Base2 {
    public:
        int x;
        void fun(int) {

        }
    private:
        int y;
    protected:
        int z;
        void fun() {

        }
    };
    class Derive2 : public Base2 {
    public:
        using/*可以改变数据成员z的权限，同理也可以改变函数权限*/ Base2::z;
        using Base2::fun/*给出的是名称，不是函数，没有()*/;
        //对于函数来说，如果函数fun()有重载函数，且权限不一样呢？ using修改的是所有重载函数的权限。
    private:
    //        using Base2::x;//修改了x的权限。
    //        Base2::y;//illegal 因为是基类的private，不能用在派生类中。在派生类中，无论改成什么权限都会报错
    };

    class Base3 {
    protected:
        Base3(int val) /*构造函数不一定都是public的*/{

        }
    };
    class Derive3 : public Base3 {
    public:
        using Base3::Base3;
    };

    class Base3_1 {
    protected:
        Base3_1() {}
        Base3_1(const Base3_1&) {}
    };
    class Derive3_1 : public Base3_1 {
    public:
        using Base3_1::Base3_1;
    };

    class Base4 {
    protected:
        virtual/*不是虚函数，也可以在派生类修改*/ void fun() {
            std::cout << "1" << std::endl;
        }
        virtual void fun(int) {
            std::cout << "2" << std::endl;
        }
    };
    class Derive4 : public Base4 {
    public:
        using Base4::fun;
    };

    class Base5 {
    protected:
        virtual void fun() {
            std::cout << "1" << std::endl;
        }
        virtual void fun(int) {
            std::cout << "2" << std::endl;
        }
    };
    class Derive5 : public Base5 {
    public:
        using Base5::fun;

        void fun(int) override {
            std::cout << "3" << std::endl;
        }
        //using的优先级低于override
    };


    class Base6 {
    public:
        friend void fun(const Base6&);
    protected:
        int x = 10;
    };
    class Derive6 : public Base6 {
    private:
        int y = 20;
    };
    void fun(const Base6& val) {
        std::cout << val.x << std::endl;
    }


    class Base7 {
    protected:
        int x = 10;
    };
    class Derive7 : public Base7 {
    public:
//        friend void fun(const Base7&);
        friend void fun(const Derive7&);
    private:
        int y = 20;
    };
//    void fun(const Base7& val) {
//        std::cout << val.x << std::endl;//illegal 不能在派生类中定义基类的友元
//    }
    void fun(const Derive7& val) {
        std::cout << val.x << std::endl;
    }


    class Derive8;//先给一个声明，否则Base8中的fun参数编译器不认识
    class Base8 {
    public:
        friend void fun(const Derive8&);
        friend void fun1(const Derive8&);
    protected:
        int x = 100;
    };
    class Derive8 : public Base8 {
    private:
        int y = 20;
    };
    void fun(const Derive8& val) {
        std::cout << val.x << std::endl;
    }
    void fun1(const Derive8& val) {
//        std::cout << val.y << std::endl;//illegal. fun1()只能访问Derive8中隶属于Base8的那一部分
    }

    class Base9 {
    public:
        virtual double/*取double和int中范围大的类型，因为虚函数的重写不改变返回类型*/ getValue() = 0;
        virtual ~Base9() = default;//基类指针指向派生类对象，防止内存泄漏
    };
    class Derive9 final : public Base9 {
    public:
        Derive9(int x)
            : val(x)
        {}
        double getValue() override {
            return val;
        }
        int val;
    };
    class Derive9_2 final : public Base9 {
    public:
        Derive9_2(double x)
                : val(x)
        {}
        double getValue() override {
            return val;
        }
        double val;
    };

    class Base10 {
    public:
        virtual ~Base10() = default;
    };
    class Base10_2 {
    public:
        virtual ~Base10_2() = default;
    };
    class Derive10 final : public Base10, public Base10_2/*多重继承*/ {
    public:
    };


    class BBase11 {
    public:
        int x;
        virtual ~BBase11() = default;
    };
    class Base11 : virtual public BBase11 {
    public:
        virtual ~Base11() = default;
    };
    class Base11_2 : virtual public BBase11{
    public:
        virtual ~Base11_2() = default;
    };
    class Derive11 final : public Base11, public Base11_2 {
    public:
    };

    class Base12 {
    };
    class Derive12 : public Base12 {
    };

    class Base13 {
        void fun() {}
    };
    class Derive13 : public Base13 {
    };

    class Base14 {
        void fun() {}
    };
    class Derive14 {
        int x;
        Base14 b1;
    };

    class Base15 {
        void fun() {}
    };
    class Derive15 : public Base15 {//空基类优化
        int x;
    };

    class Base16 {
        void fun() {}
    };
    class Derive16 {
        int x;
        [[no_unique_address]] Base16 b1;
    };


}

using namespace updateKnowledge;

int main() {
    //派生类的继承可以有public private protected。无论是哪种继承，派生类对基类成员的访问权限都不改变。
    //基类public，派生可以访问；基类private，派生无法访问；基类protected，派生可以访问

    Derive2 d;
    d.x;
    d.z;//illegal. z对派生是protected，外部无法访问。 引入 public: using Base2::z; 则可以访问
    d.fun();
    d.fun(1);

//    Derive3 d2(100);//‘updateKnowledge::Base3::Base3(int)’ is protected within this context. 还是protected权限
    Derive3_1 d2_1;//单参构造变成缺省构造就可以了，为什么？因为Derive3_1在构造过程中，编译器发现没有构造函数，编译器
    //合成缺省构造，因此会调用基类的缺省构造函数。在派生类构造完成之后，才会通过using语句在派生类中将基类构造变为
    //public权限。就是说Derive3_1 d2_1;的合法性是通过派生类缺省构造函数调用基类缺省构造得来的
    Derive3_1 d2_2(d2_1);//

    Derive4 d3;
    d3.fun();
    d3.fun(3);

    Derive5 d4;
    d4.fun();
    d4.fun(3);//在派生类中重写了fun(int)。

    Base6 b;
    fun(b);


    Base7 b1;
//    fun(b1);//illegal.
    Derive7 d5;
    fun(d5);

    ///权限有传递性，但是友元在派生和基类中没有传递性

    Derive8 d6;
    fun(d6);//legal. Derive8 是一个 Base8.所以可以访问Base8的成员
    std::cout << "--------------------------" << std::endl;


    //通过基类指针在容器中保存不同类型对象，有一个条件，类型需要找到一个公共类型可以代表的。比如double和int

    std::vector<std::shared_ptr<Base9>> vec;//可以用Base9保存int double类型的vector
    vec.emplace_back(new Derive9{1});
    vec.emplace_back(new Derive9_2{33.1});

    std::cout << vec[0]->getValue() << std::endl;
    std::cout << vec[1]->getValue() << std::endl;


    Derive11 d7;
//    d7.x;//不知道是从Base11  的基类BBase11中获取x，
           //    还是从Base11_2的基类BBase11中获取x
    //通过virtual虚继承来获取
    d7.x;//因为Base11和Base11_2都是虚继承于BBase11，编译器在构造的对象里只保存BBase11的一个实例

    std::cout << sizeof(Base12) << std::endl;//输出1。为了区别Base12 a[10]中的 a[0] 和 a[1]的区别，所以为不能为0，设置为1
    std::cout << sizeof(Base13) << std::endl;//还是1
    std::cout << alignof(Derive14) << std::endl;//输出4
    std::cout << sizeof(Derive14) << std::endl;//输出8 : 4 + 1 -> 8
    //为了节省空间，同时还满足在Derive14中，可以使用Base14的函数，因此将Derive14设置派生为Base14中，
    //有Base15 Derive15。称之为 空基类优化（编译器优化）：如果基类没有成员变量或虚函数，基类所占内存可以省掉
    std::cout << sizeof(Derive15) << std::endl;//输出4
    std::cout << sizeof(Derive16) << std::endl;//输出4 通过[[no_unique_address]]完成

}