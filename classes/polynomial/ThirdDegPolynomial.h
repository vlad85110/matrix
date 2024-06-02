//
// Created by Влад Кирилов on 05.09.2022.
//

#pragma once


#include <ostream>
#include <optional>
#include <vector>
#include "SecondDegPolynomial.h"
#include "math_functions.h"
#include "Sides.h"


class ThirdDegPolynomial {
private:
    const double a, b, c, d;
    [[nodiscard]] double get_root(Interval& interval, double epse) const;
    [[nodiscard]] double get_side_root(double end_point, Sides way) const;
    [[nodiscard]] double find_one_root(double start_point) const;
    [[nodiscard]] bool is_maximum(double point) const;
    [[nodiscard]] bool is_minimum(double point) const;
    [[nodiscard]] bool is_root(double point, double eps) const;
public:
    ThirdDegPolynomial(double a, double b, double c, double d);
    friend std::ostream &operator<<(std::ostream &os, const ThirdDegPolynomial &polynomial);
    [[nodiscard]] double get_value(double x) const;
    [[nodiscard]] SecondDegPolynomial get_derivative() const;
    [[nodiscard]] std::optional<std::vector<double>> get_inflection_points() const;
    [[nodiscard]] std::vector<double> get_roots() const;
};


