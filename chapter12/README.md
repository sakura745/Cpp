## 1.运算符重载

可以实现为成员函数和非成员函数。

是否为成员函数的区别是：成员函数会以`*this`作为第一个操作数

[可以实现重载的运算符](https://en.cppreference.com/w/cpp/language/operators)

因为成员函数第一个参数是`*this`，会导致有的运算符重载只能定义为非成员函数。
## 2.类继承
派生类**是一个**基类。 只要有派生类的构建，一直围绕着这一性质展开的。

继承是指一个类（称为派生类或子类）可以继承另一个类（称为基类或父类）的特性和行为。通过类的继承（派生）来引入**是一个**的关系

![inheritance](https://cdn.staticaly.com/gh/sakura745/picx-images-hosting@master/20230604/inheritance.yy6ts2ylbhc.png)

Triangle **is a** Shape，Right Triangle **is a** Triangle，**is** also **a** Shape。

通常采用`public`继承

`protected` = `private` + 派生

### 虚函数
非静态、非构造函数可以声明为虚函数

虚函数的作用是可以与指针（引用）实现动态绑定。

![vtable](https://cdn.staticaly.com/gh/sakura745/picx-images-hosting@master/20230604/vtable.49dz5ft46v40.webp)

