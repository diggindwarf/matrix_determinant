#include "fraction.hpp"

#include <algorithm>
#include <stdexcept>
#include <cmath>

namespace Numbers {

// anonymous namespace of helper functions for this compilation unit.
namespace {
    // calculate greatest common denominator

    long long binary_gcd(long long first, long long second)
    {
        unsigned long long a = std::abs(first);
        unsigned long long b = std::abs(second);
        unsigned int shift = 0;

        if (a == 0) return b;
        if (b == 0) return a;

        while (((a | b) & 1) == 0) {
            shift++;
            a >>= 1;
            b >>= 1;
        }
        while ((a & 1) == 0)
            a >>= 1;

        do {
            while ((b & 1) == 0)
                b >>= 1;
            if (a > b) {
                std::swap(a,b);
            }
            b -= a;
        } while (b != 0);

        return a << shift;
    }

    // calculate lowest common multiplication.
    long long lcm(long long a, long long b)
    {
        return (a*b)/binary_gcd(a,b);
    }
}

Fraction::Fraction() : Fraction(0,1)
{}

Fraction::Fraction(long long number): Fraction(number,1)
{}

Fraction::Fraction(long long num, long long denum)
{
    // denumerator cannot be 0!
    // here we throw self defined exception.
    if (denum==0) {
        throw std::runtime_error("denominator can't be zero!");
    }
    auto gcd = binary_gcd(num,denum);
    if (denum<0) {
        numerator = -num/gcd;
        denumerator = -denum/gcd;
    } else {
        numerator = num/gcd;
        denumerator = denum/gcd;
    }
}
// copy constructor (unused for this project)
Fraction::Fraction(const Fraction& fraction)
{
    numerator = fraction.numerator;
    denumerator = fraction.denumerator;
}

Fraction Fraction::abs() const
{
    // since abs() is defined as const method derefered this is const object reference.
    // then: if a ? b : c 
    // both (b and c) value category (cv) and type in return of ternary(conditional) operator 
    // should be same. i need to cast it to const.
    return numerator>=0 ? *this : const_cast<const Fraction&&>(Fraction(-numerator, denumerator));
}

Fraction Fraction::operator*(const Fraction& another)const
{
    return Fraction(numerator*another.numerator, denumerator*another.denumerator);
}

Fraction Fraction::operator+(const Fraction& another) const
{
    // this will be shorten in constructor... might be 
    long long a = (numerator*another.denumerator) + (another.numerator*denumerator);
    long long b = (denumerator*another.denumerator);
    return Fraction(a, b);
}

Fraction Fraction::operator-(const Fraction& another) const
{
    return this->operator+(Fraction(-another.numerator, another.denumerator));
}

Fraction Fraction::operator/(const Fraction& another) const 
{
    // you can't devide by 0 - throw an error.
    if (another.numerator == 0) {
        throw std::runtime_error("can't devide by 0!");
    }
    return this->operator*(Fraction(another.denumerator, another.numerator));
}

bool Fraction::operator<(const Fraction& another) const 
{
    const auto mul = lcm(another.denumerator, denumerator);
    return numerator*(mul/denumerator) < another.numerator*(mul/another.denumerator);
}

bool Fraction::operator>(const Fraction& another) const
{
    return this->operator!=(another) && !this->operator<(another);
}

std::ostream& operator<<(std::ostream& os, const Fraction& fraction)
{
    if (fraction.denumerator == 1) {
    	os << fraction.numerator;
    } else {
        os << fraction.numerator << "/" << fraction.denumerator;
    }
    return os;
}

bool Fraction::operator!=(const Fraction& another) const
{
    return !this->operator==(another);
}

bool Fraction::operator==(const Fraction& another) const
{
    return (this->numerator == another.numerator) && 
        (this->denumerator == another.denumerator);
}

} // namespace Numbers
