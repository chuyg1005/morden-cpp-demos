#ifndef TYPE_TRAITS_DEMO_H
#define TYPE_TRAITS_DEMO_H

#include "type_traits_base.h"
#include <typeinfo>

// 运行type_traits演示
namespace type_traits_demo {
    inline void run_demo() {
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