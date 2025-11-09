#ifndef VARIADIC_TEMPLATES_BASE_H
#define VARIADIC_TEMPLATES_BASE_H

#include <iostream>
#include <string>
#include <type_traits>

// 可变参数模板基础功能
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
}

#endif // VARIADIC_TEMPLATES_BASE_H