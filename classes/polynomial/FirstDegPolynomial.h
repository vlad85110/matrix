//
// Created by Влад Кирилов on 06.09.2022.
//

#pragma once

class FirstDegPolynomial {
private:
   const double a, b;
public:
    FirstDegPolynomial(const double a, const double b);
    [[nodiscard]] double get_value(double x) const;
};


