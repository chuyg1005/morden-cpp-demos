#include <gtest/gtest.h>
#include "../utils/vector_utils.h"
#include <vector>

// 测试向量求和函数
TEST(VectorUtilsTest, Sum) {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    EXPECT_EQ(vector_utils::sum(vec1), 15);
    
    std::vector<double> vec2 = {1.5, 2.5, 3.0};
    EXPECT_DOUBLE_EQ(vector_utils::sum(vec2), 7.0);
    
    std::vector<int> empty_vec;
    EXPECT_EQ(vector_utils::sum(empty_vec), 0);
}

// 测试向量平均值函数
TEST(VectorUtilsTest, Average) {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    EXPECT_DOUBLE_EQ(vector_utils::average(vec1), 3.0);
    
    std::vector<double> vec2 = {1.0, 2.0, 3.0};
    EXPECT_DOUBLE_EQ(vector_utils::average(vec2), 2.0);
    
    std::vector<int> empty_vec;
    EXPECT_DOUBLE_EQ(vector_utils::average(empty_vec), 0.0);
}

// 测试查找最大值函数
TEST(VectorUtilsTest, MaxElement) {
    std::vector<int> vec = {1, 5, 3, 9, 2};
    EXPECT_EQ(vector_utils::max_element(vec), 9);
    
    std::vector<double> vec2 = {1.1, 5.5, 3.3, 9.9, 2.2};
    EXPECT_DOUBLE_EQ(vector_utils::max_element(vec2), 9.9);
    
    // 测试空向量异常
    std::vector<int> empty_vec;
    EXPECT_THROW(vector_utils::max_element(empty_vec), std::invalid_argument);
}

// 测试查找最小值函数
TEST(VectorUtilsTest, MinElement) {
    std::vector<int> vec = {1, 5, 3, 9, 2};
    EXPECT_EQ(vector_utils::min_element(vec), 1);
    
    std::vector<double> vec2 = {1.1, 5.5, 3.3, 9.9, 2.2};
    EXPECT_DOUBLE_EQ(vector_utils::min_element(vec2), 1.1);
    
    // 测试空向量异常
    std::vector<int> empty_vec;
    EXPECT_THROW(vector_utils::min_element(empty_vec), std::invalid_argument);
}