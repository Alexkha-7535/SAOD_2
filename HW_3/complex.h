#ifndef SEMINAR3_COMPLEX_H
#define SEMINAR3_COMPLEX_H

#include <iostream>

class Complex {
public:
    double Re, Im;

    Complex(double re = 0, double im = 0);

    Complex operator +(const Complex& c) const;
    Complex operator -(const Complex& c) const;
    Complex operator *(const Complex& c) const;
    Complex operator /(const Complex& c) const;

    Complex Conjugate() const;
    double Mod() const;
    double Arg() const;

    static double GetPI();
};

inline std::ostream& operator <<(std::ostream& o, const Complex& c)
{
    return o << '(' << c.Re << ", " << c.Im << ')';
}

#endif //SEMINAR3_COMPLEX_H
