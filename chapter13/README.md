## 1.函数模板
函数模板不是函数

避免使用函数模板特化
## 2.类模板与成员函数模板
类模板不是类

类模板的特化非常重要
## 3.Concepts (c20)
[Concepts](https://en.cppreference.com/w/cpp/language/constraints) 是一种新的语言特性，它是一种对类型进行约束的机制，
可以帮助程序员编写更加通用和模板化的代码。它可以用于检查类型是否满足特定的要求，或检查函数的参数是否具有特定的行为和属性。
Concepts 可以在编译时捕获错误，让编译器更容易推断类型和参数，提高代码的可读性，可维护性和可重用性。它是通过一种叫
做“concept 模板”的语法进行定义和实现的。Concepts 是 C++ 中重要的语言特性之一，并成为了标准库和模板元编程的基础。

## 4.模板相关内容
数值模板参数与模板模板参数：`templateParameters.cc`

别名模板与变长模板：`aliasVariadic.cc`
通过引入`parameter_pack`从而引入可变长度的模板

如何使用可变长模板，通过[包展开](https://en.cppreference.com/w/cpp/language/parameter_pack)和[折叠表达式](https://en.cppreference.com/w/cpp/language/fold)：`expensionFolding.cc`

完美转发与lambda表达式模板：`perfectForwardingLambda.cc`

消除歧义和变量模板：`resolveAmbiguityVariableTemplates.cc`