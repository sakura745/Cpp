## 1.结构体与对象的聚合

静态数据成员`static`
## 2.成员函数
成员函数也叫方法。区分于算法。

在结构体中，将数据与相关的成员函数（方法）组合在一起，形成了**类**

类视为一种抽象的数据类型，通过成员函数（接口）进行交互

类内声明+类外定义：用于给公户头文件和链接库来使用成员函数

## 3.访问限定符与友元
不考虑继承，`private` 和 `protected`一样

可以使用友元`friend`来打破权限限制(走后门)

## 4.构造、析构与复制成员函数
构造函数是特殊的成员函数，在构造对象时，调用的函数。构造函数没有返回类型

**构造函数**：缺省构造函数、单一构造函数、拷贝构造函数、移动构造函数(c11)。

复制的本质就是调用拷贝构造函数

**拷贝赋值**与**移动赋值**函数`operator =`

**析构函数**

有`destructor` 就需要 `copy constructor` & `copy assignment`。

有`copy constructor`就需要 `copy assignment`。

有`copy constructor/assignment` 也可以考虑 `move constructor/assignment`。


**下图中，红框表示可能会废除的行为**
![142BI](https://cdn.staticaly.com/gh/sakura745/Picx_image_host@master/20230402/142BI.23g8t0v1suyo.webp)

**[cppreference:useful resources](https://en.cppreference.com/w/cpp/links)** 可以查到c98 c11 c14 c17 c20等标准

## 5.字面值类，成员指针与`bind`交互

### 字面值类 
`literal.cc`

字面值类：可以构造成比编译期常量的类型

抽象数据类型构造成编译期常量

### 成员指针
`memberPointer.cc`

### `bind`
