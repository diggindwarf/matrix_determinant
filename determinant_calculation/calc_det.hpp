#pragma once

#include <vector>
#include "../fractions/fraction.hpp"

// thanks to alias Matrix below, within scope of this compilation unit
// I do not have to repeat std::vector<std::vector<Fraction>>
// when refering to myself defined matrix.
using Matrix = std::vector<std::vector<Numbers::Fraction>>;

Numbers::Fraction calculate_determinant(const Matrix& matrix);