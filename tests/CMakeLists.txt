# 测试的CMakeLists.txt

# 启用测试
enable_testing()

# 查找Google Test
find_package(GTest QUIET)

if(GTEST_FOUND)
    message(STATUS "Found GTest: ${GTEST_INCLUDE_DIRS}")
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
    target_include_directories(cpp_learning_demo_tests PRIVATE ${GTEST_INCLUDE_DIRS})

    # 注册测试
    add_test(NAME cpp_learning_demo_tests COMMAND cpp_learning_demo_tests)
else()
    # 尝试使用pkg-config查找Google Test
    find_package(PkgConfig QUIET)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(GTEST QUIET gtest_main)
    endif()
    
    if(GTEST_FOUND)
        message(STATUS "Found GTest via pkg-config: ${GTEST_INCLUDE_DIRS}")
        # 创建测试可执行文件
        add_executable(cpp_learning_demo_tests
            test_main.cpp
            test_vector_utils.cpp
        )

        # 链接Google Test和项目库
        target_link_libraries(cpp_learning_demo_tests 
            ${GTEST_LIBRARIES}
        )
        target_include_directories(cpp_learning_demo_tests PRIVATE ${GTEST_INCLUDE_DIRS})

        # 注册测试
        add_test(NAME cpp_learning_demo_tests COMMAND cpp_learning_demo_tests)
    else()
        message(WARNING "Google Test not found. Tests will not be built.")
    endif()
endif()