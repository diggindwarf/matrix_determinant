#include <utility>
#include <stdexcept>

#include "calc_det.hpp"

using namespace Numbers;

namespace Exceptions {

class DegeneratedMatrixException : std::exception
{
    public:
    const char * what () const throw ()
    {
    	return "Exception: Matrix is degenerated:";
    }
};

}// namespace Exceptions

// take matrix as reference, and permutate it for our purposes.
// bool return value is sign of permutation
// true = 1.
// false = -1.
bool permutate_matrix(Matrix& perm_mat)
{
    int swap_count = 0;
    for ( int i = 0; i < perm_mat.size(); i++ )
    {
        int max_value_index = i;
        auto max_value = Fraction();
        // write lambda for this.
        for ( int j = i; j < perm_mat.size(); j++ )
        {
            if ( max_value < perm_mat.at(j).at(i) )
            {
                max_value = perm_mat.at(j).at(i);
                max_value_index = j;
            }
        }
        // swap rows of matrix.
        if (max_value == 0) {
            throw DegeneratedMatrixException();
        }
        if ( max_value_index != i )
        {
            perm_mat[i].swap(perm_mat[max_value_index]);
            swap_count++;
        }
        for (int j = i + 1; j < perm_mat.size(); j++) {
            perm_mat[j][i] = 
                perm_mat.at(j).at(i)/perm_mat.at(i).at(i);
            for (int k = i + 1; k < perm_mat.size(); k++) {
                perm_mat[j][k] = 
                    perm_mat.at(j).at(k) - (perm_mat.at(j).at(i)*perm_mat.at(i).at(k));
            }
        }
    }
    return ( swap_count % 2 ) == 0;
}

std::pair<Matrix, bool> LU_decompose(const Matrix& matrix)
{
    Matrix perm_mat = matrix;
    bool sign = permutate_matrix(perm_mat);
    return std::make_pair(perm_mat, sign);
}
// arguments: sign of permutation
Numbers::Fraction LU_determinant_value(const Matrix& matrix, const bool sign)
{
    Fraction determinant = Fraction(1);
    for (int i = 0; i < matrix.size(); i++) {
        determinant = determinant * matrix.at(i).at(i);
    }
    return sign ? determinant: Fraction(0)-determinant;
}

// LU algorithm based function
Numbers::Fraction calculate_determinant(const Matrix& matrix)
{
    std::pair<Matrix, bool> LU_decomposition_pair;
    try {
        LU_decomposition_pair = LU_decompose(matrix);
    } catch (const Exceptions::DegeneratedMatrixException& e) {
        std::cout << e.what();
        return Fraction();
    }

    return LU_determinant_value(
       LU_decomposition_pair.first,
       LU_decomposition_pair.second
    );
}