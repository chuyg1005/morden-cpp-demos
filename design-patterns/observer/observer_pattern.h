#ifndef OBSERVER_PATTERN_H
#define OBSERVER_PATTERN_H

#include "../design_patterns_base.h"

// 观察者模式 (Observer Pattern)
namespace design_patterns_demo {
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
}

#endif // OBSERVER_PATTERN_H