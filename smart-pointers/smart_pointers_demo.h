#ifndef SMART_POINTERS_DEMO_H
#define SMART_POINTERS_DEMO_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// 演示智能指针的使用
namespace smart_pointers_demo {
    class Resource {
    private:
        std::string name_;

    public:
        explicit Resource(const std::string& name) : name_(name) {
            std::cout << "资源 " << name_ << " 已创建" << std::endl;
        }

        ~Resource() {
            std::cout << "资源 " << name_ << " 已销毁" << std::endl;
        }

        const std::string& getName() const {
            return name_;
        }

        void use() const {
            std::cout << "正在使用资源 " << name_ << std::endl;
        }
    };

    // 演示unique_ptr的使用
    void unique_ptr_demo() {
        std::cout << "\n=== unique_ptr 演示 ===" << std::endl;
        
        // 创建unique_ptr
        std::unique_ptr<Resource> ptr1 = std::make_unique<Resource>("Resource1");
        
        // 使用资源
        ptr1->use();
        
        // 转移所有权
        std::unique_ptr<Resource> ptr2 = std::move(ptr1);
        
        // 现在ptr1为空
        if (!ptr1) {
            std::cout << "ptr1 现在为空" << std::endl;
        }
        
        // ptr2拥有资源
        ptr2->use();
        
        // 作用域结束时自动释放资源
    }

    // 演示shared_ptr的使用
    void shared_ptr_demo() {
        std::cout << "\n=== shared_ptr 演示 ===" << std::endl;
        
        // 创建shared_ptr
        std::shared_ptr<Resource> ptr1 = std::make_shared<Resource>("SharedResource");
        
        // 检查引用计数
        std::cout << "引用计数: " << ptr1.use_count() << std::endl;
        
        // 创建另一个shared_ptr指向同一资源
        std::shared_ptr<Resource> ptr2 = ptr1;
        
        // 引用计数增加
        std::cout << "引用计数: " << ptr1.use_count() << std::endl;
        
        // 使用资源
        ptr1->use();
        ptr2->use();
        
        // 作用域结束时，引用计数减少
    }

    // 演示weak_ptr的使用
    void weak_ptr_demo() {
        std::cout << "\n=== weak_ptr 演示 ===" << std::endl;
        
        // 创建shared_ptr
        std::shared_ptr<Resource> shared = std::make_shared<Resource>("WeakResource");
        
        // 创建weak_ptr
        std::weak_ptr<Resource> weak = shared;
        
        // 检查资源是否仍然存在
        if (auto locked = weak.lock()) {
            std::cout << "资源仍然存在: " << locked->getName() << std::endl;
        } else {
            std::cout << "资源已被销毁" << std::endl;
        }
        
        // 释放shared_ptr
        shared.reset();
        
        // 再次检查
        if (auto locked = weak.lock()) {
            std::cout << "资源仍然存在: " << locked->getName() << std::endl;
        } else {
            std::cout << "资源已被销毁" << std::endl;
        }
    }

    // 演示循环引用问题及解决方案
    class Node {
    public:
        std::string name;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> parent;  // 使用weak_ptr避免循环引用

        Node(const std::string& n) : name(n) {
            std::cout << "节点 " << name << " 已创建" << std::endl;
        }

        ~Node() {
            std::cout << "节点 " << name << " 已销毁" << std::endl;
        }
    };

    void circular_reference_demo() {
        std::cout << "\n=== 循环引用演示 ===" << std::endl;
        
        {
            auto parent = std::make_shared<Node>("Parent");
            auto child = std::make_shared<Node>("Child");
            
            // 建立关系
            parent->next = child;
            child->parent = parent;  // 使用weak_ptr
            
            // 检查引用计数
            std::cout << "Parent引用计数: " << parent.use_count() << std::endl;
            std::cout << "Child引用计数: " << child.use_count() << std::endl;
        }
        // 作用域结束，对象正确销毁
    }
}

#endif // SMART_POINTERS_DEMO_H