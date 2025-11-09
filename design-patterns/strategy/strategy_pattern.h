#ifndef STRATEGY_PATTERN_H
#define STRATEGY_PATTERN_H

#include "../design_patterns_base.h"

// 策略模式 (Strategy Pattern)
namespace design_patterns_demo {
    class Strategy {
    public:
        virtual ~Strategy() = default;
        virtual int execute(int a, int b) = 0;
    };

    class AddStrategy : public Strategy {
    public:
        int execute(int a, int b) override {
            return a + b;
        }
    };

    class MultiplyStrategy : public Strategy {
    public:
        int execute(int a, int b) override {
            return a * b;
        }
    };

    class Context {
    private:
        std::unique_ptr<Strategy> strategy_;

    public:
        explicit Context(std::unique_ptr<Strategy> strategy) 
            : strategy_(std::move(strategy)) {}

        int executeStrategy(int a, int b) {
            return strategy_->execute(a, b);
        }
    };

    void strategy_demo() {
        std::cout << "\n=== 策略模式演示 ===" << std::endl;
        
        // 使用加法策略
        Context addContext(std::make_unique<AddStrategy>());
        std::cout << "加法策略结果: 5 + 3 = " << addContext.executeStrategy(5, 3) << std::endl;
        
        // 使用乘法策略
        Context multiplyContext(std::make_unique<MultiplyStrategy>());
        std::cout << "乘法策略结果: 5 * 3 = " << multiplyContext.executeStrategy(5, 3) << std::endl;
    }
}

#endif // STRATEGY_PATTERN_H