#ifndef CPP_LEARNING_DEMO_ADVANCED_DESIGN_PATTERNS_DEMO_H
#define CPP_LEARNING_DEMO_ADVANCED_DESIGN_PATTERNS_DEMO_H

#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>
#include <unordered_map>
#include <algorithm>

namespace advanced_design_patterns_demo {
    // 1. 命令模式 (Command Pattern)
    class Command {
    public:
        virtual ~Command() = default;
        virtual void execute() = 0;
    };

    class Receiver {
    public:
        void action(const std::string& msg) {
            std::cout << "Receiver执行动作: " << msg << std::endl;
        }
    };

    class ConcreteCommand : public Command {
    private:
        std::shared_ptr<Receiver> receiver;
        std::string message;

    public:
        ConcreteCommand(std::shared_ptr<Receiver> r, const std::string& msg) 
            : receiver(r), message(msg) {}

        void execute() override {
            receiver->action(message);
        }
    };

    class Invoker {
    private:
        std::vector<std::unique_ptr<Command>> commands;

    public:
        void add_command(std::unique_ptr<Command> cmd) {
            commands.push_back(std::move(cmd));
        }

        void execute_commands() {
            for (auto& cmd : commands) {
                cmd->execute();
            }
        }
    };

    void command_pattern_demo() {
        std::cout << "\n=== 命令模式演示 ===" << std::endl;
        auto receiver = std::make_shared<Receiver>();
        Invoker invoker;

        invoker.add_command(std::make_unique<ConcreteCommand>(receiver, "命令1"));
        invoker.add_command(std::make_unique<ConcreteCommand>(receiver, "命令2"));
        invoker.add_command(std::make_unique<ConcreteCommand>(receiver, "命令3"));

        invoker.execute_commands();
    }

    // 2. 责任链模式 (Chain of Responsibility Pattern)
    class Handler {
    protected:
        std::shared_ptr<Handler> next_handler;

    public:
        virtual ~Handler() = default;
        void set_next(std::shared_ptr<Handler> next) {
            next_handler = next;
        }
        virtual void handle_request(int request) {
            if (next_handler) {
                next_handler->handle_request(request);
            }
        }
    };

    class ConcreteHandler1 : public Handler {
    public:
        void handle_request(int request) override {
            if (request >= 0 && request < 10) {
                std::cout << "ConcreteHandler1处理请求: " << request << std::endl;
            } else {
                Handler::handle_request(request);
            }
        }
    };

    class ConcreteHandler2 : public Handler {
    public:
        void handle_request(int request) override {
            if (request >= 10 && request < 20) {
                std::cout << "ConcreteHandler2处理请求: " << request << std::endl;
            } else {
                Handler::handle_request(request);
            }
        }
    };

    class ConcreteHandler3 : public Handler {
    public:
        void handle_request(int request) override {
            if (request >= 20 && request < 30) {
                std::cout << "ConcreteHandler3处理请求: " << request << std::endl;
            } else {
                Handler::handle_request(request);
            }
        }
    };

    void chain_of_responsibility_demo() {
        std::cout << "\n=== 责任链模式演示 ===" << std::endl;
        auto handler1 = std::make_shared<ConcreteHandler1>();
        auto handler2 = std::make_shared<ConcreteHandler2>();
        auto handler3 = std::make_shared<ConcreteHandler3>();

        handler1->set_next(handler2);
        handler2->set_next(handler3);

        handler1->handle_request(5);   // Handler1处理
        handler1->handle_request(15);  // Handler2处理
        handler1->handle_request(25);  // Handler3处理
        handler1->handle_request(35);  // 没有处理器处理
    }

    // 3. 访问者模式 (Visitor Pattern)
    class ConcreteElementA;
    class ConcreteElementB;

    class Visitor {
    public:
        virtual ~Visitor() = default;
        virtual void visit(ConcreteElementA& element) = 0;
        virtual void visit(ConcreteElementB& element) = 0;
    };

    class Element {
    public:
        virtual ~Element() = default;
        virtual void accept(Visitor& visitor) = 0;
    };

    class ConcreteElementA : public Element {
    public:
        void accept(Visitor& visitor) override {
            visitor.visit(*this);
        }

        void operationA() {
            std::cout << "ConcreteElementA的操作" << std::endl;
        }
    };

    class ConcreteElementB : public Element {
    public:
        void accept(Visitor& visitor) override {
            visitor.visit(*this);
        }

        void operationB() {
            std::cout << "ConcreteElementB的操作" << std::endl;
        }
    };

    class ConcreteVisitor1 : public Visitor {
    public:
        void visit(ConcreteElementA& element) override {
            std::cout << "ConcreteVisitor1访问";
            element.operationA();
        }

        void visit(ConcreteElementB& element) override {
            std::cout << "ConcreteVisitor1访问";
            element.operationB();
        }
    };

    class ConcreteVisitor2 : public Visitor {
    public:
        void visit(ConcreteElementA& element) override {
            std::cout << "ConcreteVisitor2访问";
            element.operationA();
        }

        void visit(ConcreteElementB& element) override {
            std::cout << "ConcreteVisitor2访问";
            element.operationB();
        }
    };

    void visitor_pattern_demo() {
        std::cout << "\n=== 访问者模式演示 ===" << std::endl;
        std::vector<std::unique_ptr<Element>> elements;
        elements.push_back(std::make_unique<ConcreteElementA>());
        elements.push_back(std::make_unique<ConcreteElementB>());

        ConcreteVisitor1 visitor1;
        ConcreteVisitor2 visitor2;

        for (auto& element : elements) {
            element->accept(visitor1);
        }

        for (auto& element : elements) {
            element->accept(visitor2);
        }
    }

    // 4. 状态模式 (State Pattern)
    class Context;

    class State {
    public:
        virtual ~State() = default;
        virtual void handle(Context& context) = 0;
    };

    class Context {
    private:
        std::unique_ptr<State> state;

    public:
        void set_state(std::unique_ptr<State> new_state) {
            state = std::move(new_state);
        }

        void request() {
            if (state) {
                state->handle(*this);
            }
        }
    };

    class ConcreteStateA : public State {
    public:
        void handle(Context& context) override {
            std::cout << "处理状态A" << std::endl;
            context.set_state(std::make_unique<ConcreteStateB>());
        }
    };

    class ConcreteStateB : public State {
    public:
        void handle(Context& context) override {
            std::cout << "处理状态B" << std::endl;
            context.set_state(std::make_unique<ConcreteStateA>());
        }
    };

    void state_pattern_demo() {
        std::cout << "\n=== 状态模式演示 ===" << std::endl;
        Context context;
        context.set_state(std::make_unique<ConcreteStateA>());

        context.request();  // 切换到状态B
        context.request();  // 切换到状态A
        context.request();  // 切换到状态B
    }

    // 5. 模板方法模式 (Template Method Pattern)
    class AbstractClass {
    public:
        virtual ~AbstractClass() = default;

        // 模板方法
        void template_method() {
            step1();
            step2();
            step3();
        }

    protected:
        virtual void step1() {
            std::cout << "抽象类步骤1" << std::endl;
        }

        virtual void step2() = 0;  // 纯虚函数，子类必须实现

        virtual void step3() {
            std::cout << "抽象类步骤3" << std::endl;
        }
    };

    class ConcreteClassA : public AbstractClass {
    protected:
        void step2() override {
            std::cout << "具体类A步骤2" << std::endl;
        }
    };

    class ConcreteClassB : public AbstractClass {
    protected:
        void step1() override {
            std::cout << "具体类B步骤1" << std::endl;
        }

        void step2() override {
            std::cout << "具体类B步骤2" << std::endl;
        }
    };

    void template_method_demo() {
        std::cout << "\n=== 模板方法模式演示 ===" << std::endl;
        std::cout << "具体类A:" << std::endl;
        ConcreteClassA classA;
        classA.template_method();

        std::cout << "\n具体类B:" << std::endl;
        ConcreteClassB classB;
        classB.template_method();
    }

    // 6. 策略模式增强版 (Enhanced Strategy Pattern)
    class SortStrategy {
    public:
        virtual ~SortStrategy() = default;
        virtual void sort(std::vector<int>& data) = 0;
    };

    class BubbleSort : public SortStrategy {
    public:
        void sort(std::vector<int>& data) override {
            std::cout << "使用冒泡排序" << std::endl;
            size_t n = data.size();
            for (size_t i = 0; i < n-1; ++i) {
                for (size_t j = 0; j < n-i-1; ++j) {
                    if (data[j] > data[j+1]) {
                        std::swap(data[j], data[j+1]);
                    }
                }
            }
        }
    };

    class QuickSort : public SortStrategy {
    public:
        void sort(std::vector<int>& data) override {
            std::cout << "使用快速排序" << std::endl;
            quick_sort(data, 0, data.size() - 1);
        }

    private:
        void quick_sort(std::vector<int>& data, int low, int high) {
            if (low < high) {
                int pi = partition(data, low, high);
                quick_sort(data, low, pi - 1);
                quick_sort(data, pi + 1, high);
            }
        }

        int partition(std::vector<int>& data, int low, int high) {
            int pivot = data[high];
            int i = (low - 1);

            for (int j = low; j <= high - 1; j++) {
                if (data[j] < pivot) {
                    i++;
                    std::swap(data[i], data[j]);
                }
            }
            std::swap(data[i + 1], data[high]);
            return (i + 1);
        }
    };

    class SortContext {
    private:
        std::unique_ptr<SortStrategy> strategy;

    public:
        void set_strategy(std::unique_ptr<SortStrategy> new_strategy) {
            strategy = std::move(new_strategy);
        }

        void execute_sort(std::vector<int>& data) {
            if (strategy) {
                strategy->sort(data);
            }
        }
    };

    void enhanced_strategy_demo() {
        std::cout << "\n=== 增强策略模式演示 ===" << std::endl;
        SortContext context;
        std::vector<int> data1 = {64, 34, 25, 12, 22, 11, 90};
        std::vector<int> data2 = {64, 34, 25, 12, 22, 11, 90};

        std::cout << "原始数据1: ";
        for (int n : data1) std::cout << n << " ";
        std::cout << std::endl;

        context.set_strategy(std::make_unique<BubbleSort>());
        context.execute_sort(data1);

        std::cout << "排序后数据1: ";
        for (int n : data1) std::cout << n << " ";
        std::cout << std::endl;

        std::cout << "\n原始数据2: ";
        for (int n : data2) std::cout << n << " ";
        std::cout << std::endl;

        context.set_strategy(std::make_unique<QuickSort>());
        context.execute_sort(data2);

        std::cout << "排序后数据2: ";
        for (int n : data2) std::cout << n << " ";
        std::cout << std::endl;
    }

    // 运行所有演示
    void run_demo() {
        std::cout << "=== 高级设计模式演示 ===" << std::endl;
        command_pattern_demo();
        chain_of_responsibility_demo();
        visitor_pattern_demo();
        state_pattern_demo();
        template_method_demo();
        enhanced_strategy_demo();
    }
}

#endif //CPP_LEARNING_DEMO_ADVANCED_DESIGN_PATTERNS_DEMO_H