# C++ 全面学习项目

这个项目是一个全面的C++学习资源，涵盖了从基础到高级的众多主题。它旨在帮助开发者深入理解现代C++的特性和最佳实践。

## 目录

- [项目概述](#项目概述)
- [项目结构](#项目结构)
- [依赖项](#依赖项)
- [构建和运行](#构建和运行)
- [功能演示](#功能演示)
- [设计模式](#设计模式)
- [测试](#测试)
- [贡献](#贡献)
- [许可证](#许可证)

## 项目概述

本项目包含以下C++主题的演示代码：

1. **元编程** - 类型特征、模板特化、SFINAE、constexpr、可变参数模板、类型introspection、CRTP
2. **智能指针** - unique_ptr、shared_ptr、weak_ptr、循环引用处理
3. **STL容器和算法** - 序列容器、关联容器、无序关联容器、STL算法
4. **移动语义** - 右值引用、移动构造函数、完美转发、移动迭代器
5. **异常处理** - 基本异常处理、异常安全、函数try块、noexcept
6. **多线程编程** - 基本线程操作、互斥锁、条件变量、原子操作、异步操作、共享互斥锁
7. **设计模式** - 单例、观察者、策略、装饰器、工厂（简单工厂、工厂方法、抽象工厂）
8. **现代C++特性** - auto类型推导、范围for循环、Lambda表达式、std::optional、std::variant、std::any、结构化绑定、if constexpr、折叠表达式、Concepts、Ranges、std::format
9. **性能分析和基准测试** - 高精度计时器、函数性能比较、自定义基准测试
10. **文件系统操作** - 目录操作、文件操作、路径操作、文件复制移动、空间信息
11. **网络编程** - TCP客户端/服务器、HTTP客户端、URL解析
12. **内存管理** - 内存池、自定义分配器、内存泄漏检测
13. **与其他语言的互操作性** - C语言互操作、Python互操作概念、JavaScript互操作概念、Rust互操作概念
14. **高级并发编程** - 线程池、无锁数据结构、并发哈希表、原子操作高级用法、异步编程高级用法、线程局部存储
15. **高级设计模式** - 命令模式、责任链模式、访问者模式、状态模式、模板方法模式、增强策略模式

## 项目结构

```
.
├── advanced-concurrency/          # 高级并发编程演示
├── advanced-design-patterns/      # 高级设计模式演示
├── cpp20-23/                      # C++20/23新特性演示
├── design-patterns/               # 设计模式演示
│   ├── decorator/
│   ├── factory/
│   ├── observer/
│   ├── singleton/
│   └── strategy/
├── exception-handling/            # 异常处理演示
├── filesystem/                    # 文件系统操作演示
├── function-comparison/           # 函数比较演示
├── interop/                       # 与其他语言互操作演示
├── memory-arena/                  # 内存池演示
├── memory-leak-detection/         # 内存泄漏检测演示
├── modern-cpp-features/           # 现代C++特性演示
├── move-semantics/                # 移动语义演示
├── multithreading/                # 多线程编程演示
├── network/                       # 网络编程演示
├── performance-benchmarking/      # 性能分析和基准测试演示
├── smart-pointers/                # 智能指针演示
│   ├── circular_reference/
│   ├── shared_ptr/
│   ├── unique_ptr/
│   └── weak_ptr/
├── stl-algorithms/                # STL算法演示
├── stl-containers/                # STL容器演示
├── tests/                         # 单元测试
├── utils/                         # 工具函数
├── CMakeLists.txt                 # CMake构建配置
├── main.cpp                       # 主程序入口
└── README.md                      # 项目说明文档
```

## 依赖项

- C++20兼容的编译器（如GCC 10+、Clang 10+、MSVC 2019+）
- CMake 3.30+
- Google Test（用于单元测试）
- POSIX线程库（Linux/macOS）或Windows线程库

### 安装依赖项

#### macOS

```bash
# 安装Homebrew（如果尚未安装）
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# 安装依赖项
brew install cmake googletest
```

#### Ubuntu/Debian

```bash
# 更新包列表
sudo apt update

# 安装依赖项
sudo apt install cmake libgtest-dev build-essential

# 构建Google Test
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp lib/*.a /usr/lib
```

#### Windows

1. 安装Visual Studio（包含C++工具）
2. 安装CMake
3. 安装Google Test（可以通过vcpkg安装）

## 构建和运行

### 使用CMake构建

```bash
# 创建构建目录
mkdir build
cd build

# 配置项目（根据你的系统调整路径）
# macOS:
cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew/Cellar/googletest/1.14.0

# Ubuntu/Debian:
cmake ..

# 构建项目
make

# 运行主程序
./cpp_learning_demo
```

### 使用编译器直接编译

```bash
# 使用g++编译（需要支持C++20）
g++ main.cpp -std=c++20 -lpthread -o cpp_learning_demo

# 使用clang++编译
clang++ main.cpp -std=c++20 -lpthread -o cpp_learning_demo

# 运行程序
./cpp_learning_demo
```

## 功能演示

### 元编程

元编程是C++的一个强大特性，允许在编译时进行计算和类型操作。

- **类型特征**：编译时类型检查和转换
- **模板特化**：为特定类型提供特殊实现
- **SFINAE**：替换失败不是错误原则的应用
- **constexpr**：编译时常量表达式
- **可变参数模板**：处理可变数量的模板参数
- **类型introspection**：在编译时检查类型信息
- **CRTP**：奇异递归模板模式

### 智能指针

智能指针是现代C++中管理动态内存的推荐方式。

- **unique_ptr**：独占所有权的智能指针
- **shared_ptr**：共享所有权的智能指针
- **weak_ptr**：解决循环引用问题的智能指针
- **循环引用处理**：使用weak_ptr避免shared_ptr的循环引用

### STL容器和算法

STL提供了丰富的容器和算法，是C++标准库的核心部分。

- **序列容器**：vector、array、deque、list、forward_list
- **关联容器**：set、map、multiset、multimap
- **无序关联容器**：unordered_set、unordered_map、unordered_multiset、unordered_multimap
- **STL算法**：非修改性序列算法、修改性序列算法、排序算法、数值算法、集合算法

### 移动语义

移动语义是C++11引入的重要特性，可以显著提高性能。

- **右值引用**：区分左值和右值
- **移动构造函数**：避免不必要的拷贝
- **完美转发**：保持参数的值类别
- **移动迭代器**：将拷贝操作转换为移动操作

### 异常处理

异常处理是C++中处理错误的重要机制。

- **基本异常处理**：try、catch、throw的使用
- **异常安全**：强异常安全保证、无异常安全保证
- **函数try块**：在构造函数中处理异常
- **noexcept**：指定函数不抛出异常

### 多线程编程

多线程编程是现代C++的重要组成部分。

- **基本线程操作**：创建和管理线程
- **互斥锁和条件变量**：同步线程访问共享资源
- **原子操作**：无锁编程的基础
- **异步操作和future**：异步执行任务
- **共享互斥锁**：读写锁的实现

### 设计模式

设计模式是解决常见软件设计问题的经典方案。

- **单例模式**：确保类只有一个实例
- **观察者模式**：定义对象间的一对多依赖关系
- **策略模式**：定义一系列算法，使它们可以互换
- **装饰器模式**：动态地给对象添加新功能
- **工厂模式**：创建对象而不暴露创建逻辑

### 现代C++特性

现代C++（C++11到C++20）引入了许多新特性。

- **auto类型推导**：让编译器推导变量类型
- **范围for循环**：简化容器遍历
- **Lambda表达式**：定义匿名函数
- **std::optional**：表示可能存在或不存在的值
- **std::variant**：类型安全的union
- **std::any**：存储任何类型的值
- **结构化绑定**：解构tuple、pair和struct
- **if constexpr**：编译时条件判断
- **折叠表达式**：处理可变参数模板参数包
- **Concepts**：约束模板参数
- **Ranges**：更直观的范围操作
- **std::format**：类型安全的格式化

### 性能分析和基准测试

性能分析和基准测试是优化程序性能的重要工具。

- **高精度计时器**：测量代码执行时间
- **函数性能比较**：比较不同实现的性能
- **自定义基准测试**：创建专门的性能测试

### 文件系统操作

C++17引入了文件系统库，简化了文件和目录操作。

- **目录操作**：创建、删除、遍历目录
- **文件操作**：创建、读取、写入、复制、移动文件
- **路径操作**：处理文件路径
- **空间信息**：获取磁盘空间信息

### 网络编程

网络编程是现代应用程序的重要组成部分。

- **TCP客户端/服务器**：基本的网络通信
- **HTTP客户端**：发送HTTP请求
- **URL解析**：解析和处理URL

### 内存管理

有效的内存管理是高性能程序的关键。

- **内存池**：预分配内存块以提高分配效率
- **自定义分配器**：为特定需求定制内存分配策略
- **内存泄漏检测**：检测和防止内存泄漏

### 与其他语言的互操作性

C++可以与其他语言互操作。

- **C语言互操作**：调用C函数和使用C结构体
- **Python互操作概念**：使用pybind11将C++代码暴露给Python
- **JavaScript互操作概念**：使用Emscripten将C++编译为WebAssembly
- **Rust互操作概念**：通过C接口与Rust代码互操作

### 高级并发编程

高级并发编程技术可以进一步提高程序性能。

- **线程池**：管理线程资源
- **无锁数据结构**：避免锁开销的并发数据结构
- **并发哈希表**：线程安全的哈希表实现
- **原子操作高级用法**：高级原子操作技术
- **异步编程高级用法**：packaged_task、promise等高级异步编程技术
- **线程局部存储**：每个线程独立的存储空间

### 高级设计模式

除了基本设计模式，还有更多高级设计模式。

- **命令模式**：将请求封装为对象
- **责任链模式**：为请求创建处理对象链
- **访问者模式**：在不修改元素类的情况下定义新操作
- **状态模式**：允许对象在其内部状态改变时改变其行为
- **模板方法模式**：定义算法骨架，子类可以重写特定步骤
- **增强策略模式**：更灵活的策略模式实现

## 设计模式详解

### 创建型模式

1. **工厂模式**
   - 简单工厂：一个工厂类创建多种产品
   - 工厂方法：定义创建对象的接口，由子类决定实例化哪个类
   - 抽象工厂：提供一个创建一系列相关或相互依赖对象的接口

2. **单例模式**
   - 确保一个类只有一个实例，并提供一个全局访问点

### 结构型模式

1. **装饰器模式**
   - 动态地给一个对象添加一些额外的职责

2. **适配器模式**（在本项目中未实现，但可以添加）
   - 将一个类的接口转换成客户希望的另一个接口

### 行为型模式

1. **观察者模式**
   - 定义对象间的一种一对多的依赖关系

2. **策略模式**
   - 定义一系列算法，把它们一个个封装起来，并且使它们可相互替换

3. **命令模式**
   - 将一个请求封装为一个对象

4. **责任链模式**
   - 为解除请求的发送者和接收者之间的耦合

5. **访问者模式**
   - 表示一个作用于某对象结构中的各元素的操作

6. **状态模式**
   - 允许一个对象在其内部状态改变时改变它的行为

7. **模板方法模式**
   - 定义一个操作中的算法骨架，而将一些步骤延迟到子类中

## 测试

本项目使用Google Test框架进行单元测试。

### 构建和运行测试

```bash
# 构建项目（包括测试）
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew/Cellar/googletest/1.14.0  # macOS
make

# 运行测试
./tests/cpp_learning_demo_tests

# 或者使用ctest（需要在tests目录中运行）
cd tests
ctest
```

### 测试内容

当前测试包括：

1. **向量工具函数测试**
   - 向量求和函数
   - 向量平均值函数
   - 查找最大值函数
   - 查找最小值函数

### 添加新测试

要添加新测试，请在`tests/`目录中创建新的测试文件，并在`tests/CMakeLists.txt`中添加相应的配置。

## 贡献

欢迎对本项目做出贡献！请遵循以下步骤：

1. Fork本项目
2. 创建你的特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交你的更改 (`git commit -m 'Add some amazing feature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启一个Pull Request

## 许可证

本项目采用MIT许可证。详情请见[LICENSE](LICENSE)文件。

---

**注意**：本项目主要用于学习和演示目的。在生产环境中使用时，请根据具体需求进行适当的修改和优化。