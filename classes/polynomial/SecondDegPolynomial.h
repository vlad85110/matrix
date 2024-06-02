//
// Created by Влад Кирилов on 05.09.2022.
//

#pragma once


#include <ostream>
#include <optional>
#include <vector>
#include <cmath>
#include "FirstDegPolynomial.h"

class SecondDegPolynomial {
private:
    const double a, b, c;
public:
    SecondDegPolynomial(double a, double b, double c);
    friend std::ostream &operator<<(std::ostream &os, const SecondDegPolynomial &polynomial);
    [[nodiscard]] double get_discriminant() const;
    [[nodiscard]] std::optional<std::vector<double>> get_roots() const;
    [[nodiscard]] const double getA() const;
    [[nodiscard]] double get_vertex() const;
    [[nodiscard]] double get_value(double x) const;
    [[nodiscard]] FirstDegPolynomial get_derivative() const;
};

