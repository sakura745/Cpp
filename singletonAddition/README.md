## 额外的评注
### 第三品与第九品的性能对比
`./build_cmd`中给出了两个测试指令，分别将第三品和第九品的main函数中的**循环**打开，其余代码注释掉，然后通过`build_cmd`第一行指令编译

第三品使用`/usr/bin/time ./a.out`
```shell
Sing construct
Sing destroy
Command exited with non-zero status 157
0.49user 0.00system 0:00.49elapsed 100%CPU (0avgtext+0avgdata 3424maxresident)k
0inputs+0outputs (0major+140minor)pagefaults 0swaps
```
时间为0.49


第九品使用`/usr/bin/time ./a.out`
```shell
Sing1 construct
Sing2 construct
Sing2 destroy
Sing1 destroy
Command exited with non-zero status 157
0.15user 0.00system 0:00.15elapsed 100%CPU (0avgtext+0avgdata 3456maxresident)k
0inputs+0outputs (0major+139minor)pagefaults 0swaps
```
时间为0.15


第三品使用`valgrind --tool=callgrind ./a.out`
```shell
Sing construct
Sing destroy
==74489== 
==74489== Events    : Ir
==74489== Collected : 9002306889
==74489== 
==74489== I   refs:      9,002,306,889
```
执行了`9,002,306,889`条指令

第九品使用`valgrind --tool=callgrind ./a.out`
```shell
Sing1 construct
Sing2 construct
Sing2 destroy
Sing1 destroy
==74637== 
==74637== Events    : Ir
==74637== Collected : 2752297301
==74637== 
==74637== I   refs:      2,752,297,301
```
执行了`2,752,297,301`条指令
### C++标准IO流的实现方式
- [ios_base::init 类](https://en.cppreference.com/w/cpp/io/ios_base/Init)
- [GCC的实现示例](https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/src/c%2B%2B98/ios_init.cc)

### 如果在实现单例A的逻辑时：
- 部分实现逻辑在源文件而非头文件中
- 源文件中的逻辑使用了单例 **B** 的内容
- 那么一定要将单例  **B** 的头文件置于单例 **A** 的 **头文件** 中