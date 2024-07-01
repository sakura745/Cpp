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
singletonInst: 0x62e6785e7164
singletonInst2: 0x62e6785e7164
Sing destroy
```
---
```shell
./ms
```
输出为
```shell
Sing construct
singletonInst: 0x603844285174
singletonInst2: 0
Sing destroy
```
发现编译之后链接顺序不同，导致输出结果不同

未被初始化过的全局指针，指向为0的地址