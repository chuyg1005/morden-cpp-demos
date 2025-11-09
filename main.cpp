#include <iostream>
#include <string>
#include <vector>
#include <array>

// Meta-programming headers
#include "meta-programming/type_traits/type_traits_demo.h"
#include "meta-programming/template_specialization/template_specialization_demo.h"
#include "meta-programming/sfinae/sfinae_demo.h"
#include "meta-programming/constexpr/constexpr_demo.h"
#include "meta-programming/variadic_templates/variadic_templates_demo.h"
#include "meta-programming/type_introspection/type_introspection_demo.h"
#include "meta-programming/crtp/crtp_demo.h"

// Smart pointers headers
#include "smart-pointers/unique_ptr/unique_ptr_demo.h"
#include "smart-pointers/shared_ptr/shared_ptr_demo.h"
#include "smart-pointers/weak_ptr/weak_ptr_demo.h"
#include "smart-pointers/circular_reference/circular_reference_demo.h"

// Design patterns headers
#include "design-patterns/singleton/singleton_pattern.h"
#include "design-patterns/observer/observer_pattern.h"
#include "design-patterns/strategy/strategy_pattern.h"
#include "design-patterns/decorator/decorator_pattern.h"
#include "design-patterns/factory/factory_pattern.h"

// Other C++ topics headers
#include "stl-containers/stl_containers_demo.h"
#include "stl-algorithms/stl_algorithms_demo.h"
#include "move-semantics/move_semantics_demo.h"
#include "exception-handling/exception_handling_demo.h"
#include "multithreading/multithreading_demo.h"
#include "modern-cpp-features/modern_cpp_features_demo.h"

int main() {
    std::cout << "=== C++ 全面学习项目演示 ===" << std::endl;
    
    // 1. Meta-programming demo
    std::cout << "\n1. 元编程演示:" << std::endl;
    type_traits_demo::run_demo();
    template_specialization_demo::run_demo();
    sfinae_demo::run_demo();
    constexpr_demo::run_demo();
    variadic_templates_demo::run_demo();
    type_introspection_demo::run_demo();
    crtp_demo::run_demo();
    
    // 2. Smart pointers demo
    std::cout << "\n\n2. 智能指针演示:" << std::endl;
    smart_pointers_demo::unique_ptr_demo();
    smart_pointers_demo::shared_ptr_demo();
    smart_pointers_demo::weak_ptr_demo();
    smart_pointers_demo::circular_reference_demo();
    
    // 3. STL containers demo
    std::cout << "\n\n3. STL容器演示:" << std::endl;
    stl_containers_demo::sequence_containers_demo();
    stl_containers_demo::associative_containers_demo();
    stl_containers_demo::unordered_containers_demo();
    
    // 4. STL algorithms demo
    std::cout << "\n\n4. STL算法演示:" << std::endl;
    stl_algorithms_demo::non_modifying_sequence_algorithms_demo();
    stl_algorithms_demo::modifying_sequence_algorithms_demo();
    stl_algorithms_demo::sorting_algorithms_demo();
    stl_algorithms_demo::numeric_algorithms_demo();
    stl_algorithms_demo::set_algorithms_demo();
    stl_algorithms_demo::algorithm_performance_demo();
    
    // 5. Move semantics demo
    std::cout << "\n\n5. 移动语义演示:" << std::endl;
    move_semantics_demo::copy_vs_move_performance_demo();
    move_semantics_demo::std_move_demo();
    move_semantics_demo::perfect_forwarding_demo();
    move_semantics_demo::move_iterator_demo();
    
    // 6. Exception handling demo
    std::cout << "\n\n6. 异常处理演示:" << std::endl;
    exception_handling_demo::basic_exception_handling_demo();
    exception_handling_demo::exception_safety_demo();
    exception_handling_demo::function_try_block_demo();
    exception_handling_demo::noexcept_demo();

    // 7. Multithreading demo
    std::cout << "\n\n7. 多线程演示:" << std::endl;
    multithreading_demo::basic_threading_demo();
    multithreading_demo::mutex_condition_variable_demo();
    multithreading_demo::atomic_operations_demo();
    multithreading_demo::async_future_demo();
    multithreading_demo::shared_mutex_demo();
    
    // 8. Design patterns demo
    std::cout << "\n\n8. 设计模式演示:" << std::endl;
    design_patterns_demo::singleton_demo();
    design_patterns_demo::observer_demo();
    design_patterns_demo::strategy_demo();
    design_patterns_demo::decorator_demo();
    design_patterns_demo::factory_demo();
    
    // 9. Modern C++ features demo
    std::cout << "\n\n9. 现代C++特性演示:" << std::endl;
    modern_cpp_features_demo::auto_type_deduction_demo();
    modern_cpp_features_demo::range_based_for_loop_demo();
    modern_cpp_features_demo::lambda_expressions_demo();
    modern_cpp_features_demo::optional_demo();
    modern_cpp_features_demo::variant_demo();
    modern_cpp_features_demo::any_demo();
    modern_cpp_features_demo::structured_bindings_demo();
    modern_cpp_features_demo::if_constexpr_demo();
    modern_cpp_features_demo::fold_expressions_demo();

    std::cout << "\n\n=== 所有演示完成 ===" << std::endl;
    
    return 0;
}