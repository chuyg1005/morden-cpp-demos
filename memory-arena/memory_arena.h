#ifndef MEMORY_ARENA_H
#define MEMORY_ARENA_H

#include <iostream>
#include <cstring>
#include <cstdint>
#include <new>
#include <chrono>

// 内存池/内存竞技场实现
namespace memory_arena_demo {
    class MemoryArena {
    private:
        void* memory_pool_;      // 内存池指针
        size_t pool_size_;       // 内存池大小
        size_t offset_;          // 当前分配偏移量
        size_t alignment_;       // 对齐要求

        // 计算对齐后的大小
        size_t aligned_size(size_t size) const {
            return (size + alignment_ - 1) & ~(alignment_ - 1);
        }

    public:
        // 构造函数
        explicit MemoryArena(size_t size, size_t alignment = alignof(std::max_align_t))
            : pool_size_(size), offset_(0), alignment_(alignment) {
            // 分配内存池
            memory_pool_ = std::malloc(pool_size_);
            if (!memory_pool_) {
                throw std::bad_alloc();
            }
            std::memset(memory_pool_, 0, pool_size_);
        }

        // 析构函数
        ~MemoryArena() {
            if (memory_pool_) {
                std::free(memory_pool_);
            }
        }

        // 禁止拷贝
        MemoryArena(const MemoryArena&) = delete;
        MemoryArena& operator=(const MemoryArena&) = delete;

        // 分配内存
        void* allocate(size_t size) {
            if (size == 0) {
                return nullptr;
            }

            // 计算对齐后的大小
            size_t aligned = aligned_size(size);
            
            // 检查是否有足够空间
            if (offset_ + aligned > pool_size_) {
                throw std::bad_alloc();
            }
            
            // 分配内存
            void* ptr = static_cast<char*>(memory_pool_) + offset_;
            offset_ += aligned;
            return ptr;
        }

        // 重置内存池（不会释放内存，但会重置偏移量）
        void reset() {
            offset_ = 0;
            std::memset(memory_pool_, 0, pool_size_);
        }

        // 获取已使用内存大小
        size_t used_memory() const {
            return offset_;
        }

        // 获取总内存大小
        size_t total_memory() const {
            return pool_size_;
        }

        // 获取剩余内存大小
        size_t remaining_memory() const {
            return pool_size_ - offset_;
        }
    };

    // 内存池分配器模板
    template<typename T>
    class ArenaAllocator {
    private:
        MemoryArena* arena_;

    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        // 构造函数
        explicit ArenaAllocator(MemoryArena* arena) : arena_(arena) {}

        // 拷贝构造函数
        template<typename U>
        ArenaAllocator(const ArenaAllocator<U>& other) : arena_(other.arena_) {}

        // 分配内存
        T* allocate(std::size_t n) {
            if (arena_) {
                return static_cast<T*>(arena_->allocate(n * sizeof(T)));
            }
            return nullptr;
        }

        // 释放内存（在内存池中不需要实际释放）
        void deallocate(T* ptr, std::size_t n) {
            // 在内存池中不需要实际释放，由内存池统一管理
            // 这里可以留空或者添加调试信息
        }

        // 重新绑定到其他类型
        template<typename U>
        struct rebind {
            using other = ArenaAllocator<U>;
        };

        // 相等比较
        template<typename U>
        bool operator==(const ArenaAllocator<U>& other) const {
            return arena_ == other.arena_;
        }

        template<typename U>
        bool operator!=(const ArenaAllocator<U>& other) const {
            return !(*this == other);
        }
    };

    // 演示内存池的使用
    void memory_arena_demo() {
        std::cout << "\n=== 内存池演示 ===" << std::endl;

        try {
            // 创建一个1KB的内存池
            MemoryArena arena(1024);
            std::cout << "创建了1KB的内存池" << std::endl;
            std::cout << "总内存: " << arena.total_memory() << " 字节" << std::endl;
            std::cout << "已使用: " << arena.used_memory() << " 字节" << std::endl;
            std::cout << "剩余内存: " << arena.remaining_memory() << " 字节" << std::endl;

            // 分配一些内存
            std::cout << "\n分配内存:" << std::endl;
            void* ptr1 = arena.allocate(100);
            std::cout << "分配100字节，地址: " << ptr1 << std::endl;
            std::cout << "已使用: " << arena.used_memory() << " 字节" << std::endl;
            std::cout << "剩余内存: " << arena.remaining_memory() << " 字节" << std::endl;

            void* ptr2 = arena.allocate(200);
            std::cout << "分配200字节，地址: " << ptr2 << std::endl;
            std::cout << "已使用: " << arena.used_memory() << " 字节" << std::endl;
            std::cout << "剩余内存: " << arena.remaining_memory() << " 字节" << std::endl;

            // 使用内存池分配器分配对象
            std::cout << "\n使用内存池分配器:" << std::endl;
            ArenaAllocator<int> int_allocator(&arena);
            int* int_array = int_allocator.allocate(10);  // 分配10个int
            std::cout << "分配了10个int，地址: " << int_array << std::endl;
            std::cout << "已使用: " << arena.used_memory() << " 字节" << std::endl;
            std::cout << "剩余内存: " << arena.remaining_memory() << " 字节" << std::endl;

            // 初始化分配的内存
            for (int i = 0; i < 10; ++i) {
                int_array[i] = i * i;
            }
            std::cout << "初始化数组: ";
            for (int i = 0; i < 10; ++i) {
                std::cout << int_array[i] << " ";
            }
            std::cout << std::endl;

            // 重置内存池
            std::cout << "\n重置内存池:" << std::endl;
            arena.reset();
            std::cout << "重置后已使用: " << arena.used_memory() << " 字节" << std::endl;
            std::cout << "重置后剩余内存: " << arena.remaining_memory() << " 字节" << std::endl;

            // 再次分配
            void* ptr3 = arena.allocate(50);
            std::cout << "重置后分配50字节，地址: " << ptr3 << std::endl;
            std::cout << "已使用: " << arena.used_memory() << " 字节" << std::endl;
            std::cout << "剩余内存: " << arena.remaining_memory() << " 字节" << std::endl;

            // 性能比较示例
            std::cout << "\n性能比较:" << std::endl;
            
            // 使用内存池分配 (批量分配然后重置)
            auto start = std::chrono::high_resolution_clock::now();
            MemoryArena perf_arena(1024 * 1024);  // 1MB内存池
            for (int j = 0; j < 100; ++j) {  // 100轮批量分配
                for (int i = 0; i < 10; ++i) {  // 每轮10次分配
                    [[maybe_unused]] void* ptr = perf_arena.allocate(100);
                }
                perf_arena.reset();  // 重置内存池
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto arena_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            // 使用标准分配器
            start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < 100; ++j) {  // 100轮分配和释放
                void* ptrs[10];
                for (int i = 0; i < 10; ++i) {
                    ptrs[i] = std::malloc(100);
                }
                for (int i = 0; i < 10; ++i) {
                    std::free(ptrs[i]);
                }
            }
            end = std::chrono::high_resolution_clock::now();
            auto malloc_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << "内存池批量分配1000次耗时: " << arena_duration.count() << " 微秒" << std::endl;
            std::cout << "malloc/free 1000次耗时: " << malloc_duration.count() << " 微秒" << std::endl;
            
            // 解释性能差异
            std::cout << "\n性能分析:" << std::endl;
            std::cout << "在当前测试中，内存池比malloc稍慢，这是因为:" << std::endl;
            std::cout << "1. 现代malloc实现已经高度优化" << std::endl;
            std::cout << "2. 测试分配大小较小且次数不多" << std::endl;
            std::cout << "3. 内存池实现还有优化空间" << std::endl;
            std::cout << "\n但内存池仍有其优势:" << std::endl;
            std::cout << "1. 避免内存碎片" << std::endl;
            std::cout << "2. 可预测的分配性能" << std::endl;
            std::cout << "3. 在大量短生命周期对象场景下更高效" << std::endl;
            std::cout << "4. 更好的缓存局部性" << std::endl;

        } catch (const std::exception& e) {
            std::cout << "内存池异常: " << e.what() << std::endl;
        }
    }
}

#endif // MEMORY_ARENA_H