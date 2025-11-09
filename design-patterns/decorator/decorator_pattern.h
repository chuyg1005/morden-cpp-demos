#ifndef DECORATOR_PATTERN_H
#define DECORATOR_PATTERN_H

#include "../design_patterns_base.h"

// 装饰器模式 (Decorator Pattern)
namespace design_patterns_demo {
    class Component {
    public:
        virtual ~Component() = default;
        virtual std::string operation() = 0;
    };

    class ConcreteComponent : public Component {
    public:
        std::string operation() override {
            return "基础操作";
        }
    };

    class Decorator : public Component {
    protected:
        std::unique_ptr<Component> component_;

    public:
        explicit Decorator(std::unique_ptr<Component> component) 
            : component_(std::move(component)) {}

        std::string operation() override {
            return component_->operation();
        }
    };

    class ConcreteDecoratorA : public Decorator {
    public:
        explicit ConcreteDecoratorA(std::unique_ptr<Component> component) 
            : Decorator(std::move(component)) {}

        std::string operation() override {
            return "装饰器A(" + Decorator::operation() + ")";
        }
    };

    class ConcreteDecoratorB : public Decorator {
    public:
        explicit ConcreteDecoratorB(std::unique_ptr<Component> component) 
            : Decorator(std::move(component)) {}

        std::string operation() override {
            return "装饰器B(" + Decorator::operation() + ")";
        }
    };

    void decorator_demo() {
        std::cout << "\n=== 装饰器模式演示 ===" << std::endl;
        
        // 创建基础组件
        auto component = std::make_unique<ConcreteComponent>();
        std::cout << "基础组件: " << component->operation() << std::endl;
        
        // 添加装饰器A
        auto decoratedA = std::make_unique<ConcreteDecoratorA>(std::move(component));
        std::cout << "装饰后A: " << decoratedA->operation() << std::endl;
        
        // 再添加装饰器B
        auto decoratedB = std::make_unique<ConcreteDecoratorB>(std::move(decoratedA));
        std::cout << "装饰后B: " << decoratedB->operation() << std::endl;
    }
}

#endif // DECORATOR_PATTERN_H