#include "fraction.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace Numbers {

// anonymous namespace of helper functions for this compilation unit.
namespace {
    // calculate greatest common denominator

    uint32_t binary_gcd(int64_t first, int64_t second)
    {
        uint32_t a = std::abs(first);
        uint32_t b = std::abs(second);
        uint8_t shift = 0;

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

    // calculate the lowest common multiplication.
    int64_t lcm(int64_t a, uint64_t b)
    {
        return (a * b) / binary_gcd(a,b);
    }
}

Fraction::Fraction() : Fraction(0,1)
{}

Fraction::Fraction(int64_t number): Fraction(number,1)
{}

Fraction::Fraction(int64_t num, int64_t denum)
{
    // denumerator cannot be 0!
    // here we throw self defined exception.
    if (denum == 0) {
        throw std::runtime_error("denominator can't be zero!");
    }
    auto gcd = binary_gcd(num,denum);
    if (denum < 0) {
        numerator = -num / gcd;
        denumerator = -denum / gcd;
    } else {
        numerator = num / gcd;
        denumerator = denum / gcd;
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
    return (numerator >= 0)? *this : const_cast<const Fraction&&>(Fraction(-numerator, denumerator));
}

Fraction Fraction::operator*(const Fraction& another)const
{
    return Fraction(numerator*another.numerator, denumerator*another.denumerator);
}

Fraction Fraction::operator+(const Fraction& another) const
{
    int64_t a = (numerator * another.denumerator) + (another.numerator * denumerator);
    int64_t b = (denumerator * another.denumerator);
    return Fraction(a, b);
}

Fraction Fraction::operator-(const Fraction& another) const
{
    return this->operator + (Fraction(-another.numerator, another.denumerator));
}

Fraction Fraction::operator/(const Fraction& another) const 
{
    // you can't divide by 0 - throw an error.
    if (another.numerator == 0) {
        throw std::runtime_error("can't devide by 0!");
    }
    return this->operator * (Fraction(another.denumerator, another.numerator));
}

bool Fraction::operator<(const Fraction& another) const 
{
    const auto mul = lcm(another.denumerator, denumerator);
    return numerator * (mul/denumerator) < another.numerator*(mul/another.denumerator);
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
    return !this->operator == (another);
}

bool Fraction::operator==(const Fraction& another) const
{
    return (this->numerator == another.numerator) &&
        (this->denumerator == another.denumerator);
}

} // namespace Numbers
