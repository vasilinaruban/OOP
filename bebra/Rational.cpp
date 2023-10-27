#include "Rational.h"
#include <sstream>

Rational::Rational(): num(1), denom(1){}

Rational::Rational(int numerator, int denominator) {
    if (denominator == 0) {
        std::stringstream ss;
        ss << "Argument must not be zero";
        throw std::invalid_argument(ss.str());
    }

    num = numerator;
    denom = denominator;
}

int Rational::Numerator() const{
    return num;
}

int Rational::Denominator() const{
    return denom;
}

Rational operator+(const Rational &a, const Rational &b){
    return {a.num * b.denom + b.num * a.denom, a.denom * b.denom};
}

Rational operator*(const Rational &a, const Rational &b){
    return {a.num * b.num, a.denom * b.denom};
}

Rational operator/(const Rational &a, const Rational &b){
    return a * Rational(b.denom, b.num);
}

Rational operator-(const Rational &a, const Rational &b){
    return {a.num * b.denom - b.num * a.denom, a.denom * b.denom};
}

bool operator==(const Rational &a, const Rational &b){
    return (a.num * b.denom == a.denom * b.num);
}

std::ostream &operator<<(std::ostream &out, const Rational &a){
    out << a.num << "/" << a.denom;
    return out;
}

std::istream &operator>>(std::istream &in, Rational &a){
    char c;
    in >> a.num >> c >> a.denom;
    return in;
}

Rational::~Rational() = default;