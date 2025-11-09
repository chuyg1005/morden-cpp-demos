#ifndef SFINAE_DEMO_H
#define SFINAE_DEMO_H

#include "sfinae_base.h"

// 运行sfinae演示
namespace sfinae_demo {
    inline void run_demo() {
        std::cout << "\n1.3 SFINAE演示:" << std::endl;
        std::vector<int> vec = {1, 2, 3, 4, 5};
        int single_value = 42;
        
        std::cout << "For vector: ";
        print_size(vec);
        
        std::cout << "For int: ";
        print_size(single_value);
        
        // Test addition with SFINAE
        int a = 10, b = 20;
        std::string s1 = "Hello", s2 = "World";
        
        std::cout << "Adding ints: " << add_if_possible(a, b) << std::endl;
        std::cout << "Adding strings: ";
        add_if_possible(s1, s2);  // Will print message that addition is not supported
    }
}

#endif // SFINAE_DEMO_H