## 1.语句基础
表达式加分号。

复合语句：由大括号组成，无需在结尾加分号，形成独立的域（明确变量的生存周期）

顺序和非顺序语句

最基本的非顺序语句是`goto`，不建议使用。

## 2.分支语句
### if
包含分支是一整条语句，多条`if else`嵌套，可实现多重分支。`if ... else if ...`是嵌套出来的。

`if constexpr`可以优化程序，在编辑期进行分支，而非运行期。提高代码效率

`if`还可以带初始化语句

### switch
`switch`下可以加任何语句，`for`语句也可以。
条件为可以隐式转换为整形或枚举类型的变量，可以包含初始化语句

`case/default`标签，在`case/default`中定义要加`{}`。
因为`switch`本身就是跳转，跳转到对应的`case`中，不希望跳转过变量的定义，给定一个生命周期。

## 3.循环语句
### while
while中不包含初始化语句

### do while
循环结尾要有分号，同样不包含初始化。

### for
可在初始化中包含多个声明，但需要确保每个声明类型相同。如`int a, b;`

`int a, double b;`这种语句非法。而且，`int* p ,q;`表示q为非指针，容易引起误解。`int* p, *q;`为指针。

除了for中初始化，不建议将多个声明一起初始化。

for的条件可为空

### range-for
语法糖，编译器会自动将该range-for转为for循环。详见c++ insights

只读元素时，可使用左值引用`for(auto&)`；写元素时，建议使用万能引用`for(auto&&)`

### break，continue
前者是终止循环，后者是跳过循环体剩余部分，执行下一次循环。（不适用于多重循环）

可使用goto跳转于多重循环

## 4.达夫设备
将switch里套了个循环。

提高性能，让性能消耗在改用的语句上。