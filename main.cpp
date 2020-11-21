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
// function which parses string provided by user: it checks 
// if size of row is proper, and if each value is correct
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
            // iterator to first element in char array under string.
            auto first = str.begin();
            // move to second element of string.
            first++;
            // create new string starting from second element.
            // and pass it to str variable.
            str = std::string(first, str.end());
            is_positive = false;
        }
        auto is_digit = [](unsigned char c){ return std::isdigit(c); };
        // we are checking if str is empty, or is not a number.
        // std::all_of(str.begin(), str.end(), is_digit)
        // is checking if all elements in str are digits.
        if (str.empty() || !std::all_of(str.begin(), str.end(), is_digit)) {
            throw std::runtime_error("Incorrect value in row provided!");
        } else {
            auto number = std::stoi(str);
            number = is_positive? number : -number;
            row_vector.push_back(Fraction(number));
        }
    }
    // for square matrixes, the size of a row must be equal to number of rows (eg. 7x7)
    // also - all rows in any matrix must be the same size.
    if (row_vector.size() != size) {
        throw std::runtime_error("Incorect number of elements!");
    }
    return row_vector;
}

Matrix parse_matrix(int size)
{
    Matrix matrix;
    // standard for loop, with i counter;
    for (int i = 0; i < size; i++) {
        std::string input;
        std::cout << "row " << i+1 << ":";
        // here we are trying to get proper value of next matrix row from user.
        // correct form is: space separated integer values.
        std::getline(std::cin, input);
        try {
            // if parse_row does not throw error - then push back new row to matrix.
            matrix.push_back(parse_row(input, size));
        } catch (std::runtime_error& e) {
            // if runtime error was thrown, write error message to console.
            // this error means that the row provided by user was not correct.
            std::cout <<
                e.what() <<
                std::endl;
            // decrement i value. User can once again pass value of matrix row.
            // this will repeat loop iteration until user passes correct value.
            --i;
        }
    }
    return matrix;
}

int run_program()
{
    // Determinant can only be calculated from square matrixes.
    std::cout << "What is the size of matrix?" << std::endl;
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
        // try to calculate determinant of provided matrix
        determinant = calculate_determinant(matrix);
    } catch (std::runtime_error& e) {
        std::cerr << "program met runtime problem: " << e.what() << std::endl;
        // if return value for main is different than 0, it means that there was a problem.
        // Program does not successfully finish job.
        return 1;
    }
    // print determinant value.
    std::cout <<
        std::endl <<
        "determinant of above matrix is equal: " <<
        determinant <<
        std::endl;
    // return 0 in main means that program does successfully finish job.
    return 0;
}

int main(int argc, char** argv)
{
    return run_program();
}