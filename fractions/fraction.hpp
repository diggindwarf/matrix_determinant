#pragma once
// this include is needed because of defined operator<< (std::ostream)
#include <cstdint>
#include <iostream>

namespace Numbers {
class Fraction
{
public:
    Fraction();
    Fraction(int64_t number);
    Fraction(int64_t numerator, int64_t denumerator);
    // copy constructor
    Fraction(const Fraction& fraction);
    // destructor
    ~Fraction() = default;
    // define own operators for basic math operations;
    // as shown: return value of this operation is just another
    // Fraction (result of operation)
    Fraction abs() const;

    Fraction operator*(const Fraction& another) const;
    Fraction operator/(const Fraction& another) const;
    Fraction operator+(const Fraction& another) const;
    Fraction operator-(const Fraction& another) const;
    // define own operators for fractions comparison.
    bool operator!=(const Fraction& another) const;
    bool operator==(const Fraction& another) const;
    bool operator<(const Fraction& another) const;
    bool operator>(const Fraction& another) const;
    // friend operator<< for proper printing of fraction when using output stream.
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
private:
    int64_t numerator;
    int64_t denumerator;
};
} // namespace Numbers