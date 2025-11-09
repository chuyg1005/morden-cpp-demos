#ifndef CPP_LEARNING_DEMO_ADVANCED_CONCURRENCY_DEMO_H
#define CPP_LEARNING_DEMO_ADVANCED_CONCURRENCY_DEMO_H

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
#include <memory>
#include <functional>
#include <algorithm>

namespace advanced_concurrency_demo {
    // 1. 线程池实现
    class ThreadPool {
    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;
        std::mutex queue_mutex;
        std::condition_variable condition;
        bool stop;

    public:
        ThreadPool(size_t threads) : stop(false) {
            for(size_t i = 0; i < threads; ++i) {
                workers.emplace_back([this] {
                    for(;;) {
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            this->condition.wait(lock, [this]{ return this->stop || !this->tasks.empty(); });
                            if(this->stop && this->tasks.empty()) return;
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }
                        task();
                    }
                });
            }
        }

        template<class F, class... Args>
        auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
            using return_type = std::invoke_result_t<F, Args...>;

            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

            std::future<return_type> res = task->get_future();
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                if(stop) throw std::runtime_error("enqueue on stopped ThreadPool");
                tasks.emplace([task](){ (*task)(); });
            }
            condition.notify_one();
            return res;
        }

        ~ThreadPool() {
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                stop = true;
            }
            condition.notify_all();
            for(std::thread &worker: workers) worker.join();
        }
    };

    void thread_pool_demo() {
        std::cout << "\n=== 线程池演示 ===" << std::endl;
        ThreadPool pool(4);
        std::vector<std::future<int>> results;

        // 提交任务到线程池
        for(int i = 0; i < 8; ++i) {
            results.emplace_back(
                pool.enqueue([i] {
                    std::cout << "任务 " << i << " 正在执行 (线程ID: " << std::this_thread::get_id() << ")" << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    return i * i;
                })
            );
        }

        // 获取结果
        for(auto && result: results) {
            std::cout << "结果: " << result.get() << std::endl;
        }
    }

    // 2. 无锁数据结构示例 - 无锁栈
    template<typename T>
    class LockFreeStack {
    private:
        struct Node {
            std::shared_ptr<T> data;
            std::atomic<Node*> next;
            Node(T const& data_) : data(std::make_shared<T>(data_)) {}
        };
        
        std::atomic<Node*> head;

    public:
        void push(T const& data) {
            Node* const new_node = new Node(data);
            Node* current_head = head.load();
            do {
                new_node->next = current_head;
            } while (!head.compare_exchange_weak(current_head, new_node));
        }
        
        std::shared_ptr<T> pop() {
            Node* old_head = head.load();
            while(old_head && !head.compare_exchange_weak(old_head, old_head->next));
            return old_head ? old_head->data : std::shared_ptr<T>();
        }
    };

    void lock_free_stack_demo() {
        std::cout << "\n=== 无锁栈演示 ===" << std::endl;
        LockFreeStack<int> stack;
        
        // 多线程推送元素
        std::vector<std::thread> threads;
        for(int i = 0; i < 4; ++i) {
            threads.emplace_back([&stack, i]() {
                for(int j = 0; j < 5; ++j) {
                    stack.push(i * 10 + j);
                }
            });
        }
        
        for(auto& t : threads) {
            t.join();
        }
        
        // 弹出所有元素
        std::shared_ptr<int> value;
        while((value = stack.pop())) {
            std::cout << "弹出值: " << *value << std::endl;
        }
    }

    // 3. 并发哈希表示例
    template<typename Key, typename Value>
    class ConcurrentHashMap {
    private:
        std::vector<std::pair<Key, Value>> buckets[16];  // 简化的实现
        mutable std::shared_mutex mutexes[16];

    public:
        void insert(const Key& key, const Value& value) {
            size_t index = std::hash<Key>{}(key) % 16;
            std::unique_lock<std::shared_mutex> lock(mutexes[index]);
            buckets[index].push_back({key, value});
        }

        std::pair<bool, Value> find(const Key& key) const {
            size_t index = std::hash<Key>{}(key) % 16;
            std::shared_lock<std::shared_mutex> lock(mutexes[index]);
            for(const auto& pair : buckets[index]) {
                if(pair.first == key) {
                    return {true, pair.second};
                }
            }
            return {false, Value{}};
        }
    };

    void concurrent_hash_map_demo() {
        std::cout << "\n=== 并发哈希表演示 ===" << std::endl;
        ConcurrentHashMap<std::string, int> map;
        
        // 多线程插入
        std::vector<std::thread> threads;
        for(int i = 0; i < 4; ++i) {
            threads.emplace_back([&map, i]() {
                for(int j = 0; j < 5; ++j) {
                    map.insert("key" + std::to_string(i * 5 + j), i * 5 + j);
                }
            });
        }
        
        for(auto& t : threads) {
            t.join();
        }
        
        // 查找元素
        for(int i = 0; i < 20; ++i) {
            auto result = map.find("key" + std::to_string(i));
            if(result.first) {
                std::cout << "找到键值对: key" << i << " -> " << result.second << std::endl;
            }
        }
    }

    // 4. 原子操作高级用法
    void atomic_operations_demo() {
        std::cout << "\n=== 原子操作高级用法演示 ===" << std::endl;
        
        // 原子标志
        std::atomic_flag flag = ATOMIC_FLAG_INIT;
        std::cout << "原子标志初始状态: " << flag.test_and_set() << std::endl;
        std::cout << "原子标志设置后状态: " << flag.test_and_set() << std::endl;
        flag.clear();
        std::cout << "原子标志清除后状态: " << flag.test_and_set() << std::endl;
        
        // 原子整数
        std::atomic<int> counter{0};
        std::vector<std::thread> threads;
        
        // 多线程增加计数器
        for(int i = 0; i < 4; ++i) {
            threads.emplace_back([&counter]() {
                for(int j = 0; j < 1000; ++j) {
                    counter.fetch_add(1, std::memory_order_relaxed);
                }
            });
        }
        
        for(auto& t : threads) {
            t.join();
        }
        
        std::cout << "多线程增加后的计数器值: " << counter.load() << std::endl;
        
        // CAS操作
        std::atomic<int> cas_value{10};
        int expected = 10;
        bool success = cas_value.compare_exchange_strong(expected, 20);
        std::cout << "CAS操作成功: " << success << ", 新值: " << cas_value.load() << std::endl;
    }

    // 5. 异步编程高级用法
    void advanced_async_demo() {
        std::cout << "\n=== 异步编程高级用法演示 ===" << std::endl;
        
        // 使用 packaged_task
        std::packaged_task<int(int, int)> task([](int a, int b) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return a + b;
        });
        
        std::future<int> f1 = task.get_future();
        std::thread t(std::move(task), 2, 3);
        
        std::cout << "packaged_task结果: " << f1.get() << std::endl;
        t.join();
        
        // 使用 promise
        std::promise<std::string> prom;
        std::future<std::string> f2 = prom.get_future();
        
        std::thread t2([&prom]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            prom.set_value("Hello from promise!");
        });
        
        std::cout << "promise结果: " << f2.get() << std::endl;
        t2.join();
        
        // 多个异步任务
        auto future1 = std::async(std::launch::async, []() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return 1;
        });
        
        auto future2 = std::async(std::launch::async, []() {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 2;
        });
        
        auto future3 = std::async(std::launch::async, []() {
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            return 3;
        });
        
        std::cout << "异步任务结果: " << future1.get() << " " << future2.get() << " " << future3.get() << std::endl;
    }

    // 6. 线程局部存储
    thread_local int thread_local_value = 0;

    void thread_local_storage_demo() {
        std::cout << "\n=== 线程局部存储演示 ===" << std::endl;
        
        auto worker = [](int id) {
            thread_local_value = id * 10;
            std::cout << "线程 " << id << " 的线程局部变量值: " << thread_local_value 
                      << " (地址: " << &thread_local_value << ")" << std::endl;
            
            // 修改值
            thread_local_value += 5;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            
            std::cout << "线程 " << id << " 修改后的线程局部变量值: " << thread_local_value << std::endl;
        };
        
        std::vector<std::thread> threads;
        for(int i = 1; i <= 3; ++i) {
            threads.emplace_back(worker, i);
        }
        
        for(auto& t : threads) {
            t.join();
        }
    }

    // 运行所有演示
    void run_demo() {
        std::cout << "=== 高级并发编程演示 ===" << std::endl;
        thread_pool_demo();
        lock_free_stack_demo();
        concurrent_hash_map_demo();
        atomic_operations_demo();
        advanced_async_demo();
        thread_local_storage_demo();
    }
}

#endif //CPP_LEARNING_DEMO_ADVANCED_CONCURRENCY_DEMO_H