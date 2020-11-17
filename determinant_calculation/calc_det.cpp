#include <memory>
#include <utility>
#include <stdexcept>

#include "calc_det.hpp"

using namespace Numbers;

namespace Exceptions {

// derived self defined exception for degenerated matrixes.
class DegeneratedMatrixException : std::exception
{
    public:
    const char * what () const throw ()
    {
    	return "Exception: Matrix is degenerated:";
    }
};

} // namespace Exceptions

// helper function for cleanup.
// fuction return index of row with largest value
// in yet column within not parsed rows.
unsigned int get_row_to_swap_with_current(
    const Matrix& matrix,
    const int current_row)
{
    int max_value_index = current_row;
    auto max_value = Fraction();

    for (unsigned int j = current_row; j < matrix.size(); j++) {
        if ( max_value < matrix.at(j).at(current_row).abs())
            {
                max_value = matrix.at(j).at(current_row).abs();
                max_value_index = j;
            }
    }
    return max_value_index;
}

// Lower and Upper matrixes are stored at same collection.
// (since both are triangular)
void process_LU_decomposition(
    Matrix& matrix,
    const int current_row)
{
    for (int j = current_row + 1; j < matrix.size(); j++) {
        matrix[j][current_row] = 
            matrix.at(j).at(current_row)/matrix.at(current_row).at(current_row);
        for (int k = current_row + 1; k < matrix.size(); k++) {
            matrix[j][k] = 
                matrix.at(j).at(k) - (matrix.at(j).at(current_row)*matrix.at(current_row).at(k));
        }
    }
}

std::pair<Matrix, bool> LU_decompose(const Matrix& matrix)
{
    Matrix perm_mat = matrix;
    int swap_count = 0;
    for (unsigned int row = 0; row < perm_mat.size(); row++)
    {
        auto max_value_row = get_row_to_swap_with_current(perm_mat, row);
        // There is no need to continue calculating of determinant if: 
        if (perm_mat.at(max_value_row).at(row) == Fraction()) {
            throw Exceptions::DegeneratedMatrixException();
        }
        // if row with biggest number on index same as row number
        // is different than current row, than swap rows.
        if ( max_value_row != row ) {
            perm_mat[row].swap(perm_mat[max_value_row]);
            swap_count++;
        }
        process_LU_decomposition(perm_mat, row);
    }
    return std::make_pair(perm_mat, !(swap_count & 1));
}

Fraction LU_determinant_value(
    const Matrix& matrix,
    const bool sign)
{
    //neutral element of multiplication for beggining.
    Fraction determinant = Fraction(1);
    for (int i = 0; i < matrix.size(); i++) {
        // I could overload also *= operator for this manner, but
        // I do not see enough advantages.
        // here we are calculating finally determinant - by multiplication of diagonal.
        determinant = determinant * matrix.at(i).at(i);
    }
    // sign is not "sign" before number: it only tells us, if we should 
    // negate value of calculated determinant (due to row swaps)
    return sign ? determinant: Fraction(0)-determinant;
}

Fraction calculate_determinant(const Matrix& matrix)
{
    std::pair<Matrix, bool> LU_decomposition_pair;
    try {
        LU_decomposition_pair = LU_decompose(matrix);
    } catch (const Exceptions::DegeneratedMatrixException& e) {
        std::cout << e.what();
        // determinant of degenerated matix is equal to zero.
        return Fraction();
    }

    return LU_determinant_value(
       LU_decomposition_pair.first,
       LU_decomposition_pair.second
    );
}