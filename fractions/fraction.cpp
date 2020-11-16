#include "fraction.hpp"

#include <algorithm>

namespace Numbers {

//anonymous namespace of helper functions for this compilation unit.
namespace {
    //calculate absolute value of number;
    unsigned int abs(int a)
    {
        return a>=0?a:-a;
    }

    //calculate greatest common denominator

    int binary_gcd(int first, int second)
    {
        unsigned int a = abs(first);
        unsigned int b = abs(second);
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
    int lcm(int a, int b)
    {
        return (a*b)/binary_gcd(a,b);
    }
}

Fraction::Fraction() : Fraction(0,1)
{}

Fraction::Fraction(int number): Fraction(number,1)
{}

Fraction::Fraction(int num, int denum)
{
    //denumerator cannot be 0!
    //here we throw self defined exception.
    if (denum==0) {
        std::cout << "denumerator can't be 0!";
    }
    auto gcd = binary_gcd(num,denum);
    numerator = num/gcd;
    denumerator = denum/gcd;
}

Fraction Fraction::operator*(const Fraction& another)
{
    return Fraction(numerator*another.numerator, denumerator*another.denumerator);
}

Fraction Fraction::operator+(const Fraction& another)
{
    int a = (numerator*another.denumerator) + (another.numerator*denumerator);
    int b = (denumerator*another.denumerator);
    return Fraction(a, b);
}

Fraction Fraction::operator-(const Fraction& another)
{
    return this->operator+(Fraction(-another.numerator, another.denumerator));
}

Fraction Fraction::operator/(const Fraction& another)
{
    // you can't devide by 0 - we don't want program to break in such situation
    if (another.numerator == 0){
        std::cout<< "What happened?";
        return Fraction();
    }
    return Fraction(numerator*another.denumerator, denumerator*another.numerator);
}

bool Fraction::operator<(const Fraction& another)
{
    const auto mul = lcm(another.denumerator, denumerator);
    return numerator*mul < another.numerator*mul;
}

bool Fraction::operator>(const Fraction& another)
{
    return !this->operator!=(another) && !this->operator<(another);
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

bool Fraction::operator!=(const Fraction& another)
{
    return !this->operator==(another);
}

bool Fraction::operator==(const Fraction& another)
{
    return (this->numerator == another.numerator) && (this->denumerator == another.denumerator);
}

} //namespace Numbers
