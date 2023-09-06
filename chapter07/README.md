`cin/cout`是in/out终端，`ifstream/ofstream`是in/out文件，`istringstream/ostringstream`是in/out缓冲区
## 1.IOStream概述
`iostream.cc`
采用流`stream`式，而非记录。stream是序列的意思，每个元素是一个字节。输入输出为字节流。
对应的记录式，则类比于数据库。数据库的底层也是字符。
C++提出了底层基础的输入输出方式。

格式化与解析

输出的处理顺序：格式化-->缓存-->编码转换-->输出

输入的处理顺序：输入-->编码转换-->缓存-->解析

## 2.输入与输出
`in_Output.cc`
分为格式化和非格式化
### 非格式化
对计算机友好
### 格式化
对用户比较友好

是对位移操作符`<<` `>>`的重载

### 格式控制
对输出的修改，不再使用缺省参数
- 位掩码类型 `showpos`
- 字符类型 `fill`
- 取值相对随意 `width` (触发后重置)

### 操纵符（不是操作符）
`setw` `setfill` `endl`

### 提取会放松对格式的限制（输入）

### 提取C风格字符串小心内存越界

## 3.文件与内存操作
### 文件流
`fileStream.cc`

`ofstream`和`ifstream`关联到同一个文件时，只有一个有效。处于打开状态的无法再次打开

多数使用域的形式，域结束可以自动关闭文件。

文件流和IO流一样，都是先进入缓存再输出或者进入文件。那么缓存释放是在什么时候呢，是对应`ifstream`的析构函数完成的。

### 内存流
`memoryStream.cc`

内存和文件、终端一样，也可以读和写。通过`.str()`成员函数来提取内存流中的元素，返回为`string`类型

基于内存流的字符串拼接会优于字符串
## 4.流的状态
`iostate.cc`

流的状态提供了流先前的输入输出是否成功和目前流的信息。可以给出流的不同状态来判断，流采用`位掩码`
- badbit 不可恢复的流错误
- failbot 可以恢复的流错误
- eofbit eof(end of file) 与输入序列有关，走到了流的结尾
- goodbit

注意`fail` 和 `eof` 的异同

<img src="https://cdn.staticaly.com/gh/sakura745/Picx_image_host@master/20230906/Screenshot-from-2023-05-11-23-19-20.26o8gxzpu6f4.png" alt="Screenshot-from-2023-05-11-23-19-20" />

`clear()` `setstate()`复位流的状态
## 5.流的定位
`iolocate.cc`
从哪读取，输出到哪
从哪写入，写入到哪

## 6.流的同步
`ioSync.cc`
刷新缓冲区

