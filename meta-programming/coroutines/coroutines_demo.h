#ifndef CPP_LEARNING_DEMO_COROUTINES_DEMO_H
#define CPP_LEARNING_DEMO_COROUTINES_DEMO_H

#include <iostream>
#include <coroutine>
#include <chrono>
#include <thread>
#include <future>
#include <vector>

#include "coroutines_base.h"

namespace coroutines_demo {
    using namespace coroutines_base;
    
    // Generator example: Fibonacci sequence
    Generator<int> fibonacci_sequence(int n) {
        if (n <= 0) co_return;
        
        int a = 0, b = 1;
        co_yield a;
        if (n == 1) co_return;
        
        co_yield b;
        for (int i = 2; i < n; ++i) {
            int next = a + b;
            co_yield next;
            a = b;
            b = next;
        }
    }
    
    // Task example: Simple async computation
    Task<int> async_computation(int x) {
        // Simulate some work with a simple loop
        for (int i = 0; i < 1000000; ++i) {
            // Busy wait to simulate work
        }
        co_return x * x;
    }
    
    // Generator example: Range of integers
    Generator<int> range(int start, int end) {
        for (int i = start; i < end; ++i) {
            co_yield i;
        }
    }
    
    // Task example: Async addition
    Task<int> async_add(int a, int b) {
        // Simulate async work with a simple loop
        for (int i = 0; i < 500000; ++i) {
            // Busy wait to simulate work
        }
        co_return a + b;
    }
    
    // Demonstrate generator usage
    void generator_demo() {
        std::cout << "\\n=== Generator演示 ===" << std::endl;
        std::cout << "斐波那契数列前10项: ";
        for (int value : fibonacci_sequence(10)) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        
        std::cout << "范围[1, 6)的整数: ";
        for (int value : range(1, 6)) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    
    // Demonstrate task usage
    void task_demo() {
        std::cout << "\\n=== Task演示 ===" << std::endl;
        
        // Simple async computation
        auto task1 = async_computation(5);
        std::cout << "5的平方: " << task1.get() << std::endl;
        
        // Async addition
        auto task2 = async_add(10, 20);
        std::cout << "10 + 20 = " << task2.get() << std::endl;
    }
    
    // Demonstrate concurrent tasks
    void concurrent_tasks_demo() {
        std::cout << "\n=== 并发任务演示 ===" << std::endl;
        
        // Launch and collect results immediately to avoid storing Tasks in a vector
        std::cout << "并发计算平方: ";
        for (int i = 1; i <= 5; ++i) {
            auto task = async_computation(i);
            std::cout << task.get() << " ";
        }
        std::cout << std::endl;
    }
    
    // Run all coroutine demos
    void run_demo() {
        std::cout << "=== C++协程演示 ===" << std::endl;
        generator_demo();
        task_demo();
        concurrent_tasks_demo();
    }
}

#endif //CPP_LEARNING_DEMO_COROUTINES_DEMO_H