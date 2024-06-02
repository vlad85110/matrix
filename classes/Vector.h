#pragma once

#include <vector>
#include <ostream>


class Vector {
    friend class SquareMatrix;
private:
    std::vector<double> data;
public:
    explicit Vector(size_t size);
    Vector(size_t size, double num);
    explicit Vector(std::vector<double>& v);
    void initWithSinus(double size);
    Vector operator*(double num) const;
    double operator*(Vector &vector) const;
    Vector operator-(const Vector &vector) const;
    Vector operator+(const Vector &vector) const;
    double operator[] (size_t index) const;
    Vector& operator=(const Vector &vector);
    [[nodiscard]] double measure() const;
    [[nodiscard]] double max() const;
    explicit operator std::vector<double>&();

    friend std::ostream &operator<<(std::ostream &os, const Vector &vector);
    void perm(std::shared_ptr<int[]>& permutation);
    void setValue(size_t index, double value);
    void add(size_t index, double value);
};


