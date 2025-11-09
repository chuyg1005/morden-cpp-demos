#ifndef IMPROVED_MEMORY_ARENA_H
#define IMPROVED_MEMORY_ARENA_H

#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <new>
#include <chrono>
#include <cstring>

// 改进的内存池/内存竞技场实现
namespace improved_memory_arena_demo {
    class ImprovedMemoryArena {
    private:
        struct MemoryBlock {
            void* ptr;
            size_t size;
            size_t offset;
            
            MemoryBlock(size_t block_size) 
                : size(block_size), offset(0) {
                ptr = std::malloc(size);
                if (!ptr) {
                    throw std::bad_alloc();
                }
            }
            
            ~MemoryBlock() {
                if (ptr) {
                    std::free(ptr);
                }
            }
            
            // 禁止拷贝
            MemoryBlock(const MemoryBlock&) = delete;
            MemoryBlock& operator=(const MemoryBlock&) = delete;
            
            // 支持移动
            MemoryBlock(MemoryBlock&& other) noexcept 
                : ptr(other.ptr), size(other.size), offset(other.offset) {
                other.ptr = nullptr;
                other.size = 0;
                other.offset = 0;
            }
            
            MemoryBlock& operator=(MemoryBlock&& other) noexcept {
                if (this != &other) {
                    if (ptr) {
                        std::free(ptr);
                    }
                    ptr = other.ptr;
                    size = other.size;
                    offset = other.offset;
                    other.ptr = nullptr;
                    other.size = 0;
                    other.offset = 0;
                }
                return *this;
            }
        };
        
        size_t block_size_;  // 每个内存块的大小
        std::list<MemoryBlock> blocks_;  // 内存块列表
        size_t alignment_;   // 对齐要求
        
        // 计算对齐后的大小
        size_t aligned_size(size_t size) const {
            return (size + alignment_ - 1) & ~(alignment_ - 1);
        }
        
        // 确保有可用的内存块
        void ensure_block() {
            if (blocks_.empty() || blocks_.back().offset >= blocks_.back().size) {
                blocks_.emplace_back(block_size_);
            }
        }
        
    public:
        // 构造函数
        explicit ImprovedMemoryArena(size_t block_size, size_t alignment = alignof(std::max_align_t))
            : block_size_(block_size), alignment_(alignment) {
            // 初始化第一个内存块
            blocks_.emplace_back(block_size_);
        }
        
        // 析构函数
        ~ImprovedMemoryArena() = default;
        
        // 禁止拷贝
        ImprovedMemoryArena(const ImprovedMemoryArena&) = delete;
        ImprovedMemoryArena& operator=(const ImprovedMemoryArena&) = delete;
        
        // 分配内存
        void* allocate(size_t size) {
            if (size == 0) {
                return nullptr;
            }
            
            // 计算对齐后的大小
            size_t aligned = aligned_size(size);
            
            // 如果请求的大小大于块大小，直接分配一个独立的块
            if (aligned > block_size_) {
                // 创建一个专门用于此分配的块
                blocks_.emplace_back(aligned);
                MemoryBlock& new_block = blocks_.back();
                void* ptr = new_block.ptr;
                new_block.offset = aligned;  // 标记为已完全使用
                return ptr;
            }
            
            // 确保有可用的内存块
            ensure_block();
            
            // 尝试在当前块中分配
            MemoryBlock& current_block = blocks_.back();
            if (current_block.offset + aligned <= current_block.size) {
                void* ptr = static_cast<char*>(current_block.ptr) + current_block.offset;
                current_block.offset += aligned;
                return ptr;
            }
            
            // 当前块空间不足，创建新块
            blocks_.emplace_back(block_size_);
            MemoryBlock& new_block = blocks_.back();
            void* ptr = new_block.ptr;
            new_block.offset = aligned;
            return ptr;
        }
        
        // 重置内存池（不会释放内存块，但会重置所有块的偏移量）
        void reset() {
            for (auto& block : blocks_) {
                block.offset = 0;
            }
        }
        
        // 获取总内存块数
        size_t block_count() const {
            return blocks_.size();
        }
        
        // 获取总分配内存大小
        size_t total_allocated() const {
            size_t total = 0;
            for (const auto& block : blocks_) {
                total += block.offset;
            }
            return total;
        }
    };
    
    // 使用内存池的示例类
    class ExampleObject {
    private:
        int id_;
        double value_;
        char name_[32];
        
    public:
        ExampleObject(int id, double value, const char* name) 
            : id_(id), value_(value) {
            std::strncpy(name_, name, sizeof(name_) - 1);
            name_[sizeof(name_) - 1] = '\0';
        }
        
        void print() const {
            std::cout << "Object ID: " << id_ << ", Value: " << value_ 
                      << ", Name: " << name_ << std::endl;
        }
        
        int getId() const { return id_; }
        double getValue() const { return value_; }
    };
    
    // 内存池分配器模板
    template<typename T>
    class ImprovedArenaAllocator {
    private:
        ImprovedMemoryArena* arena_;
        
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        
        // 构造函数
        explicit ImprovedArenaAllocator(ImprovedMemoryArena* arena) : arena_(arena) {}
        
        // 拷贝构造函数
        template<typename U>
        ImprovedArenaAllocator(const ImprovedArenaAllocator<U>& other) : arena_(other.arena_) {}
        
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
        }
        
        // 重新绑定到其他类型
        template<typename U>
        struct rebind {
            using other = ImprovedArenaAllocator<U>;
        };
        
        // 相等比较
        template<typename U>
        bool operator==(const ImprovedArenaAllocator<U>& other) const {
            return arena_ == other.arena_;
        }
        
        template<typename U>
        bool operator!=(const ImprovedArenaAllocator<U>& other) const {
            return !(*this == other);
        }
    };
    
    // 演示改进的内存池的使用
    void improved_memory_arena_demo() {
        std::cout << "\n=== 改进的内存池演示 ===" << std::endl;
        
        try {
            // 创建一个改进的内存池，块大小为512字节
            ImprovedMemoryArena arena(512);
            std::cout << "创建了块大小为512字节的内存池" << std::endl;
            std::cout << "初始内存块数: " << arena.block_count() << std::endl;
            
            // 分配一些小对象
            std::cout << "\n分配小对象:" << std::endl;
            void* ptr1 = arena.allocate(100);
            std::cout << "分配100字节，地址: " << ptr1 << std::endl;
            
            void* ptr2 = arena.allocate(200);
            std::cout << "分配200字节，地址: " << ptr2 << std::endl;
            
            std::cout << "当前内存块数: " << arena.block_count() << std::endl;
            std::cout << "总分配内存: " << arena.total_allocated() << " 字节" << std::endl;
            
            // 分配一个大对象（超过块大小）
            std::cout << "\n分配大对象:" << std::endl;
            void* ptr3 = arena.allocate(1000);  // 超过512字节
            std::cout << "分配1000字节，地址: " << ptr3 << std::endl;
            std::cout << "分配后内存块数: " << arena.block_count() << std::endl;
            std::cout << "总分配内存: " << arena.total_allocated() << " 字节" << std::endl;
            
            // 使用内存池分配器分配对象
            std::cout << "\n使用内存池分配器:" << std::endl;
            ImprovedArenaAllocator<ExampleObject> obj_allocator(&arena);
            
            // 使用就地构造创建对象
            void* obj_memory = obj_allocator.allocate(1);
            ExampleObject* obj = new(obj_memory) ExampleObject(1, 3.14, "TestObject");
            std::cout << "就地构造对象，地址: " << obj << std::endl;
            obj->print();
            
            std::cout << "当前内存块数: " << arena.block_count() << std::endl;
            std::cout << "总分配内存: " << arena.total_allocated() << " 字节" << std::endl;
            
            // 重置内存池
            std::cout << "\n重置内存池:" << std::endl;
            arena.reset();
            std::cout << "重置后内存块数: " << arena.block_count() << std::endl;
            std::cout << "重置后总分配内存: " << arena.total_allocated() << " 字节" << std::endl;
            
            // 再次分配
            void* ptr4 = arena.allocate(50);
            std::cout << "重置后分配50字节，地址: " << ptr4 << std::endl;
            std::cout << "总分配内存: " << arena.total_allocated() << " 字节" << std::endl;
            
            // 性能比较示例
            std::cout << "\n性能比较:" << std::endl;
            
            // 使用改进的内存池分配
            auto start = std::chrono::high_resolution_clock::now();
            ImprovedMemoryArena perf_arena(1024);  // 1KB块大小
            std::vector<void*> arena_ptrs;
            for (int i = 0; i < 1000; ++i) {
                arena_ptrs.push_back(perf_arena.allocate(100));
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto arena_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            // 使用标准分配器
            start = std::chrono::high_resolution_clock::now();
            std::vector<void*> malloc_ptrs;
            for (int i = 0; i < 1000; ++i) {
                malloc_ptrs.push_back(std::malloc(100));
            }
            end = std::chrono::high_resolution_clock::now();
            auto malloc_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            // 释放内存
            for (auto ptr : malloc_ptrs) {
                std::free(ptr);
            }
            
            std::cout << "改进内存池分配1000次耗时: " << arena_duration.count() << " 微秒" << std::endl;
            std::cout << "malloc 1000次耗时: " << malloc_duration.count() << " 微秒" << std::endl;
            if (malloc_duration.count() > 0) {
                double speedup = static_cast<double>(malloc_duration.count()) / arena_duration.count();
                std::cout << "性能提升: " << speedup << "x" << std::endl;
            }
            
            std::cout << "内存池使用的块数: " << perf_arena.block_count() << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "内存池异常: " << e.what() << std::endl;
        }
    }
}

#endif // IMPROVED_MEMORY_ARENA_H