#ifndef VARIADIC_TEMPLATES_DEMO_H
#define VARIADIC_TEMPLATES_DEMO_H

#include "variadic_templates_base.h"

// 运行variadic_templates演示
namespace variadic_templates_demo {
    inline void run_demo() {
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