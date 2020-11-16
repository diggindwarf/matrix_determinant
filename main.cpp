#include "fractions/fraction.hpp"
#include "determinant_calculation/calc_det.hpp"

#include <iostream>
#include <vector>
#include <utility>

// C library 
#include <getopt.h>

// TODO ===================================================================
// add function for passing fractions (somekind of parser)
// add function for passing whole matrix...
// and add switch statement - a in main function, we can have some options...
using namespace Numbers;

// print matrix by iterating through whole matrix, and printing element
// one-by-one to standard output stream. For printing fractions, we needed
// to implement an overload of operator<<.
void print_matrix(const Matrix& matrix)
{
    // for-each loop: thanks to auto (std 11) i do not have to use
    // whole type of reference on loop ( which is std::vector<Fraction>
    // for row, and Fraction for element )
    // https://en.cppreference.com/w/cpp/language/auto
    for ( auto& row: matrix ) {
        for ( auto& element: row ) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** argv)
{
    // Determinant can only be calculated from square matrixes;
    // in this program, size of this matrix is unsigned int.
    // if value passed to main is wrong (not integer or negative)
    // program will exit with warning message.
    while ((c = getopt_long_only(argc, argv) "", ))
    unsigned int size = 4;
    Matrix matrix;
    //standard for loop, with counter i;
    for (int i = 0; i < size; i++){
        std::cout << i+1 << " row: " << std::endl;
        // here we are adding new row of matrix.
        matrix.push_back(std::vector<Fraction>());
        for (int j = 0; j<size; j++) {
            int a;
            std::cin >> a;
            // here, i am refering to specific row within matrix.
            matrix[i].push_back(Fraction(a));
        }
    }
    std::cout << matrix.size();
    print_matrix(matrix);
    std::cout << "determinant value: " << calculate_determinant(matrix);
}