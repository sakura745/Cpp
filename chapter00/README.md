## 1.什么是C++

C语言的一种扩展，关注性能
- 与底层硬件结合(对比与java):Little Endian、Big Endian
- 对象声明周期的精确控制(对比与C#):异常
- Zero-overhead Abstraction(对比与C#):减少语言特性付出的成本


## 2.C++的编译、链接模型

```mermaid
graph LR;
A[源文件] -->|预处理| B[翻译单元]
B --> |编译| C[汇编代码]
C --> |汇编| D[目标文件]
D --> |链接| E[可执行程序]
```

**源文件**`main.cpp`预处理为**翻译单元**`main.i` : `g++ -E main.cpp -o main.i`

**翻译单元**`main.i`编译为**汇编代码**`main.s` : `g++ -S main.i -o main.s`

**汇编代码**`main.s`汇编为**目标文件**`main.o` : `g++ -c main.s -o main.o`


不同的`*.cpp`就属于不同的翻译单元
