#include <iostream>

class Out {
    using MyInt = int;
    inline static int val2 = 3;
public:
    class/*类内定义类为嵌套类*/ In {
    public:
        inline static MyInt val = val2;
    };
};


class Out2 {
public:
    class In2 {
    public:
//        inline static MyInt val = val2;//illegal 唯一一个打破二次编译原则
    };
    using MyInt = int;
    inline static int val2 = 3;
};

class Out3 {
    using MyInt = int;
    inline static int val2 = 3;
    int vvv = 100;
public:
    class In3 {
    public:
        inline static MyInt val = val2;
//        int xxx = vvv;//illegal 因为 int vvv = 100;不是定义，是声明（当初始化Out3的对象的时候，才是对其成员函数定义）。
        // 因此对于xxx来说，不能通过vvv来声明。除非用static 就变成定义。是定义还是声明，是否分配内存
        int xx = 100;
    };
//    int vv = In3::xx;//illegal 同理于 int xxx = vvv;
};

void fun() {
    using MyInt = int;
    int val = 100;
    struct/*函数内定义类为局部类*/ Helper {
        MyInt x;
        int y;
//        int z = val;//同理于int xxx = vvv;
        int inc() {
            return ++x;
        }
    };
    //局部类只作为函数中的辅助逻辑，只作用于fun。为了防止名称污染，将类放入函数
    Helper h;
    h.inc();
}

void fun2() {
    using MyInt = int;
    int val = 100;
    struct Helper {
        MyInt x;
        int y;
        int inc();
//        inline static int val2 = 100;//illegal 局部类 不能定义静态数据成员。如果觉得类需要设置静态成员，那么说明该
        //类足够复杂以至于不应该设置为局部类。
    };
//    int Helper::inc() { return ++x; }//illegal函数内不能定义函数
    Helper h;
}

int main() {
    Out::In obj;
    Out::In::val;

    fun();
}