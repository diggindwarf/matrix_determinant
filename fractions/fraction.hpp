#pragma once
//this include is needed because of defined operatator<< (std::ostream)
#include <iostream>

namespace Numbers {
class Fraction
{
    public:
    Fraction();
    Fraction(int number);
    Fraction(int numerator, int denumerator);
    //define own operators for basic math operations;
    // as shown: return value of this operation is just another
    // Fraction (result of operation)
    Fraction operator* (const Fraction& another);
    Fraction operator/ (const Fraction& another);
    Fraction operator+ (const Fraction& another);
    Fraction operator- (const Fraction& another);
    //define own operators for value comparison.
    bool operator!= (const Fraction& another);
    bool operator== (const Fraction& another);
    bool operator< (const Fraction& another);
    bool operator> (const Fraction& another);
    //friend operator<< for proper printing of fraction when using output stream.
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
    private:
    int numerator;
    int denumerator;
};
} //namespace Numbers