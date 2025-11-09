#ifndef STL_ALGORITHMS_DEMO_H
#define STL_ALGORITHMS_DEMO_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <string>
#include <chrono>
#include <random>

// 演示STL算法的使用
namespace stl_algorithms_demo {
    // 演示非修改性序列算法
    void non_modifying_sequence_algorithms_demo() {
        std::cout << "\n=== 非修改性序列算法演示 ===" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5, 4, 3, 2, 1};
        
        // std::find - 查找元素
        auto it = std::find(vec.begin(), vec.end(), 3);
        if (it != vec.end()) {
            std::cout << "找到元素 3，位置: " << std::distance(vec.begin(), it) << std::endl;
        }
        
        // std::count - 计算元素出现次数
        int count = std::count(vec.begin(), vec.end(), 3);
        std::cout << "元素 3 出现次数: " << count << std::endl;
        
        // std::all_of, std::any_of, std::none_of - 条件检查
        bool all_positive = std::all_of(vec.begin(), vec.end(), [](int i) { return i > 0; });
        bool any_negative = std::any_of(vec.begin(), vec.end(), [](int i) { return i < 0; });
        bool none_zero = std::none_of(vec.begin(), vec.end(), [](int i) { return i == 0; });
        
        std::cout << "所有元素都为正数: " << std::boolalpha << all_positive << std::endl;
        std::cout << "存在负数元素: " << any_negative << std::endl;
        std::cout << "不存在零元素: " << none_zero << std::endl;
    }

    // 演示修改性序列算法
    void modifying_sequence_algorithms_demo() {
        std::cout << "\n=== 修改性序列算法演示 ===" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5};
        std::vector<int> result(vec.size());
        
        // std::copy - 复制元素
        std::copy(vec.begin(), vec.end(), result.begin());
        std::cout << "复制后: ";
        for (const auto& item : result) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // std::transform - 转换元素
        std::transform(vec.begin(), vec.end(), result.begin(), [](int i) { return i * 2; });
        std::cout << "转换后(乘以2): ";
        for (const auto& item : result) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // std::replace - 替换元素
        std::replace(result.begin(), result.end(), 4, 99);
        std::cout << "替换4为99后: ";
        for (const auto& item : result) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    // 演示排序和相关算法
    void sorting_algorithms_demo() {
        std::cout << "\n=== 排序算法演示 ===" << std::endl;
        
        std::vector<int> vec = {5, 2, 8, 1, 9, 3};
        
        // std::sort - 排序
        std::vector<int> sorted_vec = vec;
        std::sort(sorted_vec.begin(), sorted_vec.end());
        std::cout << "排序后: ";
        for (const auto& item : sorted_vec) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // std::partial_sort - 部分排序
        std::vector<int> partial_vec = vec;
        std::partial_sort(partial_vec.begin(), partial_vec.begin() + 3, partial_vec.end());
        std::cout << "部分排序(前3个): ";
        for (const auto& item : partial_vec) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // std::nth_element - 第n个元素
        std::vector<int> nth_vec = vec;
        std::nth_element(nth_vec.begin(), nth_vec.begin() + 2, nth_vec.end());
        std::cout << "第3小的元素: " << nth_vec[2] << std::endl;
    }

    // 演示数值算法
    void numeric_algorithms_demo() {
        std::cout << "\n=== 数值算法演示 ===" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5};
        
        // std::accumulate - 累加
        int sum = std::accumulate(vec.begin(), vec.end(), 0);
        std::cout << "累加和: " << sum << std::endl;
        
        // std::inner_product - 内积
        std::vector<int> vec2 = {2, 3, 4, 5, 6};
        int inner_prod = std::inner_product(vec.begin(), vec.end(), vec2.begin(), 0);
        std::cout << "内积: " << inner_prod << std::endl;
        
        // std::partial_sum - 部分和
        std::vector<int> partial_sums(vec.size());
        std::partial_sum(vec.begin(), vec.end(), partial_sums.begin());
        std::cout << "部分和: ";
        for (const auto& item : partial_sums) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    // 演示集合算法
    void set_algorithms_demo() {
        std::cout << "\n=== 集合算法演示 ===" << std::endl;
        
        std::vector<int> set1 = {1, 2, 3, 4, 5};
        std::vector<int> set2 = {3, 4, 5, 6, 7};
        
        // 需要先排序
        std::sort(set1.begin(), set1.end());
        std::sort(set2.begin(), set2.end());
        
        // std::set_union - 并集
        std::vector<int> union_result;
        std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), 
                       std::back_inserter(union_result));
        std::cout << "并集: ";
        for (const auto& item : union_result) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // std::set_intersection - 交集
        std::vector<int> intersection_result;
        std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                              std::back_inserter(intersection_result));
        std::cout << "交集: ";
        for (const auto& item : intersection_result) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    // 算法性能比较
    void algorithm_performance_demo() {
        std::cout << "\n=== 算法性能比较 ===" << std::endl;
        
        // 创建测试数据
        const int size = 100000;
        std::vector<int> vec(size);
        std::iota(vec.begin(), vec.end(), 1);
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(vec.begin(), vec.end(), g);
        
        // 测试std::sort性能
        std::vector<int> vec1 = vec;
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(vec1.begin(), vec1.end());
        auto end = std::chrono::high_resolution_clock::now();
        auto sort_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // 测试std::stable_sort性能, stable_sort开销为50ms，而sort只需要5ms
        std::vector<int> vec2 = vec;
        start = std::chrono::high_resolution_clock::now();
        std::stable_sort(vec2.begin(), vec2.end());
        end = std::chrono::high_resolution_clock::now();
        auto stable_sort_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "排序" << size << "个元素的时间:" << std::endl;
        std::cout << "std::sort: " << sort_duration.count() << " 微秒" << std::endl;
        std::cout << "std::stable_sort: " << stable_sort_duration.count() << " 微秒" << std::endl;
    }
}

#endif // STL_ALGORITHMS_DEMO_H