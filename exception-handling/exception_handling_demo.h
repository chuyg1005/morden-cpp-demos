#ifndef EXCEPTION_HANDLING_DEMO_H
#define EXCEPTION_HANDLING_DEMO_H

#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <memory>

// 演示异常处理的使用
namespace exception_handling_demo {
    // 自定义异常类
    class CustomException : public std::exception {
    private:
        std::string message_;

    public:
        explicit CustomException(const std::string& msg) : message_(msg) {}

        const char* what() const noexcept override {
            return message_.c_str();
        }
    };

    // 演示基本异常处理
    void basic_exception_handling_demo() {
        std::cout << "\n=== 基本异常处理演示 ===" << std::endl;
        
        try {
            // 抛出标准异常
            throw std::runtime_error("运行时错误");
        } catch (const std::runtime_error& e) {
            std::cout << "捕获到runtime_error: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "捕获到exception: " << e.what() << std::endl;
        }
        
        try {
            // 抛出自定义异常
            throw CustomException("自定义错误信息");
        } catch (const CustomException& e) {
            std::cout << "捕获到CustomException: " << e.what() << std::endl;
        }
    }

    // 演示异常安全保证
    class ExceptionSafeClass {
    private:
        std::vector<int> data_;
        int* ptr_;

    public:
        ExceptionSafeClass() : ptr_(nullptr) {
            std::cout << "ExceptionSafeClass构造函数" << std::endl;
        }

        // 演示强异常安全保证
        void strong_guarantee_operation(int value) {
            // 创建临时对象进行操作
            std::vector<int> temp_data = data_;
            temp_data.push_back(value);
            
            // 只有在所有操作都成功后才修改对象状态，保障事务特性
            data_ = std::move(temp_data);
            std::cout << "强异常安全保证操作完成" << std::endl;
        }

        // 演示无异常安全保证
        void no_guarantee_operation(int index, int value) {
            // 直接修改对象状态，如果出错则状态不一致
            data_.at(index) = value;  // 可能抛出std::out_of_range
            std::cout << "无异常安全保证操作完成" << std::endl;
        }

        ~ExceptionSafeClass() {
            std::cout << "ExceptionSafeClass析构函数" << std::endl;
        }
    };

    void exception_safety_demo() {
        std::cout << "\n=== 异常安全演示 ===" << std::endl;
        
        ExceptionSafeClass obj;
        
        try {
            obj.strong_guarantee_operation(42);
        } catch (const std::exception& e) {
            std::cout << "强异常安全保证操作异常: " << e.what() << std::endl;
        }
        
        try {
            obj.no_guarantee_operation(10, 100);  // 会抛出异常
        } catch (const std::out_of_range& e) {
            std::cout << "无异常安全保证操作异常: " << e.what() << std::endl;
        }
    }

    // 演示函数try块
    class FunctionTryBlockDemo {
    private:
        std::unique_ptr<int> ptr_;

    public:
        // 构造函数中的函数try块
        FunctionTryBlockDemo(int value) try : ptr_(std::make_unique<int>(value)) {
            std::cout << "FunctionTryBlockDemo构造函数" << std::endl;
            if (value < 0) {
                throw std::invalid_argument("值不能为负数");
            }
        } catch (...) {
            std::cout << "构造函数中捕获异常" << std::endl;
            throw;  // 重新抛出异常
        }

        ~FunctionTryBlockDemo() {
            std::cout << "FunctionTryBlockDemo析构函数" << std::endl;
        }
    };

    class FunctionNoexceptDemo {
    private:
        std::unique_ptr<int> ptr_;

    public:
        // 构造函数中的函数try块
        FunctionNoexceptDemo(int value) noexcept : ptr_(std::make_unique<int>(value)) {
            std::cout << "FunctionNoexceptDemo构造函数" << std::endl;
            if (value < 0) {
                throw std::invalid_argument("值不能为负数");
            }
        }
    };

    void function_try_block_demo() {
        std::cout << "\n=== 函数try块演示 ===" << std::endl;
        
        try {
            FunctionTryBlockDemo obj(42);
        } catch (const std::exception& e) {
            std::cout << "捕获到异常: " << e.what() << std::endl;
        }
        
        try {
            FunctionTryBlockDemo obj(-1);  // 会抛出异常
        } catch (const std::exception& e) {
            std::cout << "捕获到异常: " << e.what() << std::endl;
        }
    }

    // 演示noexcept
    void noexcept_demo() {
        std::cout << "\n=== noexcept演示 ===" << std::endl;
        
        // 检查函数是否声明为noexcept，如果函数构造函数定义为noexcept，则各种操作效率会高不少
        std::cout << "std::is_nothrow_move_constructible<int>::value: " 
                  << std::is_nothrow_move_constructible<int>::value << std::endl;

        std::cout << "std::is_nothrow_move_assignable<FunctionTryBlockDemo>::value: "
                  << std::is_nothrow_move_assignable<FunctionTryBlockDemo>::value << std::endl;

        std::cout << "std::is_nothrow_move_assignable<FunctionNoexcpetDemo>::value: "
                  << std::is_nothrow_move_assignable<FunctionNoexceptDemo>::value << std::endl;

        // 自定义noexcept函数
        auto noexcept_func = []() noexcept {
            std::cout << "noexcept函数" << std::endl;
        };
        
        noexcept_func();
        
        // noexcept与异常规格的比较
        auto throwing_func = []() {
            throw std::runtime_error("抛出异常");
        };
        
        try {
            throwing_func();
        } catch (const std::exception& e) {
            std::cout << "捕获到异常: " << e.what() << std::endl;
        }
    }
}

#endif // EXCEPTION_HANDLING_DEMO_H