## 第二品

### 基本思路
- 将构造、析构函数设置为私有成员
- 使用静态成员函数获取唯一的实例
### 优点
- 可以防止用户不小心构造新的实例
- c11开始，系统会保证函数内部的静态成员初始化是多线程安全的

### 特点（是优缺点不一定）
- 缓式初始化(lazy initialization)
### 缺点
- 没有完全阻止用户构造该类的多个对象