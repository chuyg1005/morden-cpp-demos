# 测试的CMakeLists.txt

# 启用测试
enable_testing()

# 查找Google Test
find_package(GTest REQUIRED)

# 创建测试可执行文件
add_executable(cpp_learning_demo_tests
    test_main.cpp
    test_vector_utils.cpp
)

# 链接Google Test和项目库
target_link_libraries(cpp_learning_demo_tests 
    GTest::gtest 
    GTest::gtest_main
)

# 注册测试
add_test(NAME cpp_learning_demo_tests COMMAND cpp_learning_demo_tests)