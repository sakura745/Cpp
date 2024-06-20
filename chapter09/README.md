## 1.容器概述
一种特殊的类型，其对象可以放置其他类型的对象。属于模板

增删改查（CRUD）
### 容器分类
- 序列容器：有序排列，使用整数值索引
- 关联容器：顺序不重要，使用键索引
- 适配器：调整原有容器行为，使其对外展现新的类型、接口或 (c20)返回新的元素
- 生成器(c20)
### 迭代器
`iterator.cc`
用于指定容器的一段区间，以执行遍历、删除等操作

用来模拟数组的指针，但没有指针那么强大。根据操作的不同，分为5类:Input Iterator, Output Iterator, Forward Iterator, Bidirectional
Iterator, Random Access Iterator.

range：支持迭代器

## 2.序列容器
### `array`容器模板
元素个数固定的序列容器

`array.cc`
不支持添加、删除操作。与内建数组相比，提供了复制操作。

容器连续存储，会有`data`元素访问

**复制和交换，维护数组，成本较高**
### `vector` (c98)
`vector.cc`
元素数目可变

不提供`push_front()/pop_front()`接口，可以通过使用`insert()/erase()`来替代，但效率较低

**写操作可能会导致迭代器失效**

### `list`(c98), `forward_list`(c11), `deque`, `basic_string`
`otherSequenceContainer.cc`

`list` **写操作通常不会导致迭代器失效**

`forward_list` 迭代器只支持向后（递增）操作

`deque` **double ended queue**的简写，是vector和list的折中组合。一段一段的。段中的元素是连续的，每段之间不连续

`basic_string` 

## 3.关联容器
都是键值对，不过`set`的键是给一个变量，值是是否存在与该集合中。
### `set`,`map`,`multiset`,`multimap`
底层是用红黑树实现的，key都为const类型

`set.cc`元素支持比较大小，元素访问不支持`[]`  `set`迭代器指的对象是const类型

### `unordered_xxx`底层是哈希表实现的。
`unordered_xxx.cc`
底层是hash表实现的

## 4.适配器与生成器
对现有容器的调整，而产生新的接口

**XXX_view的使用，是给XXX对象生成一种视图（view），既然是视图，不考虑复制操作，因此没必要使用引用&，来获取视图**
### 类型适配器
`typeAdaptor.cc`
`string_view` c17支持字符串类型，推荐作为函数形参（不使用引用&的形式，直接使用），不推荐作为函数返回类型
只读，不可写

`span` c20支持非字符串类型，使用与连续容器，如`vector` `array`等
可读可写
### 接口适配器
`interfaceAdaptor.cc`
对底层容器配置接口

`stack`底层容器为`deque`

`queue`底层容器为`deque`

`priority_queue`底层容器为`vector`
### 数值适配器(c20)
`otherAdaptor.cc`

STL 2.0 `ranges` c20，求值过程是缓式求值

`std::ranges::XXX_view` -> `std::ranges::views::XXX` -> `std::views::XXX`

如`std::ranges::filter_view`改用`std::views::filter`

### 生成器(c20)
STL 2.0 `ranges`





