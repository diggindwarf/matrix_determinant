#include "fractions/fraction.hpp"
#include "determinant_calculation/calc_det.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <cctype>

using namespace Numbers;

// print matrix by iterating through whole matrix, and printing element
// one-by-one to standard output stream. For printing fractions, we needed
// to implement an overload of operator<<.
void print_matrix(const Matrix& matrix)
{
    std::cout <<
        std::endl <<
        "User provided matrix:" <<
        std::endl;
    // standard for-each loop.
    // for each row in matrix (std::vector<Fraction>)
    for ( auto& row: matrix ) {
        // standard for-each loop
        // for each element in row (Fraction)
        for ( auto& element: row ) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}
// function which parse string provided by user: it checks 
// if size is proper, and  
std::vector<Fraction> parse_row(std::string& row, int size) 
{
    std::istringstream iss(row);
    std::string str;
    std::vector<Fraction> row_vector;
    while (iss >> str) {
        // at first, we assume, that provided value is positive.
        bool is_positive = true;
        // check if value is negative;
        if (*str.begin() == '-') {
            // iterator to first char in char array under string.
            auto first = str.begin();
            // first in algorithm below must be digit - if negative value
            // is provided than we should start from second number.
            first++;
            // if '-' was the only char in string - that we should throw
            // an error.
            str = std::string(first, str.end());
            is_positive = false;
        }
        auto is_digit = [](unsigned char c){ return std::isdigit(c); };
        //here is algorithm, which is checking if all values are digits.
        if (!std::all_of(str.begin(), str.end(), is_digit)) {
            throw std::runtime_error("Incorrect value in row provided!");
        } else {
            auto number = std::stoi(str);
            number = is_positive? number : -number;
            row_vector.push_back(Fraction(number));
        }
    }
    // for square matrixes size of a row must be equal to number of rows (7x7 by example.)
    // also - all rows in any matrix must be same size.
    if (row_vector.size() != size) {
        throw std::runtime_error("Incorect number of elements!");
    }
    return row_vector;
}

Matrix parse_matrix(int size)
{
    Matrix matrix;
    //standard for loop, with counter i;
    for (int i = 0; i < size; i++) {
        std::string input;
        std::cout << "row " << i+1 << ":";
        // here we are trying to get proper value of row in matrix from user.
        // this is: space separated integer values.
        std::getline(std::cin, input);
        try {
            // if parse_row does not throw error - than push back new row to matrix.
            matrix.push_back(parse_row(input, size));
        } catch (std::runtime_error& e) {
            // if runtime error was thrown, write to console message of this error.
            std::cout <<
                e.what() <<
                std::endl;
            // decrement i value, for user to pass proper value of matrix row.
            --i;
        }
    }
    return matrix;
}

int run_program()
{
    // Determinant can only be calculated from square matrixes;
    // program will exit with warning message
    std::cout << "What is size of matrix?" << std::endl;
    int a;
    std::cin >> a;
    while (!std::cin.good() || a <= 0) {
        std::cout <<
            "Incorrect value provided! Value must be positive integer!" <<
            std::endl <<
            "Enter positive integer:" <<
            std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> a;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    auto matrix = parse_matrix(a);
    print_matrix(matrix);
    Fraction determinant;
    try {
        determinant = calculate_determinant(matrix);
    } catch ( std::runtime_error& e ) {
        std::cerr << "program meet runtime problem: " << e.what() << std::endl;
        // if return value for main is different than 0, it means, that there was problem.
        // and program does not succesfully finish job.
        return 1;
    }
    // print determinant value.
    std::cout <<
        std::endl <<
        "determinant of above matrix is equal: " <<
        determinant <<
        std::endl;
    // return 0 in main means, that program has succesfully finish job.
    return 0;
}

int main(int argc, char** argv)
{
    return run_program();
}