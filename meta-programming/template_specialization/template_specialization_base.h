#ifndef TEMPLATE_SPECIALIZATION_BASE_H
#define TEMPLATE_SPECIALIZATION_BASE_H

#include <iostream>
#include <string>
#include <vector>

// 模板特化基础功能
namespace template_specialization_demo {
    // 主模板
    template<typename T>
    struct TypeInfo {
        static std::string name() {
            return "未知类型";
        }
        
        static void print_info(const T& value) {
            std::cout << "通用类型，值为: " << value << std::endl;
        }
    };

    // int的完全特化
    template<>
    struct TypeInfo<int> {
        static std::string name() {
            return "int";
        }
        
        static void print_info(const int& value) {
            std::cout << "整数类型，值为: " << value << std::endl;
        }
    };

    // std::string的完全特化
    template<>
    struct TypeInfo<std::string> {
        static std::string name() {
            return "std::string";
        }
        
        static void print_info(const std::string& value) {
            std::cout << "字符串类型，值为: \"" << value << "\"" << std::endl;
        }
    };

    // 指针类型的偏特化
    template<typename T>
    struct TypeInfo<T*> {
        static std::string name() {
            return std::string("指向") + TypeInfo<T>::name() + "的指针";
        }
        
        static void print_info(T* value) {
            std::cout << "指向" << TypeInfo<T>::name() << "的指针，地址为: " << value << std::endl;
        }
    };

    // std::vector的偏特化
    template<typename T>
    struct TypeInfo<std::vector<T>> {
        static std::string name() {
            return std::string("std::vector<") + TypeInfo<T>::name() + ">";
        }
        
        static void print_info(const std::vector<T>& value) {
            std::cout << TypeInfo<T>::name() << "类型的向量，包含 " << value.size() << " 个元素" << std::endl;
        }
    };
}

#endif // TEMPLATE_SPECIALIZATION_BASE_H