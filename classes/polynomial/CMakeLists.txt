cmake_minimum_required(VERSION 3.21)
project(math_lab_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(polynomial ThirdDegPolynomial.cpp ThirdDegPolynomial.h SecondDegPolynomial.cpp SecondDegPolynomial.h math_functions.cpp math_functions.h Sides.h FirstDegPolynomial.cpp FirstDegPolynomial.h)
