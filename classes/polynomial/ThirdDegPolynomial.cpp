//
// Created by Влад Кирилов on 05.09.2022.
//

#include "ThirdDegPolynomial.h"
#include "math_functions.h"
#include <iostream>

double eps = pow(10,-7);

ThirdDegPolynomial::ThirdDegPolynomial(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}

std::ostream &operator<<(std::ostream &os, const ThirdDegPolynomial &polynomial) {
    os << polynomial.a << "x^3 + " << polynomial.b <<  "x^2 + " << polynomial.c <<  "x + " << polynomial.d;
    return os;
}

SecondDegPolynomial ThirdDegPolynomial::get_derivative() const {
    return SecondDegPolynomial{a * 3, b * 2, c};
}

std::optional<std::vector<double>> ThirdDegPolynomial::get_inflection_points() const {
    return get_derivative().get_roots();
}

std::vector<double> ThirdDegPolynomial::get_roots() const {
    auto roots = std::vector<double>();
    auto inflection_points = get_inflection_points();
    double start_point, root;

    if (!inflection_points.has_value()) {
        start_point = get_derivative().get_vertex();
        root = find_one_root(start_point);
        roots.push_back(root);
        return roots;
    }

    auto points_cnt = inflection_points.value().size();
    if (points_cnt == 2) {
        Interval interval;
        for (auto point: inflection_points.value()) {
            interval.push_back(point);
        }
        std::sort(interval.begin(), interval.end());

        if (is_root(interval[0], eps)) {
            roots.push_back(interval[0]);
            root = find_one_root(interval[1]);
            roots.push_back(root);
            return roots;
        }

        if (is_root(interval[1], eps)) {
            roots.push_back(interval[1]);
            root = find_one_root(interval[0]);
            roots.push_back(root);
            return roots;
        }

        if (is_sign_differs(get_value(interval[0]), get_value(interval[1]))) {
            roots.push_back(get_root(interval, eps));
            roots.push_back(get_side_root(interval[0], Left));
            roots.push_back(get_side_root(interval[1], Right));
        } else {
            if (sgn(interval[0]) < 0) {
                for (auto point: interval) {
                    if (is_minimum(point)) {
                        root = find_one_root(point);
                        roots.push_back(root);
                    }
                }
            } else if (sgn(interval[0]) > 0) {
                for (auto point: interval) {
                    if (is_maximum(point)) {
                        root = find_one_root(point);
                        roots.push_back(root);
                    }
                }
            }
        }

        return roots;
    }

    if (points_cnt == 1) {
        start_point = inflection_points.value()[0];
        root = find_one_root(start_point);
        roots.push_back(root);
        return roots;
    }

    return roots;
}

double ThirdDegPolynomial::get_value(double x) const{
    return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
}

double ThirdDegPolynomial::get_root(Interval& interval, double epse) const {
    auto center = get_interval_center(interval);

    Interval new_interval(interval);
    auto interval_len = new_interval[1] - new_interval[0];
    while (abs(get_value(center) - 0) > epse) {
        if (is_sign_differs(get_value(center), get_value(new_interval[0]))) {
            new_interval.clear();
            new_interval.push_back(new_interval[0]);
            new_interval.push_back(center);
        }

        if (is_sign_differs(get_value(center), get_value(new_interval[1]))) {
            new_interval.clear();
            new_interval.push_back(center);
            new_interval.push_back(new_interval[1]);
        }

        center = get_interval_center(new_interval);
    }

    return center;
}

double ThirdDegPolynomial::get_side_root(double end_point, Sides way) const {
    Interval res;
    double len = 1;

    double (*function)(double, double);
    if (way == Right) {
        function = addition;
    } else {
        function = subtraction;
    }

    double new_end = function(end_point, len);
    while (!is_sign_differs(get_value(end_point), get_value(new_end))) {
        len *= 1.3;
        new_end = function(end_point, len);
    }

    res.push_back(end_point);
    res.push_back(new_end);
    std::sort(res.begin(), res.end());

    return get_root(res, eps);
}

double ThirdDegPolynomial::find_one_root(double start_point) const {
    double root;

    if (is_root(start_point, eps)) {
        return start_point;
    }

    auto derivative_sgn = sgn(get_derivative().getA());
    bool left = derivative_sgn > 0 ^ get_value(start_point) < 0;

    if (left) {
        root = get_side_root(start_point, Left);
    } else {
        root = get_side_root(start_point, Right);
    }

    return root;
}

bool ThirdDegPolynomial::is_minimum(double point) const {
    return get_derivative().get_derivative().get_value(point) > 0;
}

bool ThirdDegPolynomial::is_maximum(double point) const {
    return get_derivative().get_derivative().get_value(point) < 0;
}

bool ThirdDegPolynomial::is_root(double point, double epse) const {
    return abs(get_value(point) - 0) <= epse;
}


