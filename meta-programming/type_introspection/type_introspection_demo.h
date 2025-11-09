#ifndef TYPE_INTROSPECTION_DEMO_H
#define TYPE_INTROSPECTION_DEMO_H

#include "type_introspection_base.h"

// 运行type_introspection演示
namespace type_introspection_demo {
    inline void run_demo() {
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