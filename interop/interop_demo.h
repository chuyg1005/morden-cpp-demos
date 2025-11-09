#ifndef CPP_LEARNING_DEMO_INTEROP_DEMO_H
#define CPP_LEARNING_DEMO_INTEROP_DEMO_H

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

// C语言互操作示例
extern "C" {
    // C函数声明
    void c_function(int value);
    int c_add(int a, int b);
    
    // C结构体
    typedef struct {
        int id;
        char name[50];
    } CStruct;
    
    // C函数操作结构体
    void c_fill_struct(CStruct* s, int id, const char* name);
    void c_print_struct(const CStruct* s);
}

namespace interop_demo {
    // C++包装C函数
    void call_c_function() {
        std::cout << "\n=== 调用C函数 ===" << std::endl;
        c_function(42);
        int result = c_add(5, 3);
        std::cout << "C函数加法结果: " << result << std::endl;
    }
    
    // C++使用C结构体
    void use_c_struct() {
        std::cout << "\n=== 使用C结构体 ===" << std::endl;
        CStruct s;
        c_fill_struct(&s, 1, "测试结构体");
        c_print_struct(&s);
    }
    
    // C++提供给C使用的函数
    extern "C" void cpp_function_for_c(const char* message) {
        std::cout << "从C调用的C++函数: " << message << std::endl;
    }
    
    // C++类导出为C接口
    class Calculator {
    public:
        int add(int a, int b) { return a + b; }
        int multiply(int a, int b) { return a * b; }
    };
    
    // C兼容的包装函数
    extern "C" Calculator* create_calculator() {
        return new Calculator();
    }
    
    extern "C" void destroy_calculator(Calculator* calc) {
        delete calc;
    }
    
    extern "C" int calculator_add(Calculator* calc, int a, int b) {
        return calc->add(a, b);
    }
    
    extern "C" int calculator_multiply(Calculator* calc, int a, int b) {
        return calc->multiply(a, b);
    }
    
    void cpp_class_with_c_interface() {
        std::cout << "\n=== C++类通过C接口使用 ===" << std::endl;
        Calculator* calc = create_calculator();
        int sum = calculator_add(calc, 10, 20);
        int product = calculator_multiply(calc, 5, 6);
        std::cout << "计算器加法结果: " << sum << std::endl;
        std::cout << "计算器乘法结果: " << product << std::endl;
        destroy_calculator(calc);
    }
    
    // Python互操作概念示例（通过pybind11）
    void python_interop_concept() {
        std::cout << "\n=== Python互操作概念 ===" << std::endl;
        std::cout << "使用pybind11可以将C++代码暴露给Python:" << std::endl;
        std::cout << "1. 创建绑定代码将C++函数/类暴露给Python" << std::endl;
        std::cout << "2. 编译为Python模块" << std::endl;
        std::cout << "3. 在Python中导入和使用" << std::endl;
        std::cout << std::endl;
        std::cout << "示例绑定代码:" << std::endl;
        std::cout << "PYBIND11_MODULE(example, m) {" << std::endl;
        std::cout << "    m.doc() = \"pybind11 example plugin\";" << std::endl;
        std::cout << "    m.def(\"add\", [](int i, int j) { return i + j; });" << std::endl;
        std::cout << "}" << std::endl;
    }
    
    // JavaScript互操作概念示例（通过Emscripten）
    void javascript_interop_concept() {
        std::cout << "\n=== JavaScript互操作概念 ===" << std::endl;
        std::cout << "使用Emscripten可以将C++代码编译为WebAssembly:" << std::endl;
        std::cout << "1. 使用Emscripten编译C++代码" << std::endl;
        std::cout << "2. 生成.wasm文件和JavaScript胶水代码" << std::endl;
        std::cout << "3. 在网页中加载和使用" << std::endl;
        std::cout << std::endl;
        std::cout << "示例编译命令:" << std::endl;
        std::cout << "em++ example.cpp -o example.js" << std::endl;
    }
    
    // Rust互操作概念示例
    void rust_interop_concept() {
        std::cout << "\n=== Rust互操作概念 ===" << std::endl;
        std::cout << "C++和Rust可以通过C接口互操作:" << std::endl;
        std::cout << "1. C++代码提供C兼容接口" << std::endl;
        std::cout << "2. Rust使用extern块声明外部函数" << std::endl;
        std::cout << "3. 通过bindgen工具自动生成绑定" << std::endl;
    }
    
    // 运行所有演示
    void run_demo() {
        std::cout << "=== C++与其他语言互操作演示 ===" << std::endl;
        call_c_function();
        use_c_struct();
        cpp_class_with_c_interface();
        python_interop_concept();
        javascript_interop_concept();
        rust_interop_concept();
    }
}

// C函数的实现（在实际项目中可能在单独的.c文件中）
extern "C" void c_function(int value) {
    std::cout << "这是C函数，接收到值: " << value << std::endl;
}

extern "C" int c_add(int a, int b) {
    return a + b;
}

extern "C" void c_fill_struct(CStruct* s, int id, const char* name) {
    s->id = id;
    strncpy(s->name, name, sizeof(s->name) - 1);
    s->name[sizeof(s->name) - 1] = '\0';  // 确保字符串以null结尾
}

extern "C" void c_print_struct(const CStruct* s) {
    std::cout << "C结构体 - ID: " << s->id << ", Name: " << s->name << std::endl;
}

#endif //CPP_LEARNING_DEMO_INTEROP_DEMO_H