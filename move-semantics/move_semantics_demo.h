#ifndef MOVE_SEMANTICS_DEMO_H
#define MOVE_SEMANTICS_DEMO_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>

// 演示移动语义的使用
namespace move_semantics_demo {
    class MyString {
    private:
        char* data_;
        size_t size_;
        size_t capacity_;

        void allocate(size_t capacity) {
            data_ = new char[capacity];
            capacity_ = capacity;
        }

    public:
        // 默认构造函数
        MyString() : data_(nullptr), size_(0), capacity_(0) {
            std::cout << "MyString默认构造函数" << std::endl;
        }

        // 带参数的构造函数
        explicit MyString(const char* str) {
            size_ = std::strlen(str);
            capacity_ = size_ + 1;
            data_ = new char[capacity_];
            std::strcpy(data_, str);
            std::cout << "MyString构造函数: " << data_ << std::endl;
        }

        // 拷贝构造函数
        MyString(const MyString& other) : size_(other.size_), capacity_(other.capacity_) {
            data_ = new char[capacity_];
            std::strcpy(data_, other.data_);
            std::cout << "MyString拷贝构造函数: " << data_ << std::endl;
        }

        // 拷贝赋值运算符
        MyString& operator=(const MyString& other) {
            if (this != &other) {
                delete[] data_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                data_ = new char[capacity_];
                std::strcpy(data_, other.data_);
                std::cout << "MyString拷贝赋值运算符: " << data_ << std::endl;
            }
            return *this;
        }

        // 移动构造函数
        MyString(MyString&& other) noexcept 
            : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
            std::cout << "MyString移动构造函数" << std::endl;
        }

        // 移动赋值运算符
        MyString& operator=(MyString&& other) noexcept {
            if (this != &other) {
                delete[] data_;
                data_ = other.data_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                other.data_ = nullptr;
                other.size_ = 0;
                other.capacity_ = 0;
                std::cout << "MyString移动赋值运算符" << std::endl;
            }
            return *this;
        }

        // 析构函数
        ~MyString() {
            delete[] data_;
            std::cout << "MyString析构函数" << std::endl;
        }

        const char* c_str() const {
            return data_ ? data_ : "";
        }

        size_t size() const {
            return size_;
        }
    };

    // 演示拷贝与移动的性能差异
    void copy_vs_move_performance_demo() {
        std::cout << "\n=== 拷贝与移动性能比较 ===" << std::endl;
        
        // 创建一个大的vector
        std::vector<MyString> vec;
        vec.reserve(3);
        vec.emplace_back("Hello");
        vec.emplace_back("World");
        vec.emplace_back("C++");
        
        // 测试拷贝性能
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<MyString> copy_vec = vec;  // 拷贝构造
        auto end = std::chrono::high_resolution_clock::now();
        auto copy_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // 测试移动性能
        start = std::chrono::high_resolution_clock::now();
        std::vector<MyString> move_vec = std::move(vec);  // 移动构造
        end = std::chrono::high_resolution_clock::now();
        auto move_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "拷贝构造时间: " << copy_duration.count() << " 微秒" << std::endl;
        std::cout << "移动构造时间: " << move_duration.count() << " 微秒" << std::endl;
    }

    // 演示std::move的使用
    void std_move_demo() {
        std::cout << "\n=== std::move演示 ===" << std::endl;
        
        MyString str1("Original");
        std::cout << "str1内容: " << str1.c_str() << std::endl;
        
        // 使用std::move转移资源
        MyString str2 = std::move(str1);
        std::cout << "str1内容: " << str1.c_str() << std::endl;
        std::cout << "str2内容: " << str2.c_str() << std::endl;
    }

    // 演示完美转发
    template<typename T>
    void wrapper(T&& param) {
        // 使用forward完美转发
        MyString str(std::forward<T>(param));
    }

    void perfect_forwarding_demo() {
        std::cout << "\n=== 完美转发演示 ===" << std::endl;
        
        MyString str("Test");
        wrapper(str);        // 左值 - 调用拷贝构造
        wrapper("Temp");     // 右值 - 调用移动构造
    }

    // 演示移动迭代器
    void move_iterator_demo() {
        std::cout << "\n=== 移动迭代器演示 ===" << std::endl;
        
        std::vector<MyString> vec;
        vec.emplace_back("First");
        vec.emplace_back("Second");
        vec.emplace_back("Third");
        
        std::cout << "使用移动迭代器:" << std::endl;
        std::vector<MyString> new_vec;
        // 使用make_move_iterator将拷贝转换为移动
        std::move(vec.begin(), vec.end(), std::back_inserter(new_vec));
        
        std::cout << "原vector大小: " << vec.size() << std::endl;
        std::cout << "新vector大小: " << new_vec.size() << std::endl;
    }
}

#endif // MOVE_SEMANTICS_DEMO_H