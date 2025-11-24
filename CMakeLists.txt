cmake_minimum_required(VERSION 3.10)
project(DSA_Project)

# C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 统一加入头文件根目录
include_directories(
    # ${PROJECT_SOURCE_DIR}/00_bitmap
    ${PROJECT_SOURCE_DIR}/01_vector/include
    # ${PROJECT_SOURCE_DIR}/02_list
    # ${PROJECT_SOURCE_DIR}/03_stack_queue
    # ${PROJECT_SOURCE_DIR}/04_Bintree
    # ${PROJECT_SOURCE_DIR}/05_BinSearchTree
    # ${PROJECT_SOURCE_DIR}/06_AdvancedSearchTree
    # ${PROJECT_SOURCE_DIR}/07_Dictionary
    # ${PROJECT_SOURCE_DIR}/08_Graph
    # ${PROJECT_SOURCE_DIR}/09_PrimiryQueue
    # ${PROJECT_SOURCE_DIR}/10_string
    # ${PROJECT_SOURCE_DIR}/11_sortAlgorithm
    ${PROJECT_SOURCE_DIR}/base
)

源文件
add_executable(main
)