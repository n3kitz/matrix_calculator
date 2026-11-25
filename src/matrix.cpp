#include "matrix.h"
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace matrix {
namespace {
/// @brief Проверка корректности матрицы.
bool valid(Matrix m) {
    if (!m.data || m.rows <= 0 || m.cols <= 0) return false;
    for (int i = 0; i < m.rows; ++i)
        if (!m.data[i]) return false;
    return true;
}
/// @brief Проверка матрицы с генерацией исключения.
void require_valid(Matrix m) {
    if (!valid(m)) throw std::invalid_argument("Invalid matrix");
}
}
Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0)
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    Matrix m{new double*[rows]{}, rows, cols};
    try {
        for (int i = 0; i < rows; ++i)
            m.data[i] = new double[cols]{};
    } catch (...) {
        for (int i = 0; i < rows; ++i) delete[] m.data[i];
        delete[] m.data;
        throw;
    }
    return m;
}

void free_matrix(Matrix m) {
    if (!m.data) return;
    for (int i = 0; i < m.rows; ++i) delete[] m.data[i];
    delete[] m.data;
}

Matrix matrix_add(Matrix a, Matrix b) {
    require_valid(a); require_valid(b);
    if (a.rows != b.rows || a.cols != b.cols)
        throw std::invalid_argument("Addition size mismatch");
    Matrix c = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; ++i)
        for (int j = 0; j < a.cols; ++j)
            c.data[i][j] = a.data[i][j] + b.data[i][j];
    return c;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    require_valid(a); require_valid(b);
    if (a.cols != b.rows)
        throw std::invalid_argument("Multiplication size mismatch");
    Matrix c = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; ++i)
        for (int k = 0; k < a.cols; ++k)
            for (int j = 0; j < b.cols; ++j)
                c.data[i][j] += a.data[i][k] * b.data[k][j];
    return c;
}

void print_matrix(Matrix m) {
    if (!valid(m)) { std::cout << "[Empty matrix]\n"; return; }
    constexpr int max_rows = 10, max_cols = 8;
    const auto flags = std::cout.flags();
    const auto precision = std::cout.precision();
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < m.rows; ++i) {
        if (m.rows > max_rows && i == max_rows / 2) {
            std::cout << "[...]\n";
            i = m.rows - max_rows / 2;
        }
        std::cout << '[';
        for (int j = 0; j < m.cols; ++j) {
            if (m.cols > max_cols && j == max_cols / 2) {
                std::cout << " ...";
                j = m.cols - max_cols / 2;
            }
            std::cout << std::setw(6) << m.data[i][j];
        }
        std::cout << " ]\n";
    }
    if (m.rows > max_rows || m.cols > max_cols)
        std::cout << "Matrix " << m.rows << 'x' << m.cols << '\n';
    std::cout.flags(flags);
    std::cout.precision(precision);
}

Matrix matrix_from_array(double* data, int rows, int cols) {
    if (!data) throw std::invalid_argument("Null array");
    Matrix m = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            m.data[i][j] = data[static_cast<std::size_t>(i) * cols + j];
    return m;
}

bool matrix_is_zero(Matrix m, double tolerance) {
    require_valid(m);
    if (!std::isfinite(tolerance) || tolerance < 0)
        throw std::invalid_argument("Invalid tolerance");
    for (int i = 0; i < m.rows; ++i)
        for (int j = 0; j < m.cols; ++j)
            if (!std::isfinite(m.data[i][j]) ||
                std::abs(m.data[i][j]) > tolerance) return false;
    return true;
}

Matrix matrix_transpose(Matrix m) {
    require_valid(m);
    Matrix result = create_matrix(m.cols, m.rows);
    for (int i = 0; i < m.rows; ++i)
        for (int j = 0; j < m.cols; ++j)
            result.data[j][i] = m.data[i][j];
    return result;
}
}