#ifndef CPP_LEARNING_DEMO_FILESYSTEM_DEMO_H
#define CPP_LEARNING_DEMO_FILESYSTEM_DEMO_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace filesystem_demo {
    namespace fs = std::filesystem;

    // 创建目录
    void create_directory_demo() {
        std::cout << "\n=== 创建目录演示 ===" << std::endl;
        
        fs::path dir_path = "demo_directory";
        if (fs::create_directory(dir_path)) {
            std::cout << "成功创建目录: " << dir_path << std::endl;
        } else {
            std::cout << "目录已存在或创建失败: " << dir_path << std::endl;
        }
    }

    // 文件操作演示
    void file_operations_demo() {
        std::cout << "\n=== 文件操作演示 ===" << std::endl;
        
        fs::path file_path = "demo_directory/demo_file.txt";
        
        // 创建并写入文件
        {
            std::ofstream file(file_path);
            if (file.is_open()) {
                file << "这是文件系统操作演示文件。\n";
                file << "第二行内容。\n";
                file << "第三行内容。\n";
                std::cout << "成功创建并写入文件: " << file_path << std::endl;
            } else {
                std::cout << "无法创建文件: " << file_path << std::endl;
            }
        }
        
        // 读取文件信息
        if (fs::exists(file_path)) {
            auto file_size = fs::file_size(file_path);
            auto last_write_time = fs::last_write_time(file_path);
            std::cout << "文件大小: " << file_size << " 字节" << std::endl;
            std::cout << "最后修改时间: " << decltype(last_write_time)::clock::to_time_t(last_write_time) << std::endl;
        }
    }

    // 遍历目录演示
    void directory_traversal_demo() {
        std::cout << "\n=== 遍历目录演示 ===" << std::endl;
        
        fs::path current_path = fs::current_path();
        std::cout << "当前目录: " << current_path << std::endl;
        
        std::cout << "目录内容:" << std::endl;
        for (const auto& entry : fs::directory_iterator(current_path)) {
            std::cout << (entry.is_directory() ? "DIR " : "FILE") << " ";
            std::cout << entry.path().filename().string() << std::endl;
        }
    }

    // 路径操作演示
    void path_operations_demo() {
        std::cout << "\n=== 路径操作演示 ===" << std::endl;
        
        fs::path p = "/Users/username/projects/demo/file.txt";
        
        std::cout << "完整路径: " << p << std::endl;
        std::cout << "根路径: " << p.root_path() << std::endl;
        std::cout << "根名称: " << p.root_name() << std::endl;
        std::cout << "根目录: " << p.root_directory() << std::endl;
        std::cout << "相对路径: " << p.relative_path() << std::endl;
        std::cout << "父路径: " << p.parent_path() << std::endl;
        std::cout << "文件名: " << p.filename() << std::endl;
        std::cout << "文件 stem: " << p.stem() << std::endl;
        std::cout << "扩展名: " << p.extension() << std::endl;
    }

    // 文件复制和移动演示
    void file_copy_move_demo() {
        std::cout << "\n=== 文件复制和移动演示 ===" << std::endl;
        
        fs::path source_file = "demo_directory/demo_file.txt";
        fs::path copy_file = "demo_directory/demo_file_copy.txt";
        fs::path moved_file = "demo_directory/demo_file_moved.txt";
        
        // 复制文件
        if (fs::exists(source_file)) {
            try {
                fs::copy_file(source_file, copy_file, fs::copy_options::skip_existing);
                std::cout << "文件复制成功: " << source_file << " -> " << copy_file << std::endl;
            } catch (const fs::filesystem_error& ex) {
                std::cout << "文件复制失败: " << ex.what() << std::endl;
            }
        }
        
        // 移动/重命名文件
        if (fs::exists(copy_file)) {
            try {
                fs::rename(copy_file, moved_file);
                std::cout << "文件移动/重命名成功: " << copy_file << " -> " << moved_file << std::endl;
            } catch (const fs::filesystem_error& ex) {
                std::cout << "文件移动/重命名失败: " << ex.what() << std::endl;
            }
        }
    }

    // 空间信息演示
    void space_info_demo() {
        std::cout << "\n=== 磁盘空间信息演示 ===" << std::endl;
        
        fs::path current_path = fs::current_path();
        auto space_info = fs::space(current_path);
        
        std::cout << "当前路径: " << current_path << std::endl;
        std::cout << "总空间: " << space_info.capacity << " 字节" << std::endl;
        std::cout << "可用空间: " << space_info.available << " 字节" << std::endl;
        std::cout << "已用空间: " << (space_info.capacity - space_info.free) << " 字节" << std::endl;
    }

    // 清理演示文件
    void cleanup_demo() {
        std::cout << "\n=== 清理演示文件 ===" << std::endl;
        
        fs::path dir_path = "demo_directory";
        if (fs::exists(dir_path)) {
            fs::remove_all(dir_path);
            std::cout << "已删除目录及其内容: " << dir_path << std::endl;
        }
    }

    // 运行所有演示
    void run_demo() {
        std::cout << "=== C++17 文件系统库演示 ===" << std::endl;
        create_directory_demo();
        file_operations_demo();
        directory_traversal_demo();
        path_operations_demo();
        file_copy_move_demo();
        space_info_demo();
        cleanup_demo();
    }
}

#endif //CPP_LEARNING_DEMO_FILESYSTEM_DEMO_H