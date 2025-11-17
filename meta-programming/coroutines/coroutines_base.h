#ifndef CPP_LEARNING_DEMO_COROUTINES_BASE_H
#define CPP_LEARNING_DEMO_COROUTINES_BASE_H

#include <coroutine>
#include <iostream>
#include <exception>
#include <chrono>
#include <thread>

// Base classes and utilities for coroutines

namespace coroutines_base {
    // Simple generator coroutine that yields values
    template<typename T>
    class Generator {
    public:
        struct promise_type {
            T current_value;
            
            std::suspend_always yield_value(T value) {
                current_value = value;
                return {};
            }
            
            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }
            void unhandled_exception() { std::terminate(); }
            void return_void() {}
            
            Generator get_return_object() {
                return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
            }
        };
        
        using handle_type = std::coroutine_handle<promise_type>;
        
        Generator(handle_type h) : coro(h) {}
        
        ~Generator() {
            if (coro) {
                coro.destroy();
            }
        }
        
        // Disable copy and enable move
        Generator(const Generator&) = delete;
        Generator& operator=(const Generator&) = delete;
        Generator(Generator&& other) : coro(other.coro) {
            other.coro = nullptr;
        }
        Generator& operator=(Generator&& other) {
            if (this != &other) {
                if (coro) {
                    coro.destroy();
                }
                coro = other.coro;
                other.coro = nullptr;
            }
            return *this;
        }
        
        // Iterator interface
        class Iterator {
            handle_type coro;
        public:
            Iterator(handle_type h) : coro(h) {}
            Iterator& operator++() {
                coro.resume();
                return *this;
            }
            bool operator!=(const Iterator& other) const {
                return coro != other.coro && !coro.done();
            }
            T operator*() const {
                return coro.promise().current_value;
            }
        };
        
        Iterator begin() {
            if (coro) coro.resume();
            return Iterator{coro};
        }
        
        Iterator end() {
            return Iterator{nullptr};
        }
        
    private:
        handle_type coro;
    };
    
    // Simple task coroutine that returns a value
    template<typename T>
    class Task {
    public:
        struct promise_type {
            T value;
            bool finished = false;
            
            std::suspend_never initial_suspend() { return {}; }
            std::suspend_always final_suspend() noexcept { 
                finished = true;
                return {}; 
            }
            void unhandled_exception() { std::terminate(); }
            
            Task get_return_object() {
                return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
            }
            
            void return_value(T v) {
                value = v;
            }
        };
        
        using handle_type = std::coroutine_handle<promise_type>;
        
        Task(handle_type h) : coro(h) {}
        
        ~Task() {
            if (coro) {
                coro.destroy();
            }
        }
        
        T get() {
            if (coro && !coro.done()) {
                coro.resume();
            }
            return coro.promise().value;
        }
        
        // Disable copy and enable move
        Task(const Task&) = delete;
        Task& operator=(const Task&) = delete;
        Task(Task&& other) : coro(other.coro) {
            other.coro = nullptr;
        }
        Task& operator=(Task&& other) {
            if (this != &other) {
                if (coro) {
                    coro.destroy();
                }
                coro = other.coro;
                other.coro = nullptr;
            }
            return *this;
        }
        
    private:
        handle_type coro;
    };
}

#endif //CPP_LEARNING_DEMO_COROUTINES_BASE_H