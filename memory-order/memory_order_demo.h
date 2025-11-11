#ifndef CPP_LEARNING_DEMO_MEMORY_ORDER_DEMO_H
#define CPP_LEARNING_DEMO_MEMORY_ORDER_DEMO_H

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

namespace memory_order_demo {
    // 1. memory_order_relaxed 示例
    // 最宽松的内存顺序，只保证原子性，不保证可见性和顺序性
    void relaxed_ordering_demo() {
        std::cout << "\n=== memory_order_relaxed 示例 ===" << std::endl;
        std::atomic<int> counter{0};
        std::atomic<bool> ready{false};
        int data = 0;
        
        // 写线程
        std::thread writer([&]() {
            data = 42;  // 普通写入
            counter.store(1, std::memory_order_relaxed);  // 原子写入
            ready.store(true, std::memory_order_relaxed);  // 原子写入
        });
        
        // 读线程
        std::thread reader([&]() {
            while (!ready.load(std::memory_order_relaxed)) {
                // 等待ready变为true
            }
            std::cout << "Counter: " << counter.load(std::memory_order_relaxed) << std::endl;
            std::cout << "Data: " << data << std::endl;  // 可能读到未定义值！
        });
        
        writer.join();
        reader.join();
    }
    
    // 2. memory_order_acquire 和 memory_order_release 示例
    // 用于同步不同线程之间的操作
    void acquire_release_ordering_demo() {
        std::cout << "\n=== memory_order_acquire/memory_order_release 示例 ===" << std::endl;
        std::atomic<int> data{0};
        std::atomic<bool> ready{false};
        
        // 写线程
        std::thread writer([&]() {
            data.store(42, std::memory_order_relaxed);  // 数据写入
            ready.store(true, std::memory_order_release);  // 释放操作
        });
        
        // 读线程
        std::thread reader([&]() {
            while (!ready.load(std::memory_order_acquire)) {  // 获取操作
                // 等待ready变为true
            }
            std::cout << "Data: " << data.load(std::memory_order_relaxed) << std::endl;  // 保证读到42
        });
        
        writer.join();
        reader.join();
    }
    
    // 3. memory_order_acq_rel 示例
    // 用于read-modify-write操作，既是获取也是释放
    void acq_rel_ordering_demo() {
        std::cout << "\n=== memory_order_acq_rel 示例 ===" << std::endl;
        std::atomic<int> counter{0};
        
        // 多个线程同时增加计数器
        std::vector<std::thread> threads;
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back([&counter]() {
                for (int j = 0; j < 1000; ++j) {
                    counter.fetch_add(1, std::memory_order_acq_rel);  // 获取-修改-释放操作
                }
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
        
        std::cout << "Final counter value: " << counter.load(std::memory_order_relaxed) << std::endl;
    }
    
    // 4. memory_order_seq_cst 示例
    // 最严格的内存顺序，保证全局顺序一致性
    void seq_cst_ordering_demo() {
        std::cout << "\n=== memory_order_seq_cst 示例 ===" << std::endl;
        std::atomic<bool> x{false};
        std::atomic<bool> y{false};
        std::atomic<int> z{0};
        
        // 线程1
        std::thread thread1([&]() {
            x.store(true, std::memory_order_seq_cst);
        });
        
        // 线程2
        std::thread thread2([&]() {
            y.store(true, std::memory_order_seq_cst);
        });
        
        // 线程3
        std::thread thread3([&]() {
            while (!x.load(std::memory_order_seq_cst)) {
                // 等待x变为true
            }
            if (y.load(std::memory_order_seq_cst)) {
                z.fetch_add(1, std::memory_order_seq_cst);
            }
        });
        
        // 线程4
        std::thread thread4([&]() {
            while (!y.load(std::memory_order_seq_cst)) {
                // 等待y变为true
            }
            if (x.load(std::memory_order_seq_cst)) {
                z.fetch_add(1, std::memory_order_seq_cst);
            }
        });
        
        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();
        
        std::cout << "z = " << z.load(std::memory_order_seq_cst) << std::endl;
        // 在seq_cst模型下，z的值一定是2
    }
    
    // 5. 实际应用示例：无锁单生产者单消费者队列
    template<typename T>
    class LockFreeSPSCQueue {
    private:
        static constexpr size_t kCapacity = 1024;
        T buffer[kCapacity];
        std::atomic<size_t> write_index{0};
        std::atomic<size_t> read_index{0};
        
    public:
        bool push(const T& item) {
            size_t current_write = write_index.load(std::memory_order_relaxed);
            size_t next_write = (current_write + 1) % kCapacity;
            
            // 检查队列是否已满
            if (next_write == read_index.load(std::memory_order_acquire)) {
                return false;  // 队列已满
            }
            
            buffer[current_write] = item;
            write_index.store(next_write, std::memory_order_release);  // 释放写入
            return true;
        }
        
        bool pop(T& item) {
            size_t current_read = read_index.load(std::memory_order_relaxed);
            
            // 检查队列是否为空
            if (current_read == write_index.load(std::memory_order_acquire)) {
                return false;  // 队列为空
            }
            
            item = buffer[current_read];
            read_index.store((current_read + 1) % kCapacity, std::memory_order_release);  // 释放读取
            return true;
        }
    };
    
    void lock_free_queue_demo() {
        std::cout << "\n=== 无锁队列示例 ===" << std::endl;
        LockFreeSPSCQueue<int> queue;
        
        // 生产者线程
        std::thread producer([&]() {
            for (int i = 0; i < 10; ++i) {
                while (!queue.push(i)) {
                    std::this_thread::sleep_for(std::chrono::microseconds(1));
                }
                std::cout << "生产: " << i << std::endl;
            }
        });
        
        // 消费者线程
        std::thread consumer([&]() {
            for (int i = 0; i < 10; ++i) {
                int value;
                while (!queue.pop(value)) {
                    std::this_thread::sleep_for(std::chrono::microseconds(1));
                }
                std::cout << "消费: " << value << std::endl;
            }
        });
        
        producer.join();
        consumer.join();
    }
    
    // 运行所有演示
    void run_demo() {
        std::cout << "=== C++ 内存顺序模型演示 ===" << std::endl;
        relaxed_ordering_demo();
        acquire_release_ordering_demo();
        acq_rel_ordering_demo();
        seq_cst_ordering_demo();
        lock_free_queue_demo();
    }
}

#endif //CPP_LEARNING_DEMO_MEMORY_ORDER_DEMO_H