io:

终端输入
```shell
./io > txt1 2 > txt2
cat ./txt1
cat ./txt2
```
分别显示
```shell
Output from cout
```
```shell
Output from cerrOutput from clog
```
---
namespace:
输出(mangling)
```shell
nm ./namespace.cpp.o 
```

```shell
                 U __cxa_atexit
                 U __dso_handle
                 U _GLOBAL_OFFSET_TABLE_
0000000000000062 t _GLOBAL__sub_I__ZN10NameSpace13funEv
000000000000000e T main
0000000000000019 t _Z41__static_initialization_and_destruction_0ii
0000000000000000 T _ZN10NameSpace13funEv
0000000000000007 T _ZN10NameSpace23funEv
                 U _ZNSt8ios_base4InitC1Ev
                 U _ZNSt8ios_base4InitD1Ev
0000000000000000 b _ZStL8__ioinit
```

demangling
```shell
nm ./namespace.cpp.o | c++filt -t
```

```shell
                 U __cxa_atexit
                 U __dso_handle
                 U _GLOBAL_OFFSET_TABLE_
0000000000000062 unsigned short _GLOBAL__sub_I__ZN10NameSpace13funEv
000000000000000e T main
0000000000000019 unsigned short __static_initialization_and_destruction_0(int, int)
0000000000000000 T NameSpace1::fun()
0000000000000007 T NameSpace2::fun()
                 U std::ios_base::Init::Init()
                 U std::ios_base::Init::~Init()
0000000000000000 bool std::__ioinit
```