#ifndef FACTORY_PATTERN_H
#define FACTORY_PATTERN_H

#include "../design_patterns_base.h"

// 工厂模式 (Factory Pattern)
namespace design_patterns_demo {
    // 产品基类
    class Product {
    public:
        virtual ~Product() = default;
        virtual std::string getName() = 0;
    };

    // 具体产品A
    class ConcreteProductA : public Product {
    public:
        std::string getName() override {
            return "产品A";
        }
    };

    // 具体产品B
    class ConcreteProductB : public Product {
    public:
        std::string getName() override {
            return "产品B";
        }
    };

    // 1. 简单工厂模式 (Simple Factory Pattern)
    class SimpleFactory {
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

    // 2. 工厂方法模式 (Factory Method Pattern)
    // 工厂基类
    class FactoryMethod {
    public:
        virtual ~FactoryMethod() = default;
        virtual std::unique_ptr<Product> createProduct() = 0;
    };

    // 具体工厂A
    class ConcreteFactoryA : public FactoryMethod {
    public:
        std::unique_ptr<Product> createProduct() override {
            return std::make_unique<ConcreteProductA>();
        }
    };

    // 具体工厂B
    class ConcreteFactoryB : public FactoryMethod {
    public:
        std::unique_ptr<Product> createProduct() override {
            return std::make_unique<ConcreteProductB>();
        }
    };

    // 3. 抽象工厂模式 (Abstract Factory Pattern)
    // 抽象产品族
    class AbstractProductA {
    public:
        virtual ~AbstractProductA() = default;
        virtual std::string getName() = 0;
    };

    class AbstractProductB {
    public:
        virtual ~AbstractProductB() = default;
        virtual std::string getType() = 0;
    };

    // 具体产品A1
    class ConcreteProductA1 : public AbstractProductA {
    public:
        std::string getName() override {
            return "产品A1";
        }
    };

    // 具体产品A2
    class ConcreteProductA2 : public AbstractProductA {
    public:
        std::string getName() override {
            return "产品A2";
        }
    };

    // 具体产品B1
    class ConcreteProductB1 : public AbstractProductB {
    public:
        std::string getType() override {
            return "类型B1";
        }
    };

    // 具体产品B2
    class ConcreteProductB2 : public AbstractProductB {
    public:
        std::string getType() override {
            return "类型B2";
        }
    };

    // 抽象工厂
    class AbstractFactory {
    public:
        virtual ~AbstractFactory() = default;
        virtual std::unique_ptr<AbstractProductA> createProductA() = 0;
        virtual std::unique_ptr<AbstractProductB> createProductB() = 0;
    };

    // 具体工厂1
    class ConcreteFactory1 : public AbstractFactory {
    public:
        std::unique_ptr<AbstractProductA> createProductA() override {
            return std::make_unique<ConcreteProductA1>();
        }

        std::unique_ptr<AbstractProductB> createProductB() override {
            return std::make_unique<ConcreteProductB1>();
        }
    };

    // 具体工厂2
    class ConcreteFactory2 : public AbstractFactory {
    public:
        std::unique_ptr<AbstractProductA> createProductA() override {
            return std::make_unique<ConcreteProductA2>();
        }

        std::unique_ptr<AbstractProductB> createProductB() override {
            return std::make_unique<ConcreteProductB2>();
        }
    };

    // 简单工厂演示
    void simple_factory_demo() {
        std::cout << "\n=== 简单工厂模式演示 ===" << std::endl;
        
        auto productA = SimpleFactory::createProduct(SimpleFactory::ProductType::A);
        auto productB = SimpleFactory::createProduct(SimpleFactory::ProductType::B);
        
        if (productA) {
            std::cout << "创建了: " << productA->getName() << std::endl;
        }
        
        if (productB) {
            std::cout << "创建了: " << productB->getName() << std::endl;
        }
    }

    // 工厂方法演示
    void factory_method_demo() {
        std::cout << "\n=== 工厂方法模式演示 ===" << std::endl;
        
        std::unique_ptr<FactoryMethod> factoryA = std::make_unique<ConcreteFactoryA>();
        std::unique_ptr<FactoryMethod> factoryB = std::make_unique<ConcreteFactoryB>();
        
        auto productA = factoryA->createProduct();
        auto productB = factoryB->createProduct();
        
        if (productA) {
            std::cout << "工厂A创建了: " << productA->getName() << std::endl;
        }
        
        if (productB) {
            std::cout << "工厂B创建了: " << productB->getName() << std::endl;
        }
    }

    // 抽象工厂演示
    void abstract_factory_demo() {
        std::cout << "\n=== 抽象工厂模式演示 ===" << std::endl;
        
        // 使用工厂1创建产品族
        std::unique_ptr<AbstractFactory> factory1 = std::make_unique<ConcreteFactory1>();
        auto productA1 = factory1->createProductA();
        auto productB1 = factory1->createProductB();
        
        std::cout << "工厂1创建了产品族:" << std::endl;
        if (productA1) {
            std::cout << "  " << productA1->getName() << std::endl;
        }
        if (productB1) {
            std::cout << "  " << productB1->getType() << std::endl;
        }
        
        // 使用工厂2创建产品族
        std::unique_ptr<AbstractFactory> factory2 = std::make_unique<ConcreteFactory2>();
        auto productA2 = factory2->createProductA();
        auto productB2 = factory2->createProductB();
        
        std::cout << "工厂2创建了产品族:" << std::endl;
        if (productA2) {
            std::cout << "  " << productA2->getName() << std::endl;
        }
        if (productB2) {
            std::cout << "  " << productB2->getType() << std::endl;
        }
    }

    // 工厂模式总演示
    void factory_demo() {
        std::cout << "\n=== 工厂模式演示 ===" << std::endl;
        simple_factory_demo();
        factory_method_demo();
        abstract_factory_demo();
    }
}

#endif // FACTORY_PATTERN_H