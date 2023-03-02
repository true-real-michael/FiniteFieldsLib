project(FiniteFields_lib CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(FiniteFields INTERFACE)
target_include_directories(FiniteFields INTERFACE .)