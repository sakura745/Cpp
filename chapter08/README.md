## 1.动态内存基础
`dyMemory.cc`

保存程序语句的内存只读不写，保存数据内存可读可写。

数据内存有栈内存和堆内存
- 栈内存是编译器执行，更好局部性、性能更强
- 堆内存是运行期扩展，有更大内存空间

避免内存泄漏.

对象构造分两步：先分配内存，再在内存上构造对象。对于内建类型来说，没太大区分。但是对于类来说就很重要。

销毁对象也分两步：先在内存上析构对象，再释放内存。

`new`的几种常见形式
- 构造单一对象/对象数组
- `nothrow new`：内存分配成功与否
- `placement new`：特定预分配内存上构造对象
- `new auto`

`nothrow new`和`placement new`的使用是显式的把堆构造对象的两部分离了

内存管理时，内存对齐是十分重要的

`delete`的常见用法
- 销毁单一对象/对象数组
- `placement delete`

## 2.智能指针
`smartPointer.cc`

`new` 和 `delete` 有问题，引出智能指针。

智能指针是类，有抽象特点。

### shared_ptr
推荐使用 `auto x = std::make_shared<int>(1);`，而不是`std::shared_ptr<int> x(new int(1));`
### unique_ptr
同理推荐使用`auto x = std::make_unique<int>(1);`，而不是`std::unique_ptr<int> x(new int(1));`
### weak_ptr

## 3.相关问题
`others.cc`
### `sizeof`不会返回动态分配的内存大小
### 使用分配器`allocator`来分配内存
### 使用`malloc`、`free`管理内存
C风格
### 使用`aligned_alloc`分配对齐内存
也是C风格的，正是因为`malloc`不能对齐，才引入`aligned_alloc`
### 动态内存与异常安全
通过使用智能指针，能保持系统异常安全（发生异常状态时，程序是安全的）
### c++对于垃圾回收的支持

