//
// Created by Влад Кирилов on 05.09.2022.
//

#include "math_functions.h"

int sgn(double val) {
    return (0 < val) - (val < 0);
}

bool is_sign_differs(Interval& interval) {
    return sgn(interval[0]) != sgn(interval[1]);
}

bool is_sign_differs(double x1, double x2) {
    return sgn(x1) != sgn(x2);
}

double get_interval_center(Interval& interval) {
    return (interval[0] + interval[1]) / 2;
}

double subtraction(double a, double b) {
    return a - b;
}

double addition(double a, double b) {
    return a + b;
}