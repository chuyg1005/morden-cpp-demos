#ifndef SMART_POINTERS_BASE_H
#define SMART_POINTERS_BASE_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// 智能指针基础类和通用功能
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

    // 循环引用示例中使用的Node类
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
}

#endif // SMART_POINTERS_BASE_H