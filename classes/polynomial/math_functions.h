//
// Created by Влад Кирилов on 05.09.2022.
//

#pragma once


#include <vector>

using Interval = std::vector<double>;

int sgn(double val);

bool is_sign_differs(Interval& interval);

bool is_sign_differs(double x1, double x2);

double get_interval_center(Interval& interval);

double subtraction(double a, double b);

double addition(double a, double b);