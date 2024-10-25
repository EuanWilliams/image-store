cmake_minimum_required(VERSION 3.17)
project(image_store
    VERSION 0.0
    DESCRIPTION "An image store for rapidly storing, indexing and retrieving images"
    LANGUAGES CXX)
add_executable(image_store
    ../main.cpp
    ../src/add.cpp)
