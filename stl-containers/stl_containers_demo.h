#ifndef STL_CONTAINERS_DEMO_H
#define STL_CONTAINERS_DEMO_H

#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>

// 演示STL容器的使用
namespace stl_containers_demo {
    // 演示序列容器
    void sequence_containers_demo() {
        std::cout << "\n=== 序列容器演示 ===" << std::endl;
        
        // vector - 动态数组
        std::cout << "1. vector演示:" << std::endl;
        std::vector<int> vec = {1, 2, 3, 4, 5};
        vec.push_back(6);
        for (const auto& item : vec) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // array - 固定大小数组
        std::cout << "2. array演示:" << std::endl;
        std::array<int, 5> arr = {10, 20, 30, 40, 50};
        for (const auto& item : arr) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // deque - 双端队列
        std::cout << "3. deque演示:" << std::endl;
        std::deque<int> deq = {100, 200, 300};
        deq.push_front(50);
        deq.push_back(400);
        for (const auto& item : deq) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // list - 双向链表
        std::cout << "4. list演示:" << std::endl;
        std::list<int> lst = {1000, 2000, 3000};
        lst.push_front(500);
        lst.push_back(4000);
        for (const auto& item : lst) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // forward_list - 单向链表
        std::cout << "5. forward_list演示:" << std::endl;
        std::forward_list<int> flst = {10000, 20000, 30000};
        flst.push_front(5000);
        for (const auto& item : flst) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    // 演示关联容器
    void associative_containers_demo() {
        std::cout << "\n=== 关联容器演示 ===" << std::endl;
        
        // set - 集合
        std::cout << "1. set演示:" << std::endl;
        std::set<int> s = {3, 1, 4, 1, 5, 9, 2, 6};
        for (const auto& item : s) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // map - 映射
        std::cout << "2. map演示:" << std::endl;
        std::map<std::string, int> m = {
            {"apple", 5},
            {"banana", 3},
            {"orange", 8}
        };
        for (const auto& pair : m) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
        
        // multiset - 多重集合
        std::cout << "3. multiset演示:" << std::endl;
        std::multiset<int> ms = {3, 1, 4, 1, 5, 9, 2, 6, 5};
        for (const auto& item : ms) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // multimap - 多重映射
        std::cout << "4. multimap演示:" << std::endl;
        std::multimap<std::string, int> mm = {
            {"fruit", 5},
            {"fruit", 3},
            {"vegetable", 8},
            {"fruit", 2}
        };
        for (const auto& pair : mm) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    // 演示无序关联容器
    void unordered_containers_demo() {
        std::cout << "\n=== 无序关联容器演示 ===" << std::endl;
        
        // unordered_set - 无序集合
        std::cout << "1. unordered_set演示:" << std::endl;
        std::unordered_set<int> us = {3, 1, 4, 1, 5, 9, 2, 6};
        for (const auto& item : us) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // unordered_map - 无序映射
        std::cout << "2. unordered_map演示:" << std::endl;
        std::unordered_map<std::string, int> um = {
            {"apple", 5},
            {"banana", 3},
            {"orange", 8}
        };
        for (const auto& pair : um) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    // 容器性能比较
    void container_performance_demo() {
        std::cout << "\n=== 容器性能比较 ===" << std::endl;
        
        const int size = 10000;
        
        // vector插入性能
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> vec;
        for (int i = 0; i < size; ++i) {
            vec.push_back(i);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto vec_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // list插入性能
        start = std::chrono::high_resolution_clock::now();
        std::list<int> lst;
        for (int i = 0; i < size; ++i) {
            lst.push_back(i);
        }
        end = std::chrono::high_resolution_clock::now();
        auto lst_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "插入" << size << "个元素的时间:" << std::endl;
        std::cout << "vector: " << vec_duration.count() << " 微秒" << std::endl;
        std::cout << "list: " << lst_duration.count() << " 微秒" << std::endl;
    }
}

#endif // STL_CONTAINERS_DEMO_H