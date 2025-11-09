#ifndef SHARED_PTR_DEMO_H
#define SHARED_PTR_DEMO_H

#include "../smart_pointers_base.h"

// 演示shared_ptr的使用
namespace smart_pointers_demo {
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
}

#endif // SHARED_PTR_DEMO_H