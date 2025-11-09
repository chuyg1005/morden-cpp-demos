# C++ 全面学习项目

这个项目旨在帮助开发者全面掌握C++编程语言的核心概念和现代特性。通过实际示例演示了从基础到高级的各种C++技术。

## 项目结构

```
cpp-learning-demo/
├── main.cpp                           # 主程序，演示所有C++技术
├── CMakeLists.txt                     # 构建配置文件
├── meta-programming/                  # 元编程技术
│   ├── type_traits_demo.h             # 类型特征示例
│   ├── template_specialization_demo.h # 模板特化示例
│   ├── sfinae_demo.h                  # SFINAE示例
│   ├── constexpr_demo.h               # constexpr和编译时计算示例
│   ├── variadic_templates_demo.h      # 可变参数模板示例
│   ├── type_introspection_demo.h      # 类型 introspection 示例
│   └── crtp_demo.h                    # CRTP示例
├── smart-pointers/                    # 智能指针
│   └── smart_pointers_demo.h          # 智能指针使用示例
├── stl-containers/                    # STL容器
│   └── stl_containers_demo.h          # STL容器使用示例
├── stl-algorithms/                    # STL算法
│   └── stl_algorithms_demo.h          # STL算法使用示例
├── move-semantics/                    # 移动语义
│   └── move_semantics_demo.h          # 移动语义示例
├── exception-handling/                # 异常处理
│   └── exception_handling_demo.h      # 异常处理示例
├── multithreading/                    # 多线程编程
│   └── multithreading_demo.h          # 多线程编程示例
├── design-patterns/                   # 设计模式
│   └── design_patterns_demo.h         # 设计模式示例
└── modern-cpp-features/               # 现代C++特性
    └── modern_cpp_features_demo.h     # 现代C++特性示例
```

## C++ 技术主题

### 1. 元编程 (Meta-programming)
文件目录: `meta-programming/`

涵盖C++模板元编程的核心技术：
- 类型特征 (Type Traits)
- 模板特化 (Template Specialization)
- SFINAE (Substitution Failure Is Not An Error)
- Constexpr 和编译时计算
- 可变参数模板 (Variadic Templates)
- 类型 introspection
- CRTP (奇异递归模板模式)

### 2. 智能指针 (Smart Pointers)
文件目录: `smart-pointers/`

演示现代C++内存管理技术：
- `unique_ptr` - 独占所有权的智能指针
- `shared_ptr` - 共享所有权的智能指针
- `weak_ptr` - 解决循环引用的智能指针
- 智能指针的最佳实践

### 3. STL 容器 (STL Containers)
文件目录: `stl-containers/`

涵盖标准模板库中的各种容器：
- 序列容器: `vector`, `array`, `deque`, `list`, `forward_list`
- 关联容器: `set`, `map`, `multiset`, `multimap`
- 无序关联容器: `unordered_set`, `unordered_map`
- 容器性能比较和选择指南

### 4. STL 算法 (STL Algorithms)
文件目录: `stl-algorithms/`

演示STL算法库的使用：
- 非修改性序列算法
- 修改性序列算法
- 排序和相关算法
- 数值算法
- 集合算法
- 算法性能优化

### 5. 移动语义 (Move Semantics)
文件目录: `move-semantics/`

现代C++性能优化的关键技术：
- 右值引用和移动语义
- 移动构造函数和移动赋值运算符
- `std::move` 的使用
- 完美转发 (Perfect Forwarding)
- 移动迭代器

### 6. 异常处理 (Exception Handling)
文件目录: `exception-handling/`

C++错误处理机制：
- 基本异常处理语法
- 自定义异常类
- 异常安全保证级别
- 函数try块
- `noexcept` 规格说明符

### 7. 多线程编程 (Multithreading)
文件目录: `multithreading/`

并发编程技术：
- 基本线程操作
- 互斥锁和条件变量
- 原子操作
- 异步操作和future
- 共享互斥锁

### 8. 设计模式 (Design Patterns)
文件目录: `design-patterns/`

经典设计模式在C++中的实现：
- 单例模式 (Singleton)
- 观察者模式 (Observer)
- 策略模式 (Strategy)
- 装饰器模式 (Decorator)
- 工厂模式 (Factory)

### 9. 现代C++特性 (Modern C++ Features)
文件目录: `modern-cpp-features/`

C++11/14/17/20的新特性：
- `auto`关键字和类型推导
- 范围for循环
- Lambda表达式
- `std::optional`, `std::variant`, `std::any`
- 结构化绑定
- `if constexpr`
- 折叠表达式

## 编译和运行

```bash
# 克隆项目
git clone <项目地址>
cd cpp-learning-demo

# 使用CMake构建项目
cmake .
make

# 运行程序
./cpp_learning_demo
```

## 学习建议

1. 从 `main.cpp` 开始，查看每种技术的演示
2. 阅读每个头文件中的实现代码和注释
3. 修改代码并观察结果，加深理解
4. 尝试添加自己的示例来练习这些技术
5. 按照目录顺序学习，从基础到高级逐步深入

## 参考资料

- [C++ Reference](https://en.cppreference.com/w/)
- 《C++ Primer》
- 《Effective Modern C++》
- 《C++ Templates: The Complete Guide》
- 《C++ Concurrency in Action》