#ifndef MULTITHREADING_DEMO_H
#define MULTITHREADING_DEMO_H

#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <chrono>
#include <vector>
#include <queue>
#include <random>
#include "thread_safe_queue.h"

// 演示多线程编程
namespace multithreading_demo {
    // 演示基本线程操作
    void basic_threading_demo() {
        std::cout << "\n=== 基本线程操作演示 ===" << std::endl;
        
        // 创建线程
        std::thread t1([]() {
            for (int i = 0; i < 5; ++i) {
                std::cout << "线程1执行: " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
        
        std::thread t2([]() {
            for (int i = 0; i < 5; ++i) {
                std::cout << "线程2执行: " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(150));
            }
        });
        
        // 等待线程完成
        t1.join();
        t2.join();
    }


    void mutex_condition_variable_demo() {
        std::cout << "\n=== 互斥锁和条件变量演示 ===" << std::endl;
        
        // 使用继承和std::shared_ptr的方式
        std::shared_ptr<ThreadSafeQueue> queue = std::make_shared<ThreadSafeQueue>();
        std::vector<std::thread> threads;

        threads.reserve(2);
        // 生产者线程
        threads.emplace_back([queue]() {
            for (int i = 0; i < 5; ++i) {
                queue->push(i);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
        
        // 消费者线程
        threads.emplace_back([queue]() {
            for (int i = 0; i < 5; ++i) {
                int value = queue->pop();
                std::cout << "消费值: " << value << std::endl;
            }
        });
        
        // 等待所有线程完成
        for (auto& t : threads) {
            t.join();
        }
    }

    // 演示原子操作
    void atomic_operations_demo() {
        std::cout << "\n=== 原子操作演示 ===" << std::endl;
        
        std::atomic<int> counter(0);
        std::vector<std::thread> threads;
        
        // 创建多个线程同时增加计数器
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back([&counter]() {
                for (int j = 0; j < 1000; ++j) {
                    ++counter;  // 原子操作
                }
            });
        }
        
        // 等待所有线程完成
        for (auto& t : threads) {
            t.join();
        }
        
        std::cout << "最终计数: " << counter << std::endl;
    }

    // 演示异步操作和future
    int compute_square(int x) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return x * x;
    }

    void async_future_demo() {
        std::cout << "\n=== 异步操作和future演示 ===" << std::endl;
        
        // 异步计算
        std::future<int> f1 = std::async(std::launch::async, compute_square, 5);
        std::future<int> f2 = std::async(std::launch::async, compute_square, 8);
        
        // 获取结果
        int result1 = f1.get();
        int result2 = f2.get();
        
        std::cout << "5的平方: " << result1 << std::endl;
        std::cout << "8的平方: " << result2 << std::endl;
    }

    // 演示共享互斥锁
    class SharedMutexDemo {
    private:
        int value_ = 0;
        mutable std::shared_mutex mutex_;

    public:
        void write_value(int value) {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            value_ = value;
            std::cout << "写入值: " << value_ << std::endl;
        }

        int read_value() const {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            std::cout << "读取值: " << value_ << std::endl;
            return value_;
        }
    };

    void shared_mutex_demo() {
        std::cout << "\n=== 共享互斥锁演示 ===" << std::endl;
        
        SharedMutexDemo demo;
        std::vector<std::thread> threads;
        
        // 创建读线程
        for (int i = 0; i < 3; ++i) {
            threads.emplace_back([&demo]() {
                for (int j = 0; j < 3; ++j) {
                    demo.read_value();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
            });
        }
        
        // 创建写线程
        threads.emplace_back([&demo]() {
            for (int i = 0; i < 3; ++i) {
                demo.write_value(i * 10);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
        
        // 等待所有线程完成
        for (auto& t : threads) {
            t.join();
        }
    }

    // 线程安全性测试
    void thread_safety_test() {
        std::cout << "\n=== 线程安全性测试 ===" << std::endl;
        
        // 测试线程安全的随机数生成
        std::vector<std::thread> threads;
        std::vector<std::vector<int>> results(5);
        
        for (int i = 0; i < 5; ++i) {
            threads.emplace_back([i, &results]() {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(1, 100);
                
                for (int j = 0; j < 10; ++j) {
                    results[i].push_back(dis(gen));
                }
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
        
        // 输出结果
        for (int i = 0; i < 5; ++i) {
            std::cout << "线程 " << i << " 生成的随机数: ";
            for (const auto& num : results[i]) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }
}

#endif // MULTITHREADING_DEMO_H