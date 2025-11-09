#ifndef TYPE_TRAITS_BASE_H
#define TYPE_TRAITS_BASE_H

#include <type_traits>
#include <iostream>

// 基础类型特征功能
namespace type_traits_demo {
    // 仅接受整数类型的函数
    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, void>::type
    process_integral(T value) {
        std::cout << "处理整数值: " << value << std::endl;
    }

    // 仅接受浮点类型的函数
    template<typename T>
    typename std::enable_if<std::is_floating_point<T>::value, void>::type
    process_floating_point(T value) {
        std::cout << "处理浮点值: " << value << std::endl;
    }

    // 移除const限定符的函数
    template<typename T>
    void print_without_const(const T& value) {
        // std::remove_const<T>::type 给我们非const版本
        std::cout << "值: " << value << std::endl;
    }

    // 编译时条件类型选择
    template<typename T>
    struct conditional_type {
        using type = typename std::conditional<
            std::is_integral<T>::value,
            long long,  // 如果T是整数类型，使用long long
            double      // 否则使用double
        >::type;
    };
}

#endif // TYPE_TRAITS_BASE_H