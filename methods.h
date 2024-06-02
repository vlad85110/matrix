//
// Created by Влад Кирилов on 26.10.2022.
//

#pragma once

#include "classes/Vector.h"
#include "classes/SquareMatrix.h"

Vector gauss_method(const SquareMatrix& matrixA, const Vector& vectorB);
Vector jacobi_method(const SquareMatrix& matrixA, const Vector& vectorB);
Vector householder_method(const SquareMatrix& matrixA, const Vector& vectorB);
Vector gauss_seidel_method(const SquareMatrix &matrixA, const Vector &vectorB);
Vector sweep_method(const SquareMatrix &matrixA, const Vector &vectorB);