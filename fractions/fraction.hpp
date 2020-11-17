#pragma once
//this include is needed because of defined operatator<< (std::ostream)
#include <iostream>

namespace Numbers {
class Fraction
{
public:
    Fraction();
    Fraction(long long number);
    Fraction(long long numerator, long long denumerator);
    //copy constructor
    Fraction(const Fraction& fraction);
    //destructor
    ~Fraction() = default;
    //define own operators for basic math operations;
    // as shown: return value of this operation is just another
    // Fraction (result of operation)
    Fraction abs() const;

    Fraction operator* (const Fraction& another) const;
    Fraction operator/ (const Fraction& another) const;
    Fraction operator+ (const Fraction& another) const;
    Fraction operator- (const Fraction& another) const;
    //define own operators for value comparison.
    bool operator!= (const Fraction& another) const;
    bool operator== (const Fraction& another) const;
    bool operator< (const Fraction& another) const;
    bool operator> (const Fraction& another) const;
    //friend operator<< for proper printing of fraction when using output stream.
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
private:
    long long numerator;
    long long denumerator;
};
} //namespace Numbers