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
Sing destroy
```
---
```shell
./ms
```
输出为
```shell
Segmentation fault (core dumped)
```
发现编译之后，链接顺序不同，导致输出结果不同

