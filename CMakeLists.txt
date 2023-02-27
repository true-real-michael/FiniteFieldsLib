cmake_minimum_required(VERSION 3.24)
project(FiniteFields_main)

set(CMAKE_CXX_STANDARD 20)

add_executable(FiniteFields_run main.cpp)
target_link_libraries(FiniteFields_run FiniteFields)

include_directories(FiniteFields)
add_subdirectory(FiniteFields)

if (CMAKE_TESTING_ENABLED)
    add_subdirectory(gtest)
endif()
