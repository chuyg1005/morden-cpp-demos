#ifndef VARIADIC_TEMPLATES_DEMO_H
#define VARIADIC_TEMPLATES_DEMO_H

#include <iostream>
#include <string>
#include <type_traits>

// Demonstrate variadic templates
namespace variadic_templates_demo {
    // Base case for variadic template recursion
    void print() {
        std::cout << std::endl;
    }

    // Recursive case for variadic template
    template<typename T, typename... Args>
    void print(T&& first, Args&&... args) {
        std::cout << first;
        if constexpr (sizeof...(args) > 0) {
            std::cout << " ";
        }
        print(args...);
    }

    // Calculate sum using variadic templates
    template<typename T>
    std::enable_if_t<std::is_arithmetic_v<std::decay_t<T>>, T>
    sum(T&& value) {
        return value;
    }

    template<typename T, typename... Args>
    std::enable_if_t<std::is_arithmetic_v<std::decay_t<T>>, std::decay_t<T>>
    sum(T&& first, Args&&... args) {
        return first + sum(args...);
    }

    // Type list implementation using variadic templates
    template<typename... Types>
    struct type_list {};

    // Get the size of a type list
    template<typename T>
    struct type_list_size;

    template<typename... Types>
    struct type_list_size<type_list<Types...>> {
        static constexpr size_t value = sizeof...(Types);
    };

    // Check if a type is in the type list
    template<typename T, typename TypeList>
    struct type_list_contains;

    template<typename T, typename... Types>
    struct type_list_contains<T, type_list<Types...>> {
        static constexpr bool value = (std::is_same_v<T, Types> || ...);
    };
    
    // 运行variadic_templates演示
    inline void run_meta_programming_demo() {
        std::cout << "\n1.5 可变参数模板演示:" << std::endl;
        print("Hello", "World", 42, 3.14);
        
        auto sum_result = sum(1, 2, 3, 4, 5);
        std::cout << "Sum of 1,2,3,4,5 = " << sum_result << std::endl;
        
        // Type list demo
        using my_types = type_list<int, double, std::string>;
        constexpr size_t type_count = type_list_size<my_types>::value;
        constexpr bool has_int = type_list_contains<int, my_types>::value;
        constexpr bool has_float = type_list_contains<float, my_types>::value;
        
        std::cout << "Type list contains " << type_count << " types" << std::endl;
        std::cout << "Contains int: " << std::boolalpha << has_int << std::endl;
        std::cout << "Contains float: " << std::boolalpha << has_float << std::endl;
    }
}

#endif // VARIADIC_TEMPLATES_DEMO_H