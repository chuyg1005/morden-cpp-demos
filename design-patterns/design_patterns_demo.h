#ifndef DESIGN_PATTERNS_DEMO_H
#define DESIGN_PATTERNS_DEMO_H

#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <mutex>
#include <thread>
#include <chrono>

// 演示C++中的设计模式
namespace design_patterns_demo {
    // 1. 单例模式 (Singleton Pattern)
    class Singleton {
    private:
        static std::unique_ptr<Singleton> instance_;
        static std::mutex mutex_;

        // 私有构造函数
        Singleton() {
            std::cout << "Singleton实例已创建" << std::endl;
        }

    public:
        // 禁止拷贝
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        // 获取实例
        static Singleton* getInstance() {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!instance_) {
                instance_ = std::unique_ptr<Singleton>(new Singleton());
            }
            return instance_.get();
        }

        void doSomething() {
            std::cout << "执行某些操作" << std::endl;
        }
    };

    // 静态成员定义
    std::unique_ptr<Singleton> Singleton::instance_ = nullptr;
    std::mutex Singleton::mutex_;

    void singleton_demo() {
        std::cout << "\n=== 单例模式演示 ===" << std::endl;
        
        // 获取单例实例
        Singleton* s1 = Singleton::getInstance();
        Singleton* s2 = Singleton::getInstance();
        
        // 验证是否为同一实例
        std::cout << "s1地址: " << s1 << std::endl;
        std::cout << "s2地址: " << s2 << std::endl;
        std::cout << "是否为同一实例: " << std::boolalpha << (s1 == s2) << std::endl;
        
        s1->doSomething();
    }

    // 2. 观察者模式 (Observer Pattern)
    class Observer {
    public:
        virtual ~Observer() = default;
        virtual void update(const std::string& message) = 0;
    };

    class Subject {
    private:
        std::vector<std::shared_ptr<Observer>> observers_;

    public:
        void attach(std::shared_ptr<Observer> observer) {
            observers_.push_back(observer);
        }

        void notify(const std::string& message) {
            for (const auto& observer : observers_) {
                observer->update(message);
            }
        }
    };

    class ConcreteObserver : public Observer {
    private:
        std::string name_;

    public:
        explicit ConcreteObserver(const std::string& name) : name_(name) {}

        void update(const std::string& message) override {
            std::cout << "观察者 " << name_ << " 收到消息: " << message << std::endl;
        }
    };

    void observer_demo() {
        std::cout << "\n=== 观察者模式演示 ===" << std::endl;
        
        Subject subject;
        
        auto observer1 = std::make_shared<ConcreteObserver>("Observer1");
        auto observer2 = std::make_shared<ConcreteObserver>("Observer2");
        
        subject.attach(observer1);
        subject.attach(observer2);
        
        subject.notify("Hello, Observers!");
    }

    // 3. 策略模式 (Strategy Pattern)
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

    // 4. 装饰器模式 (Decorator Pattern)
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

    // 5. 工厂模式 (Factory Pattern)
    class Product {
    public:
        virtual ~Product() = default;
        virtual std::string getName() = 0;
    };

    class ConcreteProductA : public Product {
    public:
        std::string getName() override {
            return "产品A";
        }
    };

    class ConcreteProductB : public Product {
    public:
        std::string getName() override {
            return "产品B";
        }
    };

    class Factory {
    public:
        enum class ProductType {
            A, B
        };

        static std::unique_ptr<Product> createProduct(ProductType type) {
            switch (type) {
                case ProductType::A:
                    return std::make_unique<ConcreteProductA>();
                case ProductType::B:
                    return std::make_unique<ConcreteProductB>();
                default:
                    return nullptr;
            }
        }
    };

    void factory_demo() {
        std::cout << "\n=== 工厂模式演示 ===" << std::endl;
        
        auto productA = Factory::createProduct(Factory::ProductType::A);
        auto productB = Factory::createProduct(Factory::ProductType::B);
        
        if (productA) {
            std::cout << "创建了: " << productA->getName() << std::endl;
        }
        
        if (productB) {
            std::cout << "创建了: " << productB->getName() << std::endl;
        }
    }
}

#endif // DESIGN_PATTERNS_DEMO_H