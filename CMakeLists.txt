cmake_minimum_required(VERSION 3.23)
project(matrix)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(classes/polynomial)
add_executable(matrix main.cpp classes/SquareMatrix.cpp classes/SquareMatrix.h classes/Vector.cpp classes/Vector.h
        methods.cpp methods.h classes/polynomial/ThirdDegPolynomial.cpp classes/polynomial/FirstDegPolynomial.cpp
        classes/polynomial/SecondDegPolynomial.cpp classes/polynomial/math_functions.cpp)
