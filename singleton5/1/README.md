将`sing.cpp`中的`static Sing::Init init;`注释掉，之后
运行`build_cmd`
```shell
./build_cmd
```
再分别运行`sm` 和 `ms`
```shell
./sm
```
输出为
```shell
Sing construct
get value: 100
0x5f7b2cd69eb0
100
Sing destroy
```
---
```shell
./ms
```
输出为
```shell
Sing construct
get value: 100
0
Segmentation fault (core dumped)
```

`./ms`输出的原因是：先执行`main.cpp`中的全局变量的初始化时，都正常。
再到`sing.cpp`时，调用 `MyUniquePtr<Sing> singletonInst;`进行缺省初始化，会调用其构造函数，将其赋为空，
再调用`main`函数，则会显示零初始化的0，当然，没有指针还会指向对象，会报错。

说的简单点，相当于在`sing.cpp`中，是先调用`Init()`再构造`singletonInst`，导致的未定义行为

`unique`的构造函数中出现的`constexpr`是否要在编译期被求值也是一个未定义行为，一共两个未定义的行为

---

---

将`sing.cpp`中的`static Sing::Init init;`恢复，之后
运行`build_cmd`
```shell
./build_cmd
```
再分别运行`sm` 和 `ms`
```shell
./sm
```
输出为
```shell
Sing construct
get value: 100
0x5f7b2cd69eb0
100
Sing destroy
```
---
```shell
./ms
```
输出为
```shell
Sing construct
Sing construct
get value: 100
0x5df0cca272e0
100
Sing destroy
```
有两个`Sing construct`，而只有一次`Sing destory`。这也是未定义行为的表现

在`sing.cpp`中，在最后又加入了`static Sing::Init init;`，让`singletonInst`又一次初始化，
判断`singletonInst`为空，调用`Sing()`的构造函数，给`singletonInst`的`val`赋100