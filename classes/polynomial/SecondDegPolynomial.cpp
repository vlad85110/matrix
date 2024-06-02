//
// Created by Влад Кирилов on 05.09.2022.
//

#include "SecondDegPolynomial.h"

SecondDegPolynomial::SecondDegPolynomial(double a, double b, double c) : a(a), b(b), c(c) {}

std::ostream &operator<<(std::ostream &os, const SecondDegPolynomial &polynomial) {
    os << polynomial.a << "x^2 + " << polynomial.b << "x + " << polynomial.c;
    return os;
}

double SecondDegPolynomial::get_discriminant() const {
    return pow(b, 2) - 4 * a * c;
}

std::optional<std::vector<double>> SecondDegPolynomial::get_roots() const {
    auto discriminant = get_discriminant();
    if (discriminant < 0) {
        return std::nullopt;
    } else if (discriminant == 0) {
        auto x = -((double )b / 2) / a;
        return std::vector<double>{x};
    } else {
        auto x1 = (-b - sqrt(discriminant)) / (2 * a);
        auto x2 = (-b + sqrt(discriminant)) / (2 * a);
        return std::vector<double>{x1, x2};
    }
}

double SecondDegPolynomial::get_value(double x) const {
    return a * x*x + b * x + c;
}

const double SecondDegPolynomial::getA() const {
    return a;
}

double SecondDegPolynomial::get_vertex() const {
    return -b / 2 / a;
}

FirstDegPolynomial SecondDegPolynomial::get_derivative() const {
    return FirstDegPolynomial{2 * a, b};
}
