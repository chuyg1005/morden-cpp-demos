#ifndef CPP_LEARNING_DEMO_MEMORY_LEAK_DETECTION_DEMO_H
#define CPP_LEARNING_DEMO_MEMORY_LEAK_DETECTION_DEMO_H

#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>

#ifdef _MSC_VER
// Windows平台内存泄漏检测
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

namespace memory_leak_detection_demo {
    // 内存泄漏示例类
    class LeakExample {
    public:
        int* data;
        
        LeakExample(size_t size) {
            data = new int[size];
            std::cout << "分配了 " << size << " 个整数的内存" << std::endl;
        }
        
        ~LeakExample() {
            delete[] data;
            std::cout << "释放了内存" << std::endl;
        }
        
        // 模拟忘记释放内存的情况
        void simulate_leak() {
            int* leak_data = new int[100];
            std::cout << "分配了可能泄漏的内存" << std::endl;
            // 忘记调用 delete[] leak_data;
        }
    };
    
    // 智能指针示例 - 推荐的内存管理方式
    void smart_pointer_demo() {
        std::cout << "\n=== 智能指针内存管理演示 ===" << std::endl;
        
        // unique_ptr自动管理内存
        {
            std::unique_ptr<int[]> ptr(new int[10]);
            std::cout << "使用unique_ptr分配内存" << std::endl;
            // 离开作用域时自动释放内存
        }
        std::cout << "unique_ptr自动释放了内存" << std::endl;
        
        // shared_ptr共享所有权
        {
            std::shared_ptr<int[]> shared1(new int[5]);
            {
                std::shared_ptr<int[]> shared2 = shared1;
                std::cout << "shared_ptr引用计数: " << shared1.use_count() << std::endl;
            }
            std::cout << "一个shared_ptr离开作用域，引用计数: " << shared1.use_count() << std::endl;
            // 当最后一个shared_ptr离开作用域时释放内存
        }
        std::cout << "所有shared_ptr离开作用域，内存已释放" << std::endl;
    }
    
    // 循环引用示例
    class Node {
    public:
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> parent;  // 使用weak_ptr避免循环引用
        int value;
        
        Node(int val) : value(val) {}
        
        ~Node() {
            std::cout << "销毁节点，值为: " << value << std::endl;
        }
    };
    
    void circular_reference_demo() {
        std::cout << "\n=== 循环引用演示 ===" << std::endl;
        
        // 使用shared_ptr可能导致循环引用
        {
            auto node1 = std::make_shared<Node>(1);
            auto node2 = std::make_shared<Node>(2);
            
            node1->next = node2;
            // 使用weak_ptr避免循环引用
            node2->parent = node1;
            
            std::cout << "节点1引用计数: " << node1.use_count() << std::endl;
            std::cout << "节点2引用计数: " << node2.use_count() << std::endl;
        }
        // 离开作用域后，节点应该被正确销毁
        std::cout << "离开作用域，节点应该已被销毁" << std::endl;
    }
    
    // 内存池示例
    class SimpleMemoryPool {
    private:
        std::vector<std::unique_ptr<char[]>> blocks;
        size_t block_size;
        size_t current_block;
        size_t offset_in_block;
        
    public:
        explicit SimpleMemoryPool(size_t block_sz = 1024) 
            : block_size(block_sz), current_block(0), offset_in_block(0) {
            blocks.push_back(std::make_unique<char[]>(block_size));
        }
        
        void* allocate(size_t size) {
            if (offset_in_block + size > block_size) {
                // 当前块空间不足，分配新块
                blocks.push_back(std::make_unique<char[]>(block_size));
                current_block++;
                offset_in_block = 0;
            }
            
            void* ptr = blocks[current_block].get() + offset_in_block;
            offset_in_block += size;
            return ptr;
        }
        
        // 内存池不需要单独释放内存，整体一起释放
        ~SimpleMemoryPool() {
            std::cout << "内存池销毁，所有分配的内存自动释放" << std::endl;
        }
    };
    
    void memory_pool_demo() {
        std::cout << "\n=== 内存池演示 ===" << std::endl;
        
        SimpleMemoryPool pool(256);
        
        // 从内存池分配内存
        void* ptr1 = pool.allocate(64);
        void* ptr2 = pool.allocate(32);
        void* ptr3 = pool.allocate(128);
        
        std::cout << "从内存池分配了3块内存" << std::endl;
        std::cout << "指针1地址: " << ptr1 << std::endl;
        std::cout << "指针2地址: " << ptr2 << std::endl;
        std::cout << "指针3地址: " << ptr3 << std::endl;
        
        // 离开作用域时，内存池自动释放所有内存
    }
    
    // 内存泄漏检测工具示例
    void memory_leak_detection_demo() {
        std::cout << "\n=== 内存泄漏检测演示 ===" << std::endl;
        
#ifdef _MSC_VER
        // Windows平台内存泄漏检测
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
        
        // 正确管理内存的示例
        {
            LeakExample example(100);
        }
        
        // 可能导致内存泄漏的示例
        {
            LeakExample example(50);
            example.simulate_leak();
        }
        
        std::cout << "演示完成，检查是否有内存泄漏报告" << std::endl;
    }
    
    // 自定义内存分配器示例
    template<typename T>
    class CustomAllocator {
    public:
        using value_type = T;
        
        CustomAllocator() = default;
        
        template<typename U>
        CustomAllocator(const CustomAllocator<U>&) {}
        
        T* allocate(std::size_t n) {
            std::cout << "自定义分配器: 分配 " << n << " 个 " << typeid(T).name() << " 对象" << std::endl;
            if (n > std::size_t(-1) / sizeof(T)) throw std::bad_alloc();
            if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) return p;
            else throw std::bad_alloc();
        }
        
        void deallocate(T* p, std::size_t n) {
            std::cout << "自定义分配器: 释放 " << n << " 个 " << typeid(T).name() << " 对象" << std::endl;
            std::free(p);
        }
        
        template<typename U>
        bool operator==(const CustomAllocator<U>&) const { return true; }
        
        template<typename U>
        bool operator!=(const CustomAllocator<U>&) const { return false; }
    };
    
    void custom_allocator_demo() {
        std::cout << "\n=== 自定义分配器演示 ===" << std::endl;
        
        // 使用自定义分配器的vector
        std::vector<int, CustomAllocator<int>> vec;
        vec.reserve(10);
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        
        std::cout << "Vector内容: ";
        for (const auto& item : vec) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    // 运行所有演示
    void run_demo() {
        std::cout << "=== 内存管理和泄漏检测演示 ===" << std::endl;
        smart_pointer_demo();
        circular_reference_demo();
        memory_pool_demo();
        memory_leak_detection_demo();
        custom_allocator_demo();
    }
}

#endif //CPP_LEARNING_DEMO_MEMORY_LEAK_DETECTION_DEMO_H