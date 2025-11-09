#ifndef CPP_LEARNING_DEMO_VECTOR_UTILS_H
#define CPP_LEARNING_DEMO_VECTOR_UTILS_H

#include <vector>
#include <algorithm>

namespace vector_utils {
    // 向量求和
    template<typename T>
    T sum(const std::vector<T>& vec) {
        T result = T{};
        for (const auto& element : vec) {
            result += element;
        }
        return result;
    }
    
    // 向量平均值
    template<typename T>
    double average(const std::vector<T>& vec) {
        if (vec.empty()) return 0.0;
        return static_cast<double>(sum(vec)) / vec.size();
    }
    
    // 查找最大值
    template<typename T>
    T max_element(const std::vector<T>& vec) {
        if (vec.empty()) {
            throw std::invalid_argument("Vector is empty");
        }
        return *std::max_element(vec.begin(), vec.end());
    }
    
    // 查找最小值
    template<typename T>
    T min_element(const std::vector<T>& vec) {
        if (vec.empty()) {
            throw std::invalid_argument("Vector is empty");
        }
        return *std::min_element(vec.begin(), vec.end());
    }
}

#endif //CPP_LEARNING_DEMO_VECTOR_UTILS_H