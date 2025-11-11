cmake_minimum_required(VERSION 3.30)
project(cpp_learning_demo)

set(CMAKE_CXX_STANDARD 20)

# Find required packages
find_package(Threads REQUIRED)

# All header files used in the project
set(HEADER_FILES
    # Meta-programming headers
    meta-programming/type_traits/type_traits_demo.h
    meta-programming/type_traits/type_traits_base.h
    meta-programming/template_specialization/template_specialization_demo.h
    meta-programming/template_specialization/template_specialization_base.h
    meta-programming/sfinae/sfinae_demo.h
    meta-programming/sfinae/sfinae_base.h
    meta-programming/constexpr/constexpr_demo.h
    meta-programming/constexpr/constexpr_base.h
    meta-programming/variadic_templates/variadic_templates_demo.h
    meta-programming/variadic_templates/variadic_templates_base.h
    meta-programming/type_introspection/type_introspection_demo.h
    meta-programming/type_introspection/type_introspection_base.h
    meta-programming/crtp/crtp_demo.h
    meta-programming/crtp/crtp_base.h

    # Smart pointers headers
    smart-pointers/unique_ptr/unique_ptr_demo.h
    smart-pointers/shared_ptr/shared_ptr_demo.h
    smart-pointers/weak_ptr/weak_ptr_demo.h
    smart-pointers/circular_reference/circular_reference_demo.h
    smart-pointers/smart_pointers_base.h

    # Design patterns headers
    design-patterns/singleton/singleton_pattern.h
    design-patterns/observer/observer_pattern.h
    design-patterns/strategy/strategy_pattern.h
    design-patterns/decorator/decorator_pattern.h
    design-patterns/factory/factory_pattern.h
    design-patterns/design_patterns_base.h

    # Other C++ topics headers
    stl-containers/stl_containers_demo.h
    stl-algorithms/stl_algorithms_demo.h
    move-semantics/move_semantics_demo.h
    exception-handling/exception_handling_demo.h
    multithreading/multithreading_demo.h
    multithreading/thread_safe_queue.h
    modern-cpp-features/modern_cpp_features_demo.h
    function-comparison/function_comparison_demo.h
    memory-arena/improved_memory_arena.h
    memory-arena/memory_arena.h
    performance-benchmarking/performance_benchmarking_demo.h
    filesystem/filesystem_demo.h
    network/network_demo.h
    cpp20-23/cpp20_23_features_demo.h
    memory-leak-detection/memory_leak_detection_demo.h
    interop/interop_demo.h
    advanced-concurrency/advanced_concurrency_demo.h
    advanced-design-patterns/advanced_design_patterns_demo.h
    memory-order/memory_order_demo.h
)

add_executable(cpp_learning_demo main.cpp ${HEADER_FILES})

# Link required libraries
target_link_libraries(cpp_learning_demo PRIVATE Threads::Threads)

# 添加测试子目录
# 注意：只有在系统中安装了Google Test时才会构建测试
add_subdirectory(tests)