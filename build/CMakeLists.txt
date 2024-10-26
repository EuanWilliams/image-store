cmake_minimum_required(VERSION 3.17)
project(image_store
    VERSION 0.0
    DESCRIPTION "An image store for rapidly storing, indexing and retrieving images"
    LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the SQLite3 library
find_package(SQLite3 REQUIRED)

# Add the executable
add_executable(image_store
    ../main.cpp
    ../src/database.h
    ../src/argument_parser.h
    ../src/import.cpp
)

# Link the SQLite3 library to your executable
target_link_libraries(image_store SQLite::SQLite3)

