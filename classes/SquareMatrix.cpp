#include "SquareMatrix.h"
#include <iostream>
#include <cmath>
#include "polynomial/ThirdDegPolynomial.h"

SquareMatrix::SquareMatrix(size_t size, bool isOne) : data(size * size) {
    this->size = size;

    if (isOne) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (i == j) {
                    data[i * size + j] = 1;
                }
            }
        }
    }
}

SquareMatrix::SquareMatrix(std::vector<double> &data) :
    data(data), size(static_cast<size_t>(sqrt(data.size()))) {}

Vector SquareMatrix::operator*(const Vector &vector) const {
    Vector result(size, 0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.data[i] += data[size * i + j] * vector[j];
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const SquareMatrix &matrix) {
    for (int i = 0; i < matrix.size; ++i) {
        for (int j = 0; j < matrix.size; ++j) {
            os << matrix.data[matrix.size * i + j] << " ";
        }
        os << "\n";
    }
    return os;
}

void SquareMatrix::setValue(int row, int col, double value) {
    this->data[row * size + col] = value;
}

size_t SquareMatrix::getSize() const {
    return size;
}

double SquareMatrix::getValue(size_t row, size_t col) const {
    return data[row * size + col];
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix &matrix) const {
    SquareMatrix res(size, false);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                res.add(i, j, getValue(i, k) * matrix.getValue(k, j));
            }
        }
    }

    return res;
}

void SquareMatrix::add(int row, int col, double value) {
    data[row * size + col] += value;
}

std::shared_ptr<int[]> SquareMatrix::sort_rows() {
    auto permutation = new int [size];
    int tmp;

    for (int i = 0; i < size; ++i) {
        permutation[i] = i;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            if (count_zeros(i) > count_zeros(j)) {
                swap_rows(i, j);

                tmp = permutation[i];
                permutation[i] = permutation[j];
                permutation[j] = tmp;
            }
        }
    }

    return std::shared_ptr<int[]>(permutation);
}

int SquareMatrix::count_zeros(size_t row) const {
    int res = 0;

    for (auto i = 0; i < size; ++i) {
        if (data[size * row + i] == 0) {
            res++;
        } else {
            break;
        }
    }

    return res;
}

void SquareMatrix::swap_rows(size_t i, size_t j) {
    auto start_it = data.begin() + static_cast<long>(i * size);
    auto end_it = data.begin() + static_cast<long>(i * size + size);
    auto tmp = std::vector(start_it, end_it);

    for (int k = 0; k < size; ++k) {
        data[i * size + k] = data[j * size + k];
    }

    for (int k = 0; k < size; ++k) {
        data[j * size + k] = tmp[k];
    }
}

SquareMatrix SquareMatrix::operator*(double num) const {
    SquareMatrix res(size, false);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            res.setValue(i, j,  num * getValue(i, j));
        }
    }

    return res;
}

std::vector<double> SquareMatrix::getEigenvalues() const {
    double b = 0;
    for (int i = 0; i < size; ++i) {
        b += getValue(i, i);
    }

    double c = 0;
    c +=  getValue(1, 1) * getValue(2, 2) -
          getValue(1, 2) * getValue(2, 1);

    c +=  getValue(0, 0) * getValue(2, 2) -
          getValue(2, 0) * getValue(0, 2);

    c +=  getValue(0, 0) * getValue(1, 1) -
          getValue(0, 1) * getValue(1, 0);

    double d = determinant();
    auto polynomial = ThirdDegPolynomial(-1, b, -c , d);
    std::cout << polynomial << std::endl;
    return polynomial.get_roots();
}

double SquareMatrix::determinant() const {
    if (size == 3) {
        return
                getValue(0, 0) * getValue(1, 1) * getValue(2, 2) +
                getValue(2, 0) * getValue(0, 1) * getValue(1, 2) +
                getValue(0, 2) * getValue(1, 0) * getValue(2, 1) -
                getValue(0, 2) * getValue(1, 1) * getValue(2, 0) -
                getValue(0, 1) * getValue(1, 0) * getValue(2, 2) -
                getValue(0, 0) * getValue(2, 1) * getValue(1, 2);
    }

    if (size == 2) {
        return
                getValue(0, 0) * getValue(1, 1) -
                getValue(0, 1) * getValue(1, 0);
    }

    return 0;
}

double SquareMatrix::measure(MeasureType type) const {
    std::vector<double> vector;

    switch (type) {
        case MeasureType::A1:
            for (int i = 0; i < size; ++i) {
                double sum = 0;
                for (int j = 0; j < size; ++j) {
                    sum += getValue(j, i);
                }
                vector.push_back(sum);
            }
            break;

        case MeasureType::A_INF:
            for (int i = 0; i < size; ++i) {
                double sum = 0;
                for (int j = 0; j < size; ++j) {
                    sum += getValue(i, j);
                }
                vector.push_back(sum);
            }
            break;
    }

    return Vector(vector).max();
}

SquareMatrix SquareMatrix::operator-(double num) const {
    SquareMatrix res(size, false);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            res.setValue(i, j, getValue(i, j) - num);
        }
    }

    return res;
}

SquareMatrix SquareMatrix::operator-(SquareMatrix& matrix) const {
    SquareMatrix res(size, false);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            res.setValue(i, j, getValue(i, j) - matrix.getValue(i, j));
        }
    }

    return res;
}

SquareMatrix SquareMatrix::T() const {
    SquareMatrix res(size, false);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            res.setValue(i, j, getValue(j, i));
        }
    }
    return res;
}

std::vector<double> SquareMatrix::getSingularValues() const {
    std::vector<double> res;
    auto matrix = *this * T();
    std::cout << matrix;
    auto eigenValues = matrix.getEigenvalues();

    for (auto val: eigenValues) {
        res.emplace_back(sqrt(val));
    }

    return res;
}

double SquareMatrix::getConditionNumber() const {
    auto sortedSingularValues = getSingularValues();
    auto valuesCount = sortedSingularValues.size();
    std::sort(sortedSingularValues.begin(), sortedSingularValues.end());
    return sortedSingularValues[valuesCount - 1] / sortedSingularValues[0];
}
