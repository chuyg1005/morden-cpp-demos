//
// Created by Yukang Chu on 25-11-9.
//

#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <queue>


namespace multithreading_demo {
    class Queue {
    public:
        virtual ~Queue() = default;
        virtual int pop() = 0;
        virtual bool empty() const = 0;
        virtual void push(int value) = 0;
    };

    // 演示互斥锁和条件变量
    class ThreadSafeQueue: public Queue {
    private:
        std::queue<int> queue_;
        mutable std::mutex mutex_;
        std::condition_variable cond_var_;

    public:
        void push(int value) {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(value);
            cond_var_.notify_one();
        }

        int pop() {
            std::unique_lock<std::mutex> lock(mutex_);
            cond_var_.wait(lock, [this] { return !queue_.empty(); });
            int value = queue_.front();
            queue_.pop();
            return value;
        }

        bool empty() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.empty();
        }
    };
}


#endif //THREAD_SAFE_QUEUE_H
