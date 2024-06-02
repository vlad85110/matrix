#include <iostream>
#include "classes/SquareMatrix.h"
#include "methods.h"
#include <cmath>

SquareMatrix getMatrix();

Vector getVector();

std::vector<double> test_time(const Vector &vector, const SquareMatrix &matrix,
                              std::vector<std::function<Vector(const SquareMatrix &, const Vector &)>> &methods);

int main() {
    SquareMatrix matrixA = getMatrix();
    // Vector vectorB = getVector();

//    auto methods = std::vector<std::function<Vector(const SquareMatrix &, const Vector &)>>();
//    methods.emplace_back(gauss_method);
//    methods.emplace_back(jacobi_method);
//    methods.emplace_back(householder_method);
//    methods.emplace_back(gauss_seidel_method);
//
//    auto times = test_time(vectorB, matrixA, methods);
//
//    std::cout << "метод Гаусса: " << times[0] << std::endl;
//    std::cout << "метод Якоби: " << times[1] << std::endl;
//    std::cout << "метод Хаусхолдера: " << times[2] << std::endl;
//    std::cout << "метод Гаусса-Зейделя: " << times[3] << std::endl;

    //auto vectorX = sweep_method(matrixA, vectorB);

    //   matrixA.getConditionNumber();
//
    auto eValues = matrixA.getEigenvalues();
    std::cout << "Собственные числа: " << std::endl;
    for (auto i: eValues) {
        std::cout << i << std::endl;
    }

//    std::cout << std::endl;
//    std::cout << "A_INF: " << matrixA.measure(MeasureType::A_INF) << std::endl;
//    std::cout << "A1: " << matrixA.measure(MeasureType::A1) << std::endl;
//
//    auto x = 14;
//    auto t = 1.31;
//    auto s0 = 26;
//    auto n = 26;
//
//    auto res = x + (t * s0) / sqrt(n);
//
//    std::cout << res;

    return 0;
}

std::vector<double> test_time(const Vector &vector, const SquareMatrix &matrix,
                              std::vector<std::function<Vector(const SquareMatrix &, const Vector &)>> &methods) {
    std::vector<double> res;

    for (auto &fun: methods) {
        struct timespec start{}, end{};

        clock_gettime(CLOCK_REALTIME, &start);
        fun(matrix, vector);
        clock_gettime(CLOCK_REALTIME, &end);

        auto time = (double) (end.tv_sec - start.tv_sec)
                    + 0.000000001 * (double) (end.tv_nsec - start.tv_nsec);

        res.emplace_back(time);
    }

    return res;
}

SquareMatrix getMatrix() {
//    auto m = std::vector<double>{
//            20, 20, 0,
//            15, 15, 5,
//            0, 1, 1
//    };
//
//    auto m = std::vector<double>{
//            2, 1, -1,
//            1, -5, 4,
//            3, 2, 6
//    };
//
//    auto m = std::vector<double>{
//            4, -1, -1,
//            -1, 4, -1,
//            -1, -1, 4
//    };
//
//    auto m = std::vector<double>{
//            2, -1, 0,
//            -1, 2, -1,
//            0, -1, 2
//    };
//
//    auto m = std::vector<double>{
//            1, 1.0 / 2, 1.0 / 3,
//            1.0 / 2, 1.0 / 3, 1.0 / 4,
//            1.0 / 3, 1.0 / 4, 1.0 / 5
//    };
//
    auto m = std::vector<double>{
            -2, 0, 0,
            0, 0, 1,
            0, -1, 0
    };
//
//    auto m = std::vector<double>{
//            2, -1, 0,
//            5, 4, 2,
//            0, 1, -3
//    };
//
//    auto m = std::vector<double>{
//            2, -1,
//            -1, 2
//    };

//    auto m = std::vector<double>{
//            10, -1, 2, 0, 0,
//            1, 20, 3, 0, 0,
//            0, 1, -13, 0, 0,
//            0, 0, 1, 30, 1,
//            0, 0, 0, 4, 42
//    };

    return SquareMatrix(m);
}

Vector getVector() {
//    auto v = std::vector<double>{
//            40,
//            35,
//            2
//    };
//
//    auto v = std::vector<double>{
//            0,
//            10,
//            7
//    };
//
//    auto v = std::vector<double>{
//            2,
//            2,
//            2
//    };
//
    auto v = std::vector<double>{
            2,
            2,
            2
    };
//
//    auto v = std::vector<double>{
//            1,
//            1,
//    };
//
//    auto v = std::vector<double>{
//            1,
//            1,
//            1
//    };
//
//    auto v = std::vector<double>{
//            3,
//            6,
//            2
//    };

//    auto v = std::vector<double>{
//            3,
//            6,
//            2,
//            1,
//            1
//    };

    return Vector(v);
}
