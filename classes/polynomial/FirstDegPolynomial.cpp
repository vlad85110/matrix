//
// Created by Влад Кирилов on 06.09.2022.
//

#include "FirstDegPolynomial.h"

FirstDegPolynomial::FirstDegPolynomial(const double a, const double b) : a(a), b(b) {}

double FirstDegPolynomial::get_value(double x) const {
    return a * x + b;
}
