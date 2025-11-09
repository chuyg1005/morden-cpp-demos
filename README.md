# C++ 全面学习项目

这个项目旨在帮助开发者全面掌握C++编程语言的核心概念和现代特性。通过实际示例演示了从基础到高级的各种C++技术。

## 项目结构

```
cpp-learning-demo/
├── main.cpp                                    # 主程序，演示所有C++技术
├── CMakeLists.txt                              # 构建配置文件
├── meta-programming/                           # 元编程技术
│   ├── type_traits/                            # 类型特征示例
│   │   ├── type_traits_base.h                  # 类型特征基础实现
│   │   └── type_traits_demo.h                  # 类型特征演示
│   ├── template_specialization/                # 模板特化示例
│   │   ├── template_specialization_base.h      # 模板特化基础实现
│   │   └── template_specialization_demo.h      # 模板特化演示
│   ├── sfinae/                                 # SFINAE示例
│   │   ├── sfinae_base.h                       # SFINAE基础实现
│   │   └── sfinae_demo.h                       # SFINAE演示
│   ├── constexpr/                              # constexpr示例
│   │   ├── constexpr_base.h                    # constexpr基础实现
│   │   └── constexpr_demo.h                    # constexpr演示
│   ├── variadic_templates/                     # 可变参数模板示例
│   │   ├── variadic_templates_base.h           # 可变参数模板基础实现
│   │   └── variadic_templates_demo.h           # 可变参数模板演示
│   ├── type_introspection/                     # 类型 introspection 示例
│   │   ├── type_introspection_base.h           # 类型 introspection 基础实现
│   │   └── type_introspection_demo.h           # 类型 introspection 演示
│   └── crtp/                                   # CRTP示例
│       ├── crtp_base.h                         # CRTP基础实现
│       └── crtp_demo.h                         # CRTP演示
├── smart-pointers/                             # 智能指针
│   ├── unique_ptr/                             # unique_ptr示例
│   │   └── unique_ptr_demo.h                   # unique_ptr演示
│   ├── shared_ptr/                             # shared_ptr示例
│   │   └── shared_ptr_demo.h                   # shared_ptr演示
│   ├── weak_ptr/                               # weak_ptr示例
│   │   └── weak_ptr_demo.h                     # weak_ptr演示
│   ├── circular_reference/                     # 循环引用示例
│   │   └── circular_reference_demo.h           # 循环引用演示
│   └── smart_pointers_base.h                   # 智能指针基础实现
├── stl-containers/                             # STL容器
│   └── stl_containers_demo.h                   # STL容器使用示例
├── stl-algorithms/                             # STL算法
│   └── stl_algorithms_demo.h                   # STL算法使用示例
├── move-semantics/                             # 移动语义
│   └── move_semantics_demo.h                   # 移动语义示例
├── exception-handling/                         # 异常处理
│   └── exception_handling_demo.h               # 异常处理示例
├── multithreading/                             # 多线程编程
│   ├── thread_safe_queue.h                     # 线程安全队列实现
│   └── multithreading_demo.h                   # 多线程编程示例
├── design-patterns/                            # 设计模式
│   ├── singleton/                              # 单例模式示例
│   │   └── singleton_pattern.h                 # 单例模式实现和演示
│   ├── observer/                               # 观察者模式示例
│   │   └── observer_pattern.h                  # 观察者模式实现和演示
│   ├── strategy/                               # 策略模式示例
│   │   └── strategy_pattern.h                  # 策略模式实现和演示
│   ├── decorator/                              # 装饰器模式示例
│   │   └── decorator_pattern.h                 # 装饰器模式实现和演示
│   ├── factory/                                # 工厂模式示例
│   │   └── factory_pattern.h                   # 工厂模式实现和演示
│   └── design_patterns_base.h                  # 设计模式基础实现
├── function-comparison/                        # 函数比较
│   └── function_comparison_demo.h              # 函数指针、std::function和lambda比较
├── memory-arena/                               # 内存池
│   └── improved_memory_arena.h                 # 改进的内存池实现和演示
└── modern-cpp-features/                        # 现代C++特性
    └── modern_cpp_features_demo.h              # 现代C++特性示例
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
- 线程安全数据结构

### 8. 设计模式 (Design Patterns)
文件目录: `design-patterns/`

经典设计模式在C++中的实现：
- 单例模式 (Singleton)
- 观察者模式 (Observer)
- 策略模式 (Strategy)
- 装饰器模式 (Decorator)
- 工厂模式 (Factory)

### 9. 函数比较 (Function Comparison)
文件目录: `function-comparison/`

比较不同类型的可调用对象：
- 函数指针
- 函数对象(仿函数)
- Lambda表达式
- std::function
- 性能比较和使用场景

### 10. 内存池 (Memory Arena)
文件目录: `memory-arena/`

自定义内存管理技术：
- 内存池实现原理
- 多块内存管理
- 大对象独立分配
- 自定义类型与就地构造
- 性能优化和内存碎片避免

### 11. 现代C++特性 (Modern C++ Features)
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

## 自动化通知

本项目包含GitHub Actions工作流，可以在推送到main分支时发送通知。

### QQ群通知选项

由于GitHub Actions没有直接发送QQ消息的内置功能，提供了以下几种方案：

1. **使用第三方通知服务** (如Server酱) - 需要配置相应的webhook URL
2. **自定义服务** - 需要自己搭建接收通知并转发到QQ的服务
3. **使用Discord作为中介** - 通过Discord机器人转发到QQ

要启用通知功能，需要在GitHub仓库的Secrets中添加相应的配置：
- `QQ_WEBHOOK_URL` - 自定义QQ通知服务的URL
- `SERVERCHAN_KEY` - Server酱的API密钥
- `CUSTOM_SERVICE_TOKEN` - 自定义服务的认证令牌
- `DISCORD_WEBHOOK_URL` - Discord webhook URL

工作流文件位于 `.github/workflows/` 目录下。

## 项目改进

本项目经过重构和改进，具有以下特点：

1. **模块化结构**：每个技术主题都被拆分成多个文件，便于理解和维护
2. **清晰的组织**：相似功能的代码放在同一目录下，结构更加清晰
3. **完整的示例**：每个技术都提供了完整的演示代码和实际应用示例
4. **性能对比**：关键特性提供了性能对比，帮助理解不同方法的优劣
5. **现代C++实践**：使用现代C++特性和最佳实践

## 学习建议

1. 从 `main.cpp` 开始，查看每种技术的演示
2. 阅读每个头文件中的实现代码和注释
3. 修改代码并观察结果，加深理解
4. 尝试添加自己的示例来练习这些技术
5. 按照目录顺序学习，从基础到高级逐步深入
6. 关注性能对比部分，理解不同技术的适用场景

## 参考资料

- [C++ Reference](https://en.cppreference.com/w/)
- 《C++ Primer》
- 《Effective Modern C++》
- 《C++ Templates: The Complete Guide》
- 《C++ Concurrency in Action》