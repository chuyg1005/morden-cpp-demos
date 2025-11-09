#ifndef CPP_LEARNING_DEMO_MODERN_CPP_FEATURES_DEMO_H
#define CPP_LEARNING_DEMO_MODERN_CPP_FEATURES_DEMO_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <variant>
#include <any>
#include <memory>
#include <chrono>
#include <thread>
#include <filesystem>
#include <concepts>
#include <ranges>
#include <format>

namespace modern_cpp_features_demo {
    // auto类型推导演示
    void auto_type_deduction_demo() {
        std::cout << "\n=== auto类型推导演示 ===" << std::endl;
        auto i = 42;           // int
        auto d = 3.14;         // double
        auto s = "hello";      // const char*
        auto v = std::vector<int>{1, 2, 3};  // std::vector<int>
        
        std::cout << "i = " << i << " (type: int)" << std::endl;
        std::cout << "d = " << d << " (type: double)" << std::endl;
        std::cout << "s = " << s << " (type: const char*)" << std::endl;
        std::cout << "v = {";
        for (const auto& elem : v) {
            std::cout << elem << " ";
        }
        std::cout << "} (type: std::vector<int>)" << std::endl;
    }

    // 范围for循环演示
    void range_based_for_loop_demo() {
        std::cout << "\n=== 范围for循环演示 ===" << std::endl;
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        
        // 基本用法
        std::cout << "Numbers: ";
        for (const auto& num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        
        // 修改元素
        std::cout << "Doubled numbers: ";
        for (auto& num : numbers) {
            num *= 2;
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    // Lambda表达式演示
    void lambda_expressions_demo() {
        std::cout << "\n=== Lambda表达式演示 ===" << std::endl;
        
        // 基本lambda
        auto add = [](int a, int b) { return a + b; };
        std::cout << "5 + 3 = " << add(5, 3) << std::endl;
        
        // 捕获变量
        int multiplier = 10;
        auto multiply = [multiplier](int x) { return x * multiplier; };
        std::cout << "5 * 10 = " << multiply(5) << std::endl;
        
        // 引用捕获
        int value = 100;
        auto modify_value = [&value]() { value += 10; };
        modify_value();
        std::cout << "Modified value: " << value << std::endl;
        
        // 通用捕获(C++14)
        auto factory = [value = 42]() { return value * 2; };
        std::cout << "Factory result: " << factory() << std::endl;
    }

    // std::optional演示
    void optional_demo() {
        std::cout << "\n=== std::optional演示 ===" << std::endl;
        
        std::optional<int> opt1;  // 空的optional
        std::optional<int> opt2 = 42;  // 包含值的optional
        
        std::cout << "opt1 has value: " << opt1.has_value() << std::endl;
        std::cout << "opt2 has value: " << opt2.has_value() << std::endl;
        std::cout << "opt2 value: " << opt2.value() << std::endl;
        
        // 安全访问
        if (opt1) {
            std::cout << "opt1 value: " << *opt1 << std::endl;
        } else {
            std::cout << "opt1 is empty" << std::endl;
        }
        
        // 使用默认值
        std::cout << "opt1 value or default: " << opt1.value_or(-1) << std::endl;
    }

    // std::variant演示
    void variant_demo() {
        std::cout << "\n=== std::variant演示 ===" << std::endl;
        
        std::variant<int, std::string, double> var;
        
        var = 42;
        std::cout << "Variant holds int: " << std::get<int>(var) << std::endl;
        
        var = "Hello";
        std::cout << "Variant holds string: " << std::get<std::string>(var) << std::endl;
        
        var = 3.14;
        std::cout << "Variant holds double: " << std::get<double>(var) << std::endl;
        
        // 类型安全访问
        try {
            std::cout << "Trying to get int from double variant: ";
            std::cout << std::get<int>(var) << std::endl;
        } catch (const std::bad_variant_access& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
        // 使用visit访问
        std::visit([](const auto& value) {
            std::cout << "Visited value: " << value << " (type: " << typeid(value).name() << ")" << std::endl;
        }, var);
    }

    // std::any演示
    void any_demo() {
        std::cout << "\n=== std::any演示 ===" << std::endl;
        
        std::any value;
        
        value = 42;
        std::cout << "Any holds int: " << std::any_cast<int>(value) << std::endl;
        
        value = std::string("Hello");
        std::cout << "Any holds string: " << std::any_cast<std::string>(value) << std::endl;
        
        value = 3.14;
        std::cout << "Any holds double: " << std::any_cast<double>(value) << std::endl;
        
        // 类型检查
        std::cout << "Type of value: " << value.type().name() << std::endl;
        
        // 安全转换
        try {
            int i = std::any_cast<int>(value);
            std::cout << "Any cast to int: " << i << std::endl;
        } catch (const std::bad_any_cast& e) {
            std::cout << "Cannot cast to int: " << e.what() << std::endl;
        }
    }

    // 结构化绑定演示
    void structured_bindings_demo() {
        std::cout << "\n=== 结构化绑定演示 ===" << std::endl;
        
        // 与pair/tuple一起使用
        std::pair<int, std::string> p{1, "hello"};
        auto [id, name] = p;
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
        
        // 与数组一起使用
        std::array<int, 3> arr{1, 2, 3};
        auto [a, b, c] = arr;
        std::cout << "Array elements: " << a << ", " << b << ", " << c << std::endl;
        
        // 与结构体一起使用
        struct Point {
            int x, y;
        };
        Point pt{10, 20};
        auto [x, y] = pt;
        std::cout << "Point: (" << x << ", " << y << ")" << std::endl;
    }

    // if constexpr演示
    template<typename T>
    void if_constexpr_demo_helper(T value) {
        if constexpr (std::is_integral_v<T>) {
            std::cout << "Integral value: " << value << std::endl;
        } else if constexpr (std::is_floating_point_v<T>) {
            std::cout << "Floating point value: " << value << std::endl;
        } else {
            std::cout << "Other type value: " << value << std::endl;
        }
    }

    void if_constexpr_demo() {
        std::cout << "\n=== if constexpr演示 ===" << std::endl;
        if_constexpr_demo_helper(42);
        if_constexpr_demo_helper(3.14);
        if_constexpr_demo_helper(std::string("Hello"));
    }

    // 折叠表达式演示
    template<typename... Args>
    auto sum(Args... args) {
        return (args + ...);
    }

    template<typename... Args>
    void print_all(Args... args) {
        ((std::cout << args << " "), ...);
        std::cout << std::endl;
    }

    void fold_expressions_demo() {
        std::cout << "\n=== 折叠表达式演示 ===" << std::endl;
        std::cout << "Sum of 1, 2, 3, 4, 5: " << sum(1, 2, 3, 4, 5) << std::endl;
        std::cout << "Print all: ";
        print_all(1, "hello", 3.14, 'x');
    }

    // Concepts演示 (C++20)
    template<typename T>
    concept Numeric = std::is_arithmetic_v<T>;

    template<Numeric T>
    T multiply(T a, T b) {
        return a * b;
    }

    void concepts_demo() {
        std::cout << "\n=== Concepts演示 ===" << std::endl;
        std::cout << "Multiply 3 * 4 = " << multiply(3, 4) << std::endl;
        std::cout << "Multiply 2.5 * 3.5 = " << multiply(2.5, 3.5) << std::endl;
    }

    // Ranges演示 (C++20)
    void ranges_demo() {
        std::cout << "\n=== Ranges演示 ===" << std::endl;
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // 使用范围算法
        auto even_numbers = numbers | std::views::filter([](int n) { return n % 2 == 0; });
        std::cout << "Even numbers: ";
        for (const auto& n : even_numbers) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
        
        // 转换和过滤
        auto squared_evens = numbers 
            | std::views::filter([](int n) { return n % 2 == 0; })
            | std::views::transform([](int n) { return n * n; });
        std::cout << "Squared even numbers: ";
        for (const auto& n : squared_evens) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
    }

    // std::format演示 (C++20)
    void format_demo() {
        std::cout << "\n=== std::format演示 ===" << std::endl;
        std::string name = "Alice";
        int age = 30;
        double height = 5.6;
        
        // 注意：std::format在某些编译器中可能不可用，这里提供替代方案
        std::cout << "Name: " << name << ", Age: " << age << ", Height: " << height << std::endl;
        
        // 如果支持std::format，可以使用以下代码：
        // std::cout << std::format("Name: {}, Age: {}, Height: {:.1f}", name, age, height) << std::endl;
    }

    // 运行所有演示
    void run_all_demos() {
        std::cout << "=== 现代C++特性演示 ===" << std::endl;
        auto_type_deduction_demo();
        range_based_for_loop_demo();
        lambda_expressions_demo();
        optional_demo();
        variant_demo();
        any_demo();
        structured_bindings_demo();
        if_constexpr_demo();
        fold_expressions_demo();
        concepts_demo();
        ranges_demo();
        format_demo();
    }
}

#endif //CPP_LEARNING_DEMO_MODERN_CPP_FEATURES_DEMO_H