### 1.从hello world 开始谈起
函数：返回类型、函数名、形参列表、函数体

`main`函数：整个程序的入口

类型：是C++引入的概念，不是硬件引入的。

### 2.系统I/O
`iostream`标准库提供的接口，用于人机交互。

输入流`cin`

输出流`cout` `cerr` `clog`

|传出位置|屏幕|文件日志|
|---|---|---|
|名称|`cout`、`cerr`、`clog`|`cerr`、`clog`|

|名称|`cout`|`cerr`|`clog`|
|---|---|---|---|
|是否立即缓冲|否|否|是| 

| |缓冲|换行|
|---|---|---|
|`std::flush`|是|否|
|`'\n'`|否|是|
|`std::endl`|是|是|

`#include<cstdio> printf`比较直观，但容易出错。

`#include<iostream> cout`不容易出错，但书写冗长。

