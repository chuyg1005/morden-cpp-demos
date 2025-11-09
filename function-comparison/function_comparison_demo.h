#ifndef FUNCTION_COMPARISON_DEMO_H
#define FUNCTION_COMPARISON_DEMO_H

#include <iostream>
#include <functional>
#include <chrono>
#include <vector>

// 演示函数指针、std::function和lambda表达式的比较
namespace function_comparison_demo {
    // 普通函数
    int add(int a, int b) {
        return a + b;
    }

    // 函数对象/仿函数
    struct AddFunctor {
        int operator()(int a, int b) const {
            return a + b;
        }
    };

    // 性能测试辅助函数
    template<typename Func>
    long long measure_time(Func func, int iterations) {
        auto start = std::chrono::high_resolution_clock::now();
        [[maybe_unused]] int result = 0;  // Prevent optimization without using volatile
        for (int i = 0; i < iterations; ++i) {
            result = func(i, i + 1);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        return duration.count();
    }

    // 演示函数指针、std::function和lambda的使用和性能比较
    void function_comparison_demo() {
        std::cout << "\n=== 函数指针、std::function和Lambda表达式比较 ===" << std::endl;

        const int iterations = 1000000;

        // 1. 函数指针
        std::cout << "\n1. 函数指针:" << std::endl;
        int (*func_ptr)(int, int) = add;
        auto ptr_time = measure_time(func_ptr, iterations);
        std::cout << "函数指针结果示例: " << func_ptr(5, 3) << std::endl;
        std::cout << "函数指针性能 (" << iterations << " 次调用): " << ptr_time << " 纳秒" << std::endl;

        // 2. 函数对象
        std::cout << "\n2. 函数对象(仿函数):" << std::endl;
        AddFunctor functor;
        auto functor_time = measure_time(functor, iterations);
        std::cout << "函数对象结果示例: " << functor(5, 3) << std::endl;
        std::cout << "函数对象性能 (" << iterations << " 次调用): " << functor_time << " 纳秒" << std::endl;

        // 3. Lambda表达式
        std::cout << "\n3. Lambda表达式:" << std::endl;
        auto lambda = [](int a, int b) -> int { return a + b; };
        auto lambda_time = measure_time(lambda, iterations);
        std::cout << "Lambda结果示例: " << lambda(5, 3) << std::endl;
        std::cout << "Lambda性能 (" << iterations << " 次调用): " << lambda_time << " 纳秒" << std::endl;

        // 4. std::function
        std::cout << "\n4. std::function:" << std::endl;
        std::function<int(int, int)> std_func = add;
        auto std_func_time = measure_time(std_func, iterations);
        std::cout << "std::function结果示例: " << std_func(5, 3) << std::endl;
        std::cout << "std::function性能 (" << iterations << " 次调用): " << std_func_time << " 纳秒" << std::endl;

        // 5. std::function with lambda
        std::cout << "\n5. std::function包装Lambda:" << std::endl;
        std::function<int(int, int)> std_lambda = [](int a, int b) -> int { return a + b; };
        auto std_lambda_time = measure_time(std_lambda, iterations);
        std::cout << "std::function+Lambda结果示例: " << std_lambda(5, 3) << std::endl;
        std::cout << "std::function+Lambda性能 (" << iterations << " 次调用): " << std_lambda_time << " 纳秒" << std::endl;

        // 6. 使用场景示例
        std::cout << "\n6. 使用场景示例:" << std::endl;
        
        // 函数指针 - 适合简单的函数调用，性能最好
        std::cout << "函数指针适合简单的函数调用，性能最好" << std::endl;
        
        // Lambda - 适合简短的匿名函数，可捕获局部变量
        int multiplier = 10;
        auto multiply_lambda = [multiplier](int x) { return x * multiplier; };
        std::cout << "Lambda可捕获局部变量，示例: 5 * " << multiplier << " = " << multiply_lambda(5) << std::endl;
        
        // std::function - 适合需要存储不同类型可调用对象的场景
        std::vector<std::function<int(int, int)>> functions;
        functions.push_back(add);  // 普通函数
        functions.push_back(functor);  // 函数对象
        functions.push_back(lambda);  // Lambda
        functions.push_back([](int a, int b) { return a * b; });  // 内联Lambda
        
        std::cout << "std::function可存储不同类型的可调用对象:" << std::endl;
        for (size_t i = 0; i < functions.size(); ++i) {
            std::cout << "  函数 " << i << " 结果 (5,3): " << functions[i](5, 3) << std::endl;
        }
        
        // 性能总结
        std::cout << "\n性能总结 (数值越小性能越好):" << std::endl;
        std::cout << "  函数指针: " << ptr_time << " 纳秒" << std::endl;
        std::cout << "  函数对象: " << functor_time << " 纳秒" << std::endl;
        std::cout << "  Lambda: " << lambda_time << " 纳秒" << std::endl;
        std::cout << "  std::function: " << std_func_time << " 纳秒" << std::endl;
        std::cout << "  std::function+Lambda: " << std_lambda_time << " 纳秒" << std::endl;
    }
}

#endif // FUNCTION_COMPARISON_DEMO_H