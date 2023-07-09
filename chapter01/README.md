## 1.从hello world 开始谈起
函数：返回类型、函数名、形参列表、函数体

`main`函数：整个程序的入口

类型：是C++引入的概念，不是硬件引入的。

`main.cpp` `annotations.cc`

## 2.系统I/O
`io.cpp` `iostream`标准库提供的接口，用于人机交互。

输入流`cin`

输出流`cout` `cerr` `clog`

|传出位置|屏幕|文件日志|
|---|---|---|
|名称|`cout`、`cerr`、`clog`|`cerr`、`clog`|

| 名称        |`cout`|`cerr`|`clog`|
|-----------|---|---|---|
| 是否立即刷新缓冲区 |否|否|是|
`cerr`不会刷新缓冲区，而会直接显示到控制台上。

| |缓冲|换行|
|---|---|---|
|`std::flush`|是|否|
|`'\n'`|否|是|
|`std::endl`|是|是|

`std::flush` + `\n` = `std::endl`
程序结束时，也会刷新缓冲区。

名字空间：防止名称冲突`namespace.cpp`。不建议在全局域写`using namespace XXX`，尤其是头文件中。因为名字空间就是为了避免名字
冲突所设计的。如果写了，就违背了设计的初衷了。

名字空间与名称改编：`record.md`

`c-styleCpp.cpp`:

`#include<cstdio> printf`比较直观，但容易出错。

`#include<iostream> cout`不容易出错，但书写冗长。

## 3.猜数字与控制流

## 4.结构体与自定义数据类型
`struct.cpp`
