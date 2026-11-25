/** @file matrix.h
 * @brief Библиотека для работы с матрицами.
 * @version 0.1
 */
#pragma once
/** @brief Операции с матрицами. */
namespace matrix {
/** @brief Динамическая матрица.
 * @warning Память освобождается через free_matrix().
 */
struct Matrix {
    double** data; ///< Данные по строкам.
    int rows;      ///< Количество строк.
    int cols;      ///< Количество столбцов.
};
/** @brief Создание матрицы, заполненной нулями.
 * @param rows Число строк (>0).
 * @param cols Число столбцов (>0).
 * @return Новая матрица.
 * @exception std::invalid_argument Некорректные размеры.
 * @exception std::bad_alloc Ошибка выделения памяти.
 * @see free_matrix
 * @note Сложность O(rows*cols).
 * @code
 * Matrix a = create_matrix(3, 3);
 * free_matrix(a);
 * @endcode
 */
Matrix create_matrix(int rows, int cols);
/** @brief Освобождение памяти.
 * @param m Матрица (nullptr допустим).
 * @warning Не использовать объект после освобождения.
 */
void free_matrix(Matrix m);
/** @brief Сложение матриц.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Новая матрица-сумма.
 * @exception std::invalid_argument Несовместимые размеры или невалидная матрица.
 */
Matrix matrix_add(Matrix a, Matrix b);
/** @brief Матричное умножение.
 * @param a Левая матрица M x N.
 * @param b Правая матрица N x K.
 * @return Новая матрица M x K.
 * @exception std::invalid_argument Несовместимые размеры или невалидная матрица.
 * @note Сложность O(M*N*K).
 * @warning Результат нужно освободить через free_matrix().
 */
Matrix matrix_multiply(Matrix a, Matrix b);
/** @brief Форматированный вывод матрицы.
 * @param m Матрица для вывода.
 * @note Большие матрицы выводятся сокращённо.
 */
void print_matrix(Matrix m);
/** @brief Создание матрицы из массива.
 * @param data Массив из rows*cols элементов.
 * @param rows Число строк.
 * @param cols Число столбцов.
 * @return Новая матрица.
 * @exception std::invalid_argument Нулевой указатель или неверные размеры.
 */
Matrix matrix_from_array(double* data, int rows, int cols);
/** @brief Проверка на нулевую матрицу (вариант 28).
 * @param m Проверяемая матрица.
 * @param tolerance Конечная неотрицательная погрешность.
 * @return true, если все элементы конечны и abs(element) <= tolerance.
 * @exception std::invalid_argument Невалидная матрица или погрешность.
 */
bool matrix_is_zero(Matrix m, double tolerance);
/** @brief Транспонирование матрицы.
 * @param m Исходная матрица.
 * @return Новая транспонированная матрица.
 * @exception std::invalid_argument Невалидная матрица.
 */
Matrix matrix_transpose(Matrix m);
} // namespace matrix