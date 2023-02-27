project(FiniteFields_lib CXX)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        Polynomial.hpp
        PrimeFieldElement.hpp
#        FiniteFieldElement.hpp
        )

add_library(FiniteFields INTERFACE)
target_include_directories(FiniteFields INTERFACE .)