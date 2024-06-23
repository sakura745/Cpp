## 1.结构体与对象的聚合
`struct.cc`

`static`通常使用在头文件中:

类外定义时，`static`关键字需省略

类内静态数据成员的地址的使用

对于**已知类型**的成员函数，**可以**将其设置为类内`inline`来使用，也可以在类外进行定义，类外定义是否包含`inline`都行

对于**类型为类**的成员函数，**不可**将其设置为类内`inline`来使用，但可以在类外进行定义，类外定义是否包含`inline`都行
## 2.成员函数
`memberFunction.cc`
成员函数也叫方法。区分于算法。

在结构体中，将数据与相关的成员函数（方法）组合在一起，形成了**类**

类内定义隐式内联

类视为一种抽象的数据类型，通过成员函数（接口）进行交互

类内声明+类外定义：用于给用户公共头文件和链接库，接口实现细节自己掌握的方法，来使用成员函数

## 3.访问限定符与友元
`access.cc`

权限的引用是为了对抽象数据类型进行封装

不考虑继承，`private` 和 `protected`一样

可以使用友元`friend`来打破权限限制(走后门) -- **慎用**

声明**函数**或者**类**是当前类的友元

`friend` 是不区分访问限定的
## 4.构造、析构与复制成员函数
构造函数是特殊的成员函数，在构造对象时，调用的函数。构造函数没有返回类型

**构造函数**：缺省构造函数、单一构造函数、拷贝构造函数、移动构造函数(c11)。
初始化列表是构造函数特有的

`constructorDestructor.cc`构造函数、初始化列表和缺省构造函数

`constructorDestructor2.cc`单参构造函数、拷贝构造函数和移动构造函数。
复制的本质就是调用拷贝构造函数

`constructorDestructor3.cc`拷贝赋值函数、移动赋值函数和析构函数
**拷贝赋值**与**移动赋值**函数`operator =`

**析构函数**

`constructorDestructor4.cc` `delete`关键字：某些函数对于程序运行来说是必不可少的，但是其功能又不是想要的，因此可以采用该
关键字或者是希望引入部分功能，摒弃另一部分

有`destructor` 就需要 `copy constructor` & `copy assignment`。

有`copy constructor`就需要 `copy assignment`。

有`copy constructor/assignment` 也可以考虑 `move constructor/assignment`。


**下图中，红框表示可能会废除的行为**
（单参构造函数不属于特殊函数，不可以使用`default`关键字）

![specialMembers](https://github.com/sakura745/Picx_image_host/raw/master/20230924/specialMembers.2kr4lw8aw4g0.jpg)

**[cppreference:useful resources](https://en.cppreference.com/w/cpp/links)** 可以查到c98 c11 c14 c17 c20等标准

## 5.字面值类，成员指针与`bind`交互

### 字面值类 
`literal.cc`

字面值类：可以构造成比编译期常量的类型

抽象数据类型构造成编译期常量

c14取消了constexpr成员函数缺省为const成员函数。如有需要，显式给出const限制符
### 成员指针
`memberPointer.cc`
成员指针有数据成员指针和成员函数指针

成员函数指针可以指向声明，而非定义

对于成员函数指针来说，`.*`是一个操作符，不是`.` `*`分开的操作符

对象`.*`成员指针

对象指针`->*`成员指针
### `bind`
成员函数指针不能单独使用，要引入类的对象作为第二个参数来使用
