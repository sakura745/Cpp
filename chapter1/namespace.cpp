#include <iostream>

namespace  NameSpace1 {
    void fun() {

    }
}

namespace  NameSpace2 {
    void fun() {

    }
}
int main() {
    NameSpace1::fun();//域解析符

    //名字空间别名
    namespace NA1 = NameSpace1;
    NA1::fun();
}
