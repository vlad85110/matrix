#pragma once

#include <vector>
#include <ostream>
#include "Vector.h"

enum class MeasureType {
     A1,
     A_INF
};

class SquareMatrix {
private:
    std::vector<double> data;
    size_t size;
public:
    explicit SquareMatrix(size_t size, bool isOne);
    explicit SquareMatrix(std::vector<double>& data);

    Vector operator*(const Vector &vector) const;
    SquareMatrix operator*(const SquareMatrix &matrix) const;
    SquareMatrix operator*(double num) const;
    SquareMatrix operator-(double num) const;
    SquareMatrix operator-(SquareMatrix& matrix) const;
    friend std::ostream &operator<<(std::ostream &os, const SquareMatrix &matrix);
    void setValue(int row, int col, double value);
    [[nodiscard]] double getValue(size_t row, size_t col) const;
    void add(int row, int col, double value);
    [[nodiscard]] size_t getSize() const;
    [[nodiscard]] int count_zeros(size_t row) const;
    void swap_rows(size_t i, size_t j);
    std::shared_ptr<int[]> sort_rows();
    [[nodiscard]] double determinant() const;
    [[nodiscard]] std::vector<double> getEigenvalues() const;
    [[nodiscard]] std::vector<double> getSingularValues() const;
    [[nodiscard]] double getConditionNumber() const;
    [[nodiscard]] double measure(MeasureType type) const;
    [[nodiscard]] SquareMatrix T() const;
};


