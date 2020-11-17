#include "fractions/fraction.hpp"
#include "determinant_calculation/calc_det.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

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
    std::cout << "Matrix:" << std::endl;
    for ( auto& row: matrix ) {
        for ( auto& element: row ) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

Matrix parse_matrix(int size)
{
    Matrix matrix;
    //standard for loop, with counter i;
    for (int i = 0; i < size; i++) {
        matrix.push_back(std::vector<Fraction>());
        std::string input;
        std::cout << "row " << i+1 << ":";
        std::getline(std::cin, input);
        std::cin.clear();
        std::istringstream iss(input);
        int number;

        while (iss >> number) {
            if (iss.fail()) {
                std::cerr << "Incorrect value in row provided! Please pass proper row (INTEGERS ONLY)!";
                matrix.pop_back();
                i--;
            } else {
            matrix[i].push_back(Fraction(number));
            }
        }
    }
    return matrix;
}

int main(int argc, char** argv)
{
    // Determinant can only be calculated from square matrixes;
    // program will exit with warning message
    std::cout << "What is size of matrix?" << std::endl;
    int a;
    std::cin >> a;
    while(!std::cin.good() || a <= 0){
        std::cerr << "Incorrect value provided! Value must be positive integer!"
            << "Enter positive integer ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> a;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    auto matrix = parse_matrix(a);
    print_matrix(matrix);

    try {
        std::cout << "determinant value is: " << calculate_determinant(matrix) << std::endl;
    } catch (std::runtime_error& e) {
        std::cerr << "program meet runtime problem: " << e.what() << std::endl;
        return 1;
    }
    // return 0 in main means, that program has succesfully finish job.
    return 0;
}