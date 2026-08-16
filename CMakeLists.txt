cmake_minimum_required(VERSION 3.18)
project(cpypp VERSION 0.1.0 LANGUAGES CXX)

# OPTIONS
option(BUILD_TESTS "Build unit tests" ON)

# Set the building options.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find the Python runtime.
find_package(Python3 REQUIRED COMPONENTS Development.Embed)
message(STATUS
    "Find Python header at ${Python3_INCLUDE_DIRS}\nand library at ${Python3_LIBRARIES}"
)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()
