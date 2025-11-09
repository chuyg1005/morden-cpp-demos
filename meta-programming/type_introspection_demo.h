#ifndef TYPE_INTROSPECTION_DEMO_H
#define TYPE_INTROSPECTION_DEMO_H

#include <iostream>
#include <typeinfo>
#include <string>
#include <utility>

// Demonstrate type introspection and reflection
namespace type_introspection_demo {
    // Get type name as string (implementation-dependent)
    template<typename T>
    std::string type_name() {
        return typeid(T).name();
    }

    // Pretty print type name (GCC/Clang specific implementation)
    template<typename T>
    std::string pretty_type_name() {
        std::string name = typeid(T).name();
#ifdef __GNUG__
        // For GCC/Clang, we could demangle, but for simplicity we'll just return the name
#endif
        return name;
    }

    // Type printer using template specialization
    template<typename T>
    struct type_printer {
        static void print() {
            std::cout << "Type: " << pretty_type_name<T>() << std::endl;
        }
    };

    // Print information about a type
    template<typename T>
    void print_type_info() {
        std::cout << "Type name: " << pretty_type_name<T>() << std::endl;
        std::cout << "Size: " << sizeof(T) << " bytes" << std::endl;
        std::cout << "Alignment: " << alignof(T) << " bytes" << std::endl;
    }

    // Check if two types are the same
    template<typename T, typename U>
    struct is_same_type {
        static constexpr bool value = false;
    };

    template<typename T>
    struct is_same_type<T, T> {
        static constexpr bool value = true;
    };

    // Get member count using SFINAE (simplified example)
    template<typename T>
    struct member_counter {
        template<typename U>
        static auto check(int) -> decltype(std::declval<U>().x, std::declval<U>().y, std::true_type{});
        
        template<typename U>
        static std::false_type check(...);
        
        static constexpr bool has_two_members = decltype(check<T>(0))::value;
    };
    
    // 运行type_introspection演示
    inline void run_meta_programming_demo() {
        std::cout << "\n1.6 类型 introspection 演示:" << std::endl;
        print_type_info<int>();
        print_type_info<std::string>();
        print_type_info<std::vector<double>>();
        
        constexpr bool same_types = is_same_type<int, int>::value;
        constexpr bool diff_types = is_same_type<int, double>::value;
        
        std::cout << "int == int: " << std::boolalpha << same_types << std::endl;
        std::cout << "int == double: " << std::boolalpha << diff_types << std::endl;
    }
}

#endif // TYPE_INTROSPECTION_DEMO_H