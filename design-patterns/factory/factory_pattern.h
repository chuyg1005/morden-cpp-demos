#ifndef FACTORY_PATTERN_H
#define FACTORY_PATTERN_H

#include "../design_patterns_base.h"

// 工厂模式 (Factory Pattern)
namespace design_patterns_demo {
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

#endif // FACTORY_PATTERN_H