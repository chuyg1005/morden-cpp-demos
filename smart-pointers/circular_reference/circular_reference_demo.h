#ifndef CIRCULAR_REFERENCE_DEMO_H
#define CIRCULAR_REFERENCE_DEMO_H

#include "../smart_pointers_base.h"

// 演示循环引用问题及解决方案
namespace smart_pointers_demo {
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

#endif // CIRCULAR_REFERENCE_DEMO_H