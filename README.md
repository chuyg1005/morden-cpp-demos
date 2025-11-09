# C++ 全面学习项目

这个项目涵盖了C++的各个方面，从基础到高级特性。

## 构建和运行

### 构建项目

```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=/opt/homebrew/Cellar/googletest/1.14.0
make
```

### 运行主程序

```bash
./cpp_learning_demo
```

### 运行测试

```bash
# 方法1：直接运行测试可执行文件
./tests/cpp_learning_demo_tests

# 方法2：使用ctest（需要在tests目录中运行）
cd tests
ctest
```

## 项目结构

- `main.cpp` - 主程序入口
- 各个子目录包含特定主题的演示代码
- `tests/` - 单元测试代码

## 依赖

- C++20兼容的编译器
- Google Test (用于单元测试)
- CMake 3.30+

## 主要特性演示

1. 元编程
2. 智能指针
3. STL容器和算法
4. 移动语义
5. 异常处理
6. 多线程编程
7. 设计模式
8. 现代C++特性（C++11到C++20）
9. 性能分析和基准测试
10. 文件系统操作
11. 网络编程概念
12. 内存管理
13. 与其他语言的互操作性
14. 高级并发编程
15. 高级设计模式