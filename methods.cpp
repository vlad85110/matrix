//
// Created by Влад Кирилов on 26.10.2022.
//

#include "methods.h"
#include <iostream>
#include <cmath>

Vector get_root_vector(SquareMatrix &resMatrix, Vector &resVector);

Vector gauss_method(const SquareMatrix &matrixA, const Vector &vectorB) {
    auto resMatrix = SquareMatrix(matrixA);
    auto resVector = Vector(vectorB);

    for (int j = 0; j < matrixA.getSize() - 1; ++j) {
        auto e = SquareMatrix(matrixA.getSize(), true);

        if (matrixA.getValue(j, j) != 0) {
            for (int i = j + 1; i < resMatrix.getSize(); ++i) {
                e.setValue(i, j, -matrixA.getValue(i, j) / matrixA.getValue(j, j));
            }
        }

        resMatrix = e * resMatrix;
        resVector = e * resVector;
    }

    auto perm = resMatrix.sort_rows();
    resVector.perm(perm);

    return get_root_vector(resMatrix, resVector);
}

Vector jacobi_method(const SquareMatrix &matrixA, const Vector &vectorB) {
    auto eps = pow(10, -7);

    auto size = matrixA.getSize();

    SquareMatrix matrixD1(size, false);
    for (int i = 0; i < size; ++i) {
        matrixD1.setValue(i, i, 1 / matrixA.getValue(i, i));
    }

    SquareMatrix matrixLUD(size, false);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != j) {
                matrixLUD.setValue(i, j, -matrixA.getValue(i, j) /
                                         matrixA.getValue(i, i));
            }
        }
    }

    Vector vectorXk(size, 0);
    Vector prev(size);

    do {
        prev = vectorXk;
        vectorXk = (matrixLUD * vectorXk) + (matrixD1 * vectorB);
    } while (abs((prev - vectorXk).max()) > eps);

    return vectorXk;
}

Vector householder_method(const SquareMatrix &matrixA, const Vector &vectorB) {
    auto size = matrixA.getSize();
    auto resMatrix = SquareMatrix(matrixA);
    auto resVector = Vector(vectorB);

    for (int i = 0; i < size - 1; ++i) {
        Vector vectorAin(size - i);
        Vector vectorE(size - i);
        vectorE.setValue(0, 1);

        for (int j = 0; j < size - i; ++j) {
            vectorAin.setValue(j, resMatrix.getValue(j + i, i));
        }

        SquareMatrix matrixAin(size - i, false);
        for (int j = i; j < size; ++j) {
            for (int k = i; k < size; ++k) {
                matrixAin.setValue(j - i, k - i, resMatrix.getValue(j, k));
            }
        }

        Vector vectorU_(size - i);
        if (resMatrix.getValue(i, i) >= 0) {
            vectorU_ = vectorAin + vectorE * vectorAin.measure();
        } else {
            vectorU_ = vectorAin + vectorE * vectorAin.measure();
        }
        Vector vectorU(vectorU_ * (1 / vectorU_.measure()));

        SquareMatrix matrixUU(size - i, false);
        for (int j = 0; j < size - i; ++j) {
            for (int k = 0; k < size - i; ++k) {
                matrixUU.setValue(j, k, 2 * vectorU[j] * vectorU[k]);
            }
        }

        SquareMatrix matrixE(size - i, true);
        auto matrixH_ = matrixE - matrixUU;

        SquareMatrix matrixH(size, true);
        for (int j = 0; j < size - i; ++j) {
            for (int k = 0; k < size - i; ++k) {
                matrixH.setValue(j + i, k + i, matrixH_.getValue(j, k));
            }
        }

        resMatrix = matrixH * resMatrix;
        resVector = matrixH * resVector;
    }

    return get_root_vector(resMatrix, resVector);
}

Vector gauss_seidel_method(const SquareMatrix &matrixA, const Vector &vectorB) {
    auto eps = pow(10, -7);
    auto size = matrixA.getSize();

    Vector vectorXk(size, 0);
    Vector prev(size);

    auto k = 1;
    do {
        prev = vectorXk;

        for (int i = 0; i < size; ++i) {
            auto aii = matrixA.getValue(i, i);

            double prev_sum = 0;
            for (int j = i + 1; j < size; ++j) {
                prev_sum += matrixA.getValue(i, j) * prev[j];
            }

            double new_sum = 0;
            for (int j = 0; j < i; ++j) {
                new_sum += matrixA.getValue(i, j) * vectorXk[j];
            }   

            vectorXk.setValue(i, (1 / aii) * (vectorB[i] - new_sum - prev_sum));
        }
    } while (abs((prev - vectorXk).max()) > eps);

    return vectorXk;
}

Vector sweep_method(const SquareMatrix &matrixA, const Vector &vectorB) {
    auto size = matrixA.getSize();

    Vector vector_ksi(size + 1, 0);
    Vector vector_nu(size + 1, 0);

    for (int i = 0; i < size; ++i) {
        auto ai = matrixA.getValue(i, i - 1);
        auto bi = matrixA.getValue(i, i);
        auto ci = matrixA.getValue(i, i + 1);
        auto di = vectorB[i];

        auto yi = ai * vector_ksi[i - 1] + bi;
        vector_ksi.setValue(i, -ci / yi);
        vector_nu.setValue(i, (di - ai * vector_nu[i - 1]) / yi);
    }

    Vector vectorX(size);
    vectorX.setValue(size - 1, vector_nu[size - 1]);
    for (int i = (int)size - 2; i >= 0; --i) {
        vectorX.setValue(i, vector_ksi[i] * vectorX[i + 1] + vector_nu[i]);
    }

    return vectorX;
}

Vector get_root_vector(SquareMatrix &resMatrix, Vector &resVector) {
    Vector vectorX(resMatrix.getSize());
    for (long i = (long) resMatrix.getSize() - 1; i >= 0; i--) {
        double value = 0;

        for (auto j = i + 1; j < resMatrix.getSize(); ++j) {
            value += resMatrix.getValue(i, j) * vectorX[j];
        }

        value = (resVector[i] - value) / resMatrix.getValue(i, i);
        vectorX.setValue(i, value);
    }

    return vectorX;
}
