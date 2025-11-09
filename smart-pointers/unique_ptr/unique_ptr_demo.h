#ifndef UNIQUE_PTR_DEMO_H
#define UNIQUE_PTR_DEMO_H

#include "../smart_pointers_base.h"

// 演示unique_ptr的使用
namespace smart_pointers_demo {
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
}

#endif // UNIQUE_PTR_DEMO_H