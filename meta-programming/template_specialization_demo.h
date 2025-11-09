#ifndef TEMPLATE_SPECIALIZATION_DEMO_H
#define TEMPLATE_SPECIALIZATION_DEMO_H

#include <iostream>
#include <string>
#include <vector>

// 演示模板特化
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
    
    // 运行template_specialization演示
    inline void run_meta_programming_demo() {
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