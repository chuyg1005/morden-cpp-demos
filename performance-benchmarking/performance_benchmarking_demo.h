#ifndef CPP_LEARNING_DEMO_PERFORMANCE_BENCHMARKING_DEMO_H
#define CPP_LEARNING_DEMO_PERFORMANCE_BENCHMARKING_DEMO_H

#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <iomanip>

namespace performance_benchmarking_demo {
    // 高精度计时器类
    class Timer {
    private:
        std::chrono::high_resolution_clock::time_point start_time;
        std::string name;
        bool running;

    public:
        explicit Timer(const std::string& timer_name = "Timer") 
            : name(timer_name), running(false) {
            start();
        }

        void start() {
            start_time = std::chrono::high_resolution_clock::now();
            running = true;
        }

        double stop() {
            if (!running) return 0.0;
            
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
            running = false;
            return duration.count() / 1e9; // 转换为秒
        }

        void stop_and_print() {
            double elapsed = stop();
            std::cout << name << " took: " << std::fixed << std::setprecision(6) 
                      << elapsed << " seconds" << std::endl;
        }
    };

    // 基准测试函数
    template<typename Func, typename... Args>
    double benchmark_function(int iterations, Func&& func, Args&&... args) {
        // 预热
        for (int i = 0; i < 1000; ++i) {
            func(args...);
        }

        Timer timer("Benchmark");
        for (int i = 0; i < iterations; ++i) {
            func(args...);
        }
        return timer.stop() / iterations; // 返回平均时间
    }

    // 简单的性能比较函数
    template<typename Func1, typename Func2, typename... Args>
    void compare_functions(const std::string& name1, Func1&& func1, 
                          const std::string& name2, Func2&& func2, 
                          Args&&... args) {
        const int iterations = 100000;
        
        double time1 = benchmark_function(iterations, func1, args...);
        double time2 = benchmark_function(iterations, func2, args...);
        
        std::cout << "Performance comparison:" << std::endl;
        std::cout << name1 << ": " << std::fixed << std::setprecision(9) << time1 << " seconds per call" << std::endl;
        std::cout << name2 << ": " << std::fixed << std::setprecision(9) << time2 << " seconds per call" << std::endl;
        std::cout << "Ratio (" << name1 << "/" << name2 << "): " << time1 / time2 << std::endl;
    }

    // 示例函数1: 向量操作
    void vector_push_back_test(int size) {
        std::vector<int> v;
        for (int i = 0; i < size; ++i) {
            v.push_back(i);
        }
    }

    // 示例函数2: 预分配向量操作
    void vector_reserve_test(int size) {
        std::vector<int> v;
        v.reserve(size);
        for (int i = 0; i < size; ++i) {
            v.push_back(i);
        }
    }

    // 运行演示
    void run_demo() {
        std::cout << "=== 性能分析和基准测试演示 ===" << std::endl;
        
        // 基本计时器使用
        {
            Timer t("Vector creation");
            std::vector<int> v(1000000, 42);
        }
        
        // 函数性能比较
        std::cout << "\n比较vector操作性能:" << std::endl;
        compare_functions(
            "push_back without reserve", vector_push_back_test,
            "push_back with reserve", vector_reserve_test,
            10000
        );
        
        // 自定义基准测试
        std::cout << "\n自定义基准测试:" << std::endl;
        const int iterations = 100000;
        auto lambda_test = []() {
            volatile int x = 0;
            for (int i = 0; i < 100; ++i) {
                x += i;
            }
        };
        
        double avg_time = benchmark_function(iterations, lambda_test);
        std::cout << "Lambda test average time: " << std::fixed << std::setprecision(9) 
                  << avg_time << " seconds per call" << std::endl;
    }
}

#endif //CPP_LEARNING_DEMO_PERFORMANCE_BENCHMARKING_DEMO_H