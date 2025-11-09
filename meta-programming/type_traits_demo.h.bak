#ifndef TYPE_TRAITS_DEMO_H
#define TYPE_TRAITS_DEMO_H

#include <type_traits>
#include <iostream>

// 演示使用类型特征进行编译时类型检查
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
    
    // 运行type_traits演示
    inline void run_meta_programming_demo() {
        std::cout << "\n1.1 类型特征演示:" << std::endl;
        process_integral(42);
        process_floating_point(3.14);
        print_without_const(100);
        
        // Show conditional type selection
        conditional_type<int>::type int_value = 10;
        conditional_type<double>::type double_value = 3.14;
        std::cout << "Conditional type for int: " << typeid(int_value).name() << std::endl;
        std::cout << "Conditional type for double: " << typeid(double_value).name() << std::endl;
    }
}

#endif // TYPE_TRAITS_DEMO_H