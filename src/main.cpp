#include "matrix.h"
#include <iostream>

namespace matrix {
/// @brief Демонстрация базовых операций.
void demo_basic() {
    double a[] = {1, 2, 3, 4};
    double b[] = {5, 6, 7, 8};
    Matrix A{}, B{}, sum{}, product{};
    try {
        A = matrix_from_array(a, 2, 2);
        B = matrix_from_array(b, 2, 2);
        sum = matrix_add(A, B);
        product = matrix_multiply(A, B);
        std::cout << "Matrix A:\n"; print_matrix(A);
        std::cout << "Matrix B:\n"; print_matrix(B);
        std::cout << "A+B:\n"; print_matrix(sum);
        std::cout << "A*B:\n"; print_matrix(product);
    } catch (...) {
        free_matrix(A); free_matrix(B);
        free_matrix(sum); free_matrix(product);
        throw;
    }
    free_matrix(A); free_matrix(B);
    free_matrix(sum); free_matrix(product);
}

/// @brief Демонстрация варианта 28.
void demo_variant() {
    double data[] = {0, 0.0001, -0.0001, 0};
    Matrix m = matrix_from_array(data, 2, 2);
    std::cout << std::boolalpha;
    std::cout << "Variant 28: matrix_is_zero\n";
    std::cout << "Elements: 0, 0.0001, -0.0001, 0\n";
    std::cout << "Tolerance 0.001: " << matrix_is_zero(m, 0.001) << '\n';
    std::cout << "Tolerance 0.0001: " << matrix_is_zero(m, 0.0001) << '\n';
    std::cout << "Tolerance 0.00001: " << matrix_is_zero(m, 0.00001) << '\n';
    free_matrix(m);
}
}
/// @brief Точка входа программы.
int main() {
    matrix::demo_basic();
    matrix::demo_variant();
    return 0;
}