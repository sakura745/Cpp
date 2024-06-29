#include <iostream>
#include <string>

//结构体
struct Str {
    int x;
    int y;
};

//联合。表示x y 共享内存
union Uni {
    int x;
    int y;
};

struct S {
    enum Type {
        Char,
        Int
    };
    union Uni2 {
        char x;
        int y;
    };
    //联合通常与枚举一起使用
    Type t;
    Uni2 obj3;
};

struct S2 {
    enum Type {
        Char,
        Int
    };
    union/*匿名联合*/ {
        char x;
        int y;
    };//类似于无作用域枚举，作用域在S2内

    Type t;
};


union Uni3 {
    char x;
    int y;
    std::string s;
    //要定义构造函数等
};

int main() {
    std::cout << sizeof(Str) << std::endl;//输出8
    std::cout << sizeof(Uni) << std::endl;//输出4

    Uni obj;
    obj.x = 100;
    std::cout << obj.y << std::endl;//对obj修改，同时修改了x和y

    std::cout << sizeof(S::Uni2) << std::endl;//输出4：既表示char 又表示int，当然是int

    S::Uni2 obj2;
    obj2.x = 'c';
    std::cout << obj2.y << std::endl;//本质上，是在挑战底层内存的布局。不知道char对应的int中四个字节的哪个字节。行为未定义

    S s;
    s.t = S::Char;
    s.obj3.x = 'c';
    //将enum和union联合到一起，一起使用。但s.obj3.x使用起来有点冗余。采用匿名联合

    S2 s2;
    s2.t = S2::Char;
    s2.x = 'c';

}