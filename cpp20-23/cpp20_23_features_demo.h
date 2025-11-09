#ifndef CPP_LEARNING_DEMO_CPP20_23_FEATURES_DEMO_H
#define CPP_LEARNING_DEMO_CPP20_23_FEATURES_DEMO_H

#include <iostream>
#include <vector>
#include <string>
#include <concepts>
#include <ranges>
#include <format>
#include <span>
#include <bit>
#include <numbers>
#include <chrono>

// 注意：某些C++23特性可能在当前编译器版本中不可用

namespace cpp20_23_features_demo {
    // Concepts演示
    template<typename T>
    concept Number = std::is_arithmetic_v<T>;
    
    template<typename T>
    concept Container = requires(T t) {
        t.begin();
        t.end();
        t.size();
    };
    
    template<Number T>
    T add(T a, T b) {
        return a + b;
    }
    
    template<Container C>
    void print_container(const C& container) {
        std::cout << "容器内容: ";
        for (const auto& item : container) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    void concepts_demo() {
        std::cout << "\n=== Concepts演示 ===" << std::endl;
        std::cout << "add(3, 4) = " << add(3, 4) << std::endl;
        std::cout << "add(3.14, 2.86) = " << add(3.14, 2.86) << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5};
        print_container(vec);
    }
    
    // Ranges演示
    void ranges_demo() {
        std::cout << "\n=== Ranges演示 ===" << std::endl;
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // 使用视图过滤和转换
        auto even_squares = numbers 
            | std::views::filter([](int n) { return n % 2 == 0; })
            | std::views::transform([](int n) { return n * n; });
        
        std::cout << "偶数的平方: ";
        for (int n : even_squares) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
        
        // 范围算法
        std::vector<int> data = {5, 2, 8, 1, 9, 3};
        std::ranges::sort(data);
        std::cout << "排序后的数据: ";
        for (int n : data) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }
    
    // Format库演示 (C++20)
    void format_demo() {
        std::cout << "\n=== std::format演示 ===" << std::endl;
        std::string name = "张三";
        int age = 30;
        double height = 175.5;
        
        // 注意：如果编译器不支持std::format，可以使用替代方案
        #if __cplusplus >= 202002L && defined(__cpp_lib_format)
        std::cout << std::format("姓名: {}, 年龄: {}, 身高: {:.1f}cm", name, age, height) << std::endl;
        #else
        // 替代方案
        std::cout << "姓名: " << name << ", 年龄: " << age << ", 身高: " << height << "cm" << std::endl;
        #endif
    }
    
    // Span库演示 (C++20)
    void span_demo() {
        std::cout << "\n=== std::span演示 ===" << std::endl;
        std::vector<int> vec = {1, 2, 3, 4, 5};
        int arr[] = {6, 7, 8, 9, 10};
        
        // 从vector创建span
        std::span<int> vec_span(vec);
        std::cout << "Vector span大小: " << vec_span.size() << std::endl;
        std::cout << "Vector span元素: ";
        for (const auto& item : vec_span) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // 从数组创建span
        std::span<int, 5> arr_span(arr);
        std::cout << "Array span大小: " << arr_span.size() << std::endl;
        std::cout << "Array span元素: ";
        for (const auto& item : arr_span) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    // Bit库演示 (C++20)
    void bit_demo() {
        std::cout << "\n=== Bit操作演示 ===" << std::endl;
        uint8_t value = 0b10101010;
        
        std::cout << "原始值: " << std::bitset<8>(value) << std::endl;
        std::cout << "字节序是否为小端: " << std::endian::native << std::endl;
        
        // 位反转
        uint8_t reversed = std::byteswap(value);
        std::cout << "位反转后: " << std::bitset<8>(reversed) << std::endl;
    }
    
    // Numbers库演示 (C++20)
    void numbers_demo() {
        std::cout << "\n=== 数学常数演示 ===" << std::endl;
        std::cout << "π (pi): " << std::numbers::pi << std::endl;
        std::cout << "e (自然常数): " << std::numbers::e << std::endl;
        std::cout << "log2(e): " << std::numbers::log2e << std::endl;
        std::cout << "log10(e): " << std::numbers::log10e << std::endl;
        std::cout << "sqrt(2): " << std::numbers::sqrt2 << std::endl;
    }
    
    // Coroutine示例 (概念性)
    // 注意：完整的协程实现需要编译器支持和更复杂的代码
    void coroutine_demo() {
        std::cout << "\n=== 协程演示 ===" << std::endl;
        std::cout << "协程是C++20的重要特性，允许函数在执行过程中挂起和恢复。" << std::endl;
        std::cout << "它们特别适用于异步编程和生成器模式。" << std::endl;
        std::cout << "完整实现需要<coroutine>头文件和编译器支持。" << std::endl;
    }
    
    // Modules示例 (概念性)
    // 注意：模块是C++20的重要特性，但需要编译器支持
    void modules_demo() {
        std::cout << "\n=== 模块演示 ===" << std::endl;
        std::cout << "模块是C++20用来替代头文件的特性，提供更好的编译性能和封装。" << std::endl;
        std::cout << "示例声明方式:" << std::endl;
        std::cout << "export module my_module;" << std::endl;
        std::cout << "export void my_function() { }" << std::endl;
        std::cout << "import my_module;" << std::endl;
    }
    
    // C++23特性预览 (概念性)
    void cpp23_preview() {
        std::cout << "\n=== C++23特性预览 ===" << std::endl;
        std::cout << "C++23计划包含以下特性:" << std::endl;
        std::cout << "1. std::print函数 - 更安全的打印函数" << std::endl;
        std::cout << "2. 静态反射 - 编译时检查类型信息" << std::endl;
        std::cout << "3. 执行器 - 更好的异步执行控制" << std::endl;
        std::cout << "4. 字符串格式化增强" << std::endl;
    }
    
    // 运行所有演示
    void run_demo() {
        std::cout << "=== C++20/23新特性演示 ===" << std::endl;
        concepts_demo();
        ranges_demo();
        format_demo();
        span_demo();
        bit_demo();
        numbers_demo();
        coroutine_demo();
        modules_demo();
        cpp23_preview();
    }
}

#endif //CPP_LEARNING_DEMO_CPP20_23_FEATURES_DEMO_H