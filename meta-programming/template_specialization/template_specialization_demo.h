#ifndef TEMPLATE_SPECIALIZATION_DEMO_H
#define TEMPLATE_SPECIALIZATION_DEMO_H

#include "template_specialization_base.h"

// 运行template_specialization演示
namespace template_specialization_demo {
    inline void run_demo() {
        std::cout << "\n1.2 模板特化演示:" << std::endl;
        int int_val = 42;
        std::string str_val = "Hello";
        double double_value = 3.14;
        double* ptr_val = &double_value;
        std::vector<int> vec_val = {1, 2, 3, 4, 5};
        
        TypeInfo<int>::print_info(int_val);
        TypeInfo<std::string>::print_info(str_val);
        TypeInfo<double*>::print_info(ptr_val);
        TypeInfo<std::vector<int>>::print_info(vec_val);
    }
}

#endif // TEMPLATE_SPECIALIZATION_DEMO_H