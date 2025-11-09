#include <gtest/gtest.h>

// 测试主函数 - Google Test会提供默认实现
// 这里可以添加全局测试设置和清理代码

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    // 可以在这里添加全局设置代码
    
    int result = RUN_ALL_TESTS();
    
    // 可以在这里添加全局清理代码
    
    return result;
}