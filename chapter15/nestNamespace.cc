#include <iostream>

namespace Out {
    int x;
    namespace In {
        int z;
    }
}

namespace Out {
    int y;
    namespace {
        int q;
    }
}

namespace Out::In/*c17，简化嵌套名字空间的定义*/ {
    int z2;
}

namespace /*匿名名字空间*/{//仅翻译单元可见，可以防止链接时出现的重定义，仅具有内部链接。非匿名名字空间是具有外部链接的
    int w;
}
static int o;//仅翻译单元可见，可以防止链接时出现的重定义，仅具有内部链接。
//但匿名名字空间可以批量给出

int main() {
    Out::x;
    Out::y;
    Out::In::z;

    w;//匿名名字空间内容，对外围直接可见，并不需要使用 域作用符 ::

    Out::q;//匿名名字空间作为嵌套名字空间
}