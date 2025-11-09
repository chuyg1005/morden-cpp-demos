#ifndef WEAK_PTR_DEMO_H
#define WEAK_PTR_DEMO_H

#include "../smart_pointers_base.h"

// 演示weak_ptr的使用
namespace smart_pointers_demo {
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
}

#endif // WEAK_PTR_DEMO_H