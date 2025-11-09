#ifndef SFINAE_BASE_H
#define SFINAE_BASE_H

#include <iostream>
#include <type_traits>
#include <vector>

// SFINAE基础功能
namespace sfinae_demo {
    // 辅助结构体，用于检查类型是否有size()方法
    template<typename T>
    struct has_size {
    private:
        // 如果T有size()方法，会选择这个函数
        template<typename U>
        static auto test(int) -> decltype(std::declval<U>().size(), std::true_type{});
        
        // 如果上面的函数失败，这是备选方案
        template<typename>
        static std::false_type test(...);
        
    public:
        static constexpr bool value = decltype(test<T>(0))::value;
    };

    // 适用于有size()方法的类型的函数
    template<typename T>
    typename std::enable_if<has_size<T>::value, void>::type
    print_size(const T& container) {
        std::cout << "大小: " << container.size() << std::endl;
    }

    // 适用于没有size()方法的类型的函数
    template<typename T>
    typename std::enable_if<!has_size<T>::value, void>::type
    print_size(const T& value) {
        std::cout << "类型没有size()方法" << std::endl;
    }

    // 另一个SFINAE示例 - 检查是否有operator+
    template<typename T>
    struct has_plus_operator {
    private:
        template<typename U>
        static auto test(int) -> decltype(std::declval<U>() + std::declval<U>(), std::true_type{});
        
        template<typename>
        static std::false_type test(...);
        
    public:
        static constexpr bool value = decltype(test<T>(0))::value;
    };

    // 适用于支持加法运算的类型的函数
    template<typename T>
    typename std::enable_if<has_plus_operator<T>::value, T>::type
    add_if_possible(const T& a, const T& b) {
        return a + b;
    }

    // 适用于不支持加法运算的类型的函数
    template<typename T>
    typename std::enable_if<!has_plus_operator<T>::value, T>::type
    add_if_possible(const T& a, const T& b) {
        std::cout << "此类型不支持加法运算" << std::endl;
        return a;
    }
}

#endif // SFINAE_BASE_H