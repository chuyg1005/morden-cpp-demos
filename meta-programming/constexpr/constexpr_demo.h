#ifndef CONSTEXPR_DEMO_H
#define CONSTEXPR_DEMO_H

#include "constexpr_base.h"

// 运行constexpr演示
namespace constexpr_demo {
    inline void run_demo() {
        std::cout << "\n1.4 Constexpr演示:" << std::endl;
        constexpr auto fact5 = factorial(5);
        constexpr auto pow2_10 = power(2, 10);
        
        std::cout << "5! = " << fact5 << std::endl;
        std::cout << "2^10 = " << pow2_10 << std::endl;
        
        std::cout << "First 10 Fibonacci numbers:" << std::endl;
        for (int i = 0; i < 10; ++i) {
            std::cout << fibonacci_array[i] << " ";
        }
        std::cout << std::endl;
    }
}

#endif // CONSTEXPR_DEMO_H