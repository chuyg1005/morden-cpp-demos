#ifndef MODERN_CPP_FEATURES_DEMO_H
#define MODERN_CPP_FEATURES_DEMO_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <optional>
#include <variant>
#include <any>
#include <filesystem>
#include <thread>

// 演示现代C++特性
namespace modern_cpp_features_demo {
    // 1. auto关键字和类型推导
    void auto_type_deduction_demo() {
        std::cout << "\n=== auto关键字和类型推导演示 ===" << std::endl;
        
        auto i = 42;                    // int
        auto d = 3.14;                  // double
        auto s = "Hello";               // const char*
        auto v = std::vector<int>{1, 2, 3};  // std::vector<int>
        
        std::cout << "i类型: " << typeid(i).name() << ", 值: " << i << std::endl;
        std::cout << "d类型: " << typeid(d).name() << ", 值: " << d << std::endl;
        std::cout << "s类型: " << typeid(s).name() << ", 值: " << s << std::endl;
        std::cout << "v大小: " << v.size() << std::endl;
    }

    // 2. 范围for循环
    void range_based_for_loop_demo() {
        std::cout << "\n=== 范围for循环演示 ===" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5};
        
        // 值拷贝
        std::cout << "值拷贝: ";
        for (const auto& item : vec) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // 引用修改
        std::cout << "引用修改前: ";
        for (const auto& item : vec) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        for (auto& item : vec) {
            item *= 2;
        }
        
        std::cout << "引用修改后: ";
        for (const auto& item : vec) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    // 3. Lambda表达式
    void lambda_expressions_demo() {
        std::cout << "\n=== Lambda表达式演示 ===" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5};
        
        // 基本lambda
        auto square = [](int x) { return x * x; };
        std::cout << "5的平方: " << square(5) << std::endl;
        
        // 带捕获的lambda
        int multiplier = 10;
        auto multiply = [multiplier](int x) { return x * multiplier; };
        std::cout << "5乘以" << multiplier << ": " << multiply(5) << std::endl;
        
        // 引用捕获
        auto multiply_ref = [&multiplier](int x) { return x * multiplier; };
        multiplier = 20;
        std::cout << "5乘以" << multiplier << ": " << multiply_ref(5) << std::endl;
        
        // 使用STL算法
        std::cout << "偶数: ";
        std::for_each(vec.begin(), vec.end(), [](int x) {
            if (x % 2 == 0) {
                std::cout << x << " ";
            }
        });
        std::cout << std::endl;
    }

    // 4. std::optional
    std::optional<int> divide(int a, int b) {
        if (b == 0) {
            return std::nullopt;
        }
        return a / b;
    }

    void optional_demo() {
        std::cout << "\n=== std::optional演示 ===" << std::endl;
        
        auto result1 = divide(10, 2);
        if (result1) {
            std::cout << "10 / 2 = " << *result1 << std::endl;
        }
        
        auto result2 = divide(10, 0);
        if (result2) {
            std::cout << "10 / 0 = " << *result2 << std::endl;
        } else {
            std::cout << "除零错误" << std::endl;
        }
        
        // 使用value_or提供默认值
        std::cout << "安全除法结果: " << result2.value_or(-1) << std::endl;
    }

    // 5. std::variant
    void variant_demo() {
        std::cout << "\n=== std::variant演示 ===" << std::endl;
        
        std::variant<int, std::string, double> var;
        
        // 存储整数
        var = 42;
        std::cout << "当前值(整数): " << std::get<int>(var) << std::endl;
        
        // 存储字符串
        var = std::string("Hello");
        std::cout << "当前值(字符串): " << std::get<std::string>(var) << std::endl;
        
        // 存储浮点数
        var = 3.14;
        std::cout << "当前值(浮点数): " << std::get<double>(var) << std::endl;
        
        // 使用visit处理variant
        std::visit([](const auto& value) {
            std::cout << "访问值: " << value << std::endl;
        }, var);
    }

    // 6. std::any
    void any_demo() {
        std::cout << "\n=== std::any演示 ===" << std::endl;
        
        std::any value;
        
        // 存储整数
        value = 42;
        if (value.type() == typeid(int)) {
            std::cout << "整数值: " << std::any_cast<int>(value) << std::endl;
        }
        
        // 存储字符串
        value = std::string("Hello");
        if (value.type() == typeid(std::string)) {
            std::cout << "字符串值: " << std::any_cast<std::string>(value) << std::endl;
        }
        
        // 存储向量
        value = std::vector<int>{1, 2, 3};
        if (value.type() == typeid(std::vector<int>)) {
            auto vec = std::any_cast<std::vector<int>>(value);
            std::cout << "向量值: ";
            for (const auto& item : vec) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
    }

    // 7. 结构化绑定
    std::pair<std::string, int> getPerson() {
        return {"张三", 25};
    }

    std::tuple<std::string, int, double> getStudent() {
        return {"李四", 20, 85.5};
    }

    void structured_bindings_demo() {
        std::cout << "\n=== 结构化绑定演示 ===" << std::endl;
        
        // 绑定pair
        auto [name, age] = getPerson();
        std::cout << "姓名: " << name << ", 年龄: " << age << std::endl;
        
        // 绑定tuple
        auto [studentName, studentAge, score] = getStudent();
        std::cout << "学生姓名: " << studentName << ", 年龄: " << studentAge 
                  << ", 分数: " << score << std::endl;
        
        // 绑定数组
        int arr[] = {1, 2, 3};
        auto [a, b, c] = arr;
        std::cout << "数组元素: " << a << ", " << b << ", " << c << std::endl;
    }

    // 8. if constexpr (C++17)
    template<typename T>
    void print_type_info() {
        std::cout << "类型信息: ";
        if constexpr (std::is_integral_v<T>) {
            std::cout << "整数类型" << std::endl;
        } else if constexpr (std::is_floating_point_v<T>) {
            std::cout << "浮点类型" << std::endl;
        } else {
            std::cout << "其他类型" << std::endl;
        }
    }

    void if_constexpr_demo() {
        std::cout << "\n=== if constexpr演示 ===" << std::endl;
        
        print_type_info<int>();
        print_type_info<double>();
        print_type_info<std::string>();
    }

    // 9. 折叠表达式 (C++17)
    template<typename... Args>
    auto sum(Args... args) {
        return (args + ...);  // 右折叠
    }

    template<typename... Args>
    void print_all(Args... args) {
        (std::cout << ... << args) << std::endl;  // 折叠表达式用于输出
    }

    void fold_expressions_demo() {
        std::cout << "\n=== 折叠表达式演示 ===" << std::endl;
        
        std::cout << "求和结果: " << sum(1, 2, 3, 4, 5) << std::endl;
        std::cout << "连接字符串: ";
        print_all("Hello", " ", "World", "!");
    }
}

#endif // MODERN_CPP_FEATURES_DEMO_H