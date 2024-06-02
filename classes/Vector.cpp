#include "Vector.h"
#include <iostream>
#include <cmath>
#include <algorithm>


static const double PI = 3.14159265358979323846;

Vector::Vector(size_t size, double num) : data(size, num) {}

Vector::Vector(size_t size) : data(size, 0) {}

Vector::Vector(std::vector<double>& v) : data(v){}

Vector Vector::operator*(double num) const {
    auto size = this->data.size();
    Vector result(size);
    for (auto i = 0; i < size; ++i) {
        result.data[i] = (*this)[i] * num;
    }
    return result;
}

double Vector::measure() const {
    double mes = 0;
    for (auto & it: data)
        mes += it * it;
    return sqrt(mes);
}

Vector::operator std::vector<double>&() {
    return data;
}

double Vector::operator[](size_t index) const {
    if (index >= data.size()) {
        return 0;
    }

    return data[index];
}

Vector Vector::operator-(const Vector &vector) const {
    auto size = this->data.size();
    Vector result(this->data.size());
    for (auto i = 0; i < size; ++i) {
        result.data[i] = this->data[i] - vector[i];
    }
    return result;
}

void Vector::initWithSinus(double size) {
    for (auto i = 0; i < data.size(); ++i) {
        data[i] = sin(2 * PI * i / size);
    }
}

double Vector::max() const {
    return *std::max_element(data.begin(), data.end());

}

std::ostream &operator<<(std::ostream &os, const Vector &vector) {
    for (auto it : vector.data) {
        os << std::fixed << it << std::endl;
    }
    return os;
}

void Vector::perm(std::shared_ptr<int[]>& permutation) {
    auto prev = std::vector(data);

    for (int i = 0; i < data.size(); ++i) {
        data[i] = prev[permutation[i]];
    }
}

void Vector::setValue(size_t index, double value) {
    data[index] = value;
}

Vector Vector::operator+(const Vector& vector) const {
    auto size = this->data.size();
    Vector result(size);

    for (auto i = 0; i < size; ++i) {
        result.data[i] = this->data[i] + vector[i];
    }

    return result;
}

double Vector::operator*(Vector &vector) const {
    double res = 0;

    for (int i = 0; i < data.size(); ++i) {
        res += data[i] * vector[i];
    }

    return res;
}

void Vector::add(size_t index, double value) {
    data[index] += value;
}

Vector& Vector::operator=(const Vector& v) = default;



