#ifndef SINGLETON_PATTERN_H
#define SINGLETON_PATTERN_H

#include "../design_patterns_base.h"

// 单例模式 (Singleton Pattern)
namespace design_patterns_demo {
    class Singleton {
    private:
        static std::unique_ptr<Singleton> instance_;
        static std::mutex mutex_;

        // 私有构造函数
        Singleton() {
            std::cout << "Singleton实例已创建" << std::endl;
        }

    public:
        // 禁止拷贝
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        // 获取实例
        static Singleton* getInstance() {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!instance_) {
                instance_ = std::unique_ptr<Singleton>(new Singleton());
            }
            return instance_.get();
        }

        void doSomething() {
            std::cout << "执行某些操作" << std::endl;
        }
    };

    // 静态成员定义
    std::unique_ptr<Singleton> Singleton::instance_ = nullptr;
    std::mutex Singleton::mutex_;

    void singleton_demo() {
        std::cout << "\n=== 单例模式演示 ===" << std::endl;
        
        // 获取单例实例
        Singleton* s1 = Singleton::getInstance();
        Singleton* s2 = Singleton::getInstance();
        
        // 验证是否为同一实例
        std::cout << "s1地址: " << s1 << std::endl;
        std::cout << "s2地址: " << s2 << std::endl;
        std::cout << "是否为同一实例: " << std::boolalpha << (s1 == s2) << std::endl;
        
        s1->doSomething();
    }
}

#endif // SINGLETON_PATTERN_H