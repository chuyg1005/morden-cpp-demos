cmake_minimum_required(VERSION 3.30)
project(cpp_learning_demo)

set(CMAKE_CXX_STANDARD 20)

# Find required packages
find_package(Threads REQUIRED)

add_executable(cpp_learning_demo main.cpp
        move-semantics/move_semantics_demo.h
        multithreading/thread_safe_queue.h)

# Link required libraries
target_link_libraries(cpp_learning_demo PRIVATE Threads::Threads)
