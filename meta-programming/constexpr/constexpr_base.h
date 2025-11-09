#ifndef CONSTEXPR_BASE_H
#define CONSTEXPR_BASE_H

#include <iostream>
#include <array>
#include <utility>

// Constexpr基础功能
namespace constexpr_demo {
    // Compile-time factorial calculation
    constexpr unsigned long long factorial(int n) {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    }

    // Compile-time power function
    constexpr long long power(int base, int exp) {
        return (exp == 0) ? 1 : base * power(base, exp - 1);
    }

    // Compile-time array with Fibonacci numbers
    template<int N>
    struct Fibonacci {
        static constexpr long long value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
    };

    // Template specializations for base cases
    template<>
    struct Fibonacci<0> {
        static constexpr long long value = 0;
    };

    template<>
    struct Fibonacci<1> {
        static constexpr long long value = 1;
    };

    // Generate an array of Fibonacci numbers at compile time
    template<int... Is>
    constexpr auto make_fibonacci_array(std::integer_sequence<int, Is...>) {
        return std::array<long long, sizeof...(Is)>{Fibonacci<Is>::value...};
    }

    // Create a compile-time array of the first 20 Fibonacci numbers
    constexpr auto fibonacci_array = make_fibonacci_array(std::make_integer_sequence<int, 20>{});
}

#endif // CONSTEXPR_BASE_H