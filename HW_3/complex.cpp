#include "complex.h"

#include <cmath>

Complex::Complex(double re, double im) : Re(re), Im(im) {}

Complex Complex::operator +(const Complex& c) const {
    return Complex(Re + c.Re, Im + c.Im);
}

Complex Complex::operator -(const Complex& c) const {
    return Complex(Re - c.Re, Im - c.Im);
}

Complex Complex::operator *(const Complex& c) const {
    return Complex(Re * c.Re - Im * c.Im,
        Re * c.Im + Im * c.Re);
}

Complex Complex::operator /(const Complex& c) const {
    double denominator = c.Re * c.Re + c.Im * c.Im;
    return Complex((Re * c.Re + Im * c.Im) / denominator,
        (Im * c.Re - Re * c.Im) / denominator);
}

Complex Complex::Conjugate() const {
    return Complex(Re, -Im);
}

double Complex::Mod() const {
    return sqrt(Re * Re + Im * Im);
}

double Complex::Arg() const {
    if (Mod() == 0) return 0;
    if (Re > 0) return atan(Im / Re);
    if (Re < 0) {
        if (Im >= 0) return acos(-1.0) + atan(Im / Re);
        return -acos(-1.0) + atan(Im / Re);
    }

    if (Im > 0) return acos(-1.0) / 2;
    if (Im < 0) return -acos(-1.0) / 2;
    return 0;
}

double Complex::GetPI()
{
    return acos(-1.0);
}