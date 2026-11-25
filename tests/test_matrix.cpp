#include "matrix.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <limits>

namespace matrix {
TEST(MatrixTest, CreateMatrix_NormalCase) {
    Matrix a = create_matrix(3, 4);
    EXPECT_EQ(a.rows, 3); EXPECT_EQ(a.cols, 4);
    EXPECT_NE(a.data, nullptr);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 4; ++j) EXPECT_DOUBLE_EQ(a.data[i][j], 0);
    free_matrix(a);
}
TEST(MatrixTest, Addition_NormalCase) {
    double x[] = {1,2,3,4}, y[] = {5,6,7,8};
    Matrix a = matrix_from_array(x,2,2), b = matrix_from_array(y,2,2);
    Matrix c = matrix_add(a,b);
    EXPECT_DOUBLE_EQ(c.data[0][0],6); EXPECT_DOUBLE_EQ(c.data[0][1],8);
    EXPECT_DOUBLE_EQ(c.data[1][0],10); EXPECT_DOUBLE_EQ(c.data[1][1],12);
    free_matrix(a); free_matrix(b); free_matrix(c);
}
TEST(MatrixTest, Multiplication_NormalCase) {
    double x[] = {1,2,3,4}, y[] = {5,6,7,8};
    Matrix a = matrix_from_array(x,2,2), b = matrix_from_array(y,2,2);
    Matrix c = matrix_multiply(a,b);
    EXPECT_DOUBLE_EQ(c.data[0][0],19); EXPECT_DOUBLE_EQ(c.data[0][1],22);
    EXPECT_DOUBLE_EQ(c.data[1][0],43); EXPECT_DOUBLE_EQ(c.data[1][1],50);
    free_matrix(a); free_matrix(b); free_matrix(c);
}
TEST(MatrixTest, Transpose_NormalCase) {
    double x[] = {1,2,3,4,5,6}; Matrix a = matrix_from_array(x,2,3);
    Matrix b = matrix_transpose(a);
    EXPECT_EQ(b.rows,3); EXPECT_EQ(b.cols,2);
    for(int i=0;i<2;++i) for(int j=0;j<3;++j)
        EXPECT_DOUBLE_EQ(b.data[j][i],a.data[i][j]);
    free_matrix(a); free_matrix(b);
}
TEST(MatrixTest, FreeMatrix_NormalCase) {
    Matrix a = create_matrix(3,3); EXPECT_NO_THROW(free_matrix(a));
}

TEST(MatrixTest, CreateMatrix_MinimumSize) {
    Matrix a=create_matrix(1,1); EXPECT_EQ(a.rows,1); EXPECT_EQ(a.cols,1);
    EXPECT_DOUBLE_EQ(a.data[0][0],0); free_matrix(a);
}
TEST(MatrixTest, Multiplication_RowTimesColumn_1x1) {
    double x[]={1,2,3}, y[]={4,5,6};
    Matrix a=matrix_from_array(x,1,3), b=matrix_from_array(y,3,1);
    Matrix c=matrix_multiply(a,b); EXPECT_EQ(c.rows,1); EXPECT_EQ(c.cols,1);
    EXPECT_DOUBLE_EQ(c.data[0][0],32); free_matrix(a); free_matrix(b); free_matrix(c);
}
TEST(MatrixTest, TransposeTwice_ReturnsOriginal) {
    double x[]={1,2,3,4,5,6}; Matrix a=matrix_from_array(x,2,3);
    Matrix b=matrix_transpose(a), c=matrix_transpose(b);
    EXPECT_EQ(c.rows,2); EXPECT_EQ(c.cols,3);
    for(int i=0;i<2;++i) for(int j=0;j<3;++j)
        EXPECT_DOUBLE_EQ(c.data[i][j],a.data[i][j]);
    free_matrix(a); free_matrix(b); free_matrix(c);
}

TEST(MatrixTest, CreateMatrix_ZeroRows) {
    EXPECT_THROW(create_matrix(0,3),std::invalid_argument);
}
TEST(MatrixTest, CreateMatrix_NegativeCols) {
    EXPECT_THROW(create_matrix(3,-1),std::invalid_argument);
}
TEST(MatrixTest, Addition_SizeMismatch) {
    Matrix a=create_matrix(2,2), b=create_matrix(3,3);
    EXPECT_THROW(matrix_add(a,b),std::invalid_argument); free_matrix(a); free_matrix(b);
}
TEST(MatrixTest, Multiplication_SizeMismatch) {
    Matrix a=create_matrix(2,3), b=create_matrix(2,2);
    EXPECT_THROW(matrix_multiply(a,b),std::invalid_argument); free_matrix(a); free_matrix(b);
}
TEST(MatrixTest, FreeMatrix_EmptyIsSafe) {
    Matrix a{};
EXPECT_NO_THROW(free_matrix(a));
EXPECT_NO_THROW(free_matrix(a));
}
TEST(MatrixTest, FromArray_Null) {
    EXPECT_THROW(matrix_from_array(nullptr,2,2),std::invalid_argument);
}

TEST(Variant28, ExactZero) {
    Matrix a=create_matrix(2,2); EXPECT_TRUE(matrix_is_zero(a,0)); free_matrix(a);
}
TEST(Variant28, WithinTolerance) {
    double x[]={0,0.001,-0.001,0}; Matrix a=matrix_from_array(x,2,2);
    EXPECT_TRUE(matrix_is_zero(a,0.001)); EXPECT_FALSE(matrix_is_zero(a,0.0001));
    free_matrix(a);
}
TEST(Variant28, NonZero) {
    double x[]={1}; Matrix a=matrix_from_array(x,1,1);
    EXPECT_FALSE(matrix_is_zero(a,0)); free_matrix(a);
}
TEST(Variant28, InvalidArguments) {
    Matrix a=create_matrix(1,1);
    EXPECT_THROW(matrix_is_zero(a,-1),std::invalid_argument);
    EXPECT_THROW(matrix_is_zero(Matrix{},0),std::invalid_argument);
    EXPECT_THROW(matrix_is_zero(a,std::numeric_limits<double>::infinity()),std::invalid_argument);
    free_matrix(a);
}
TEST(Variant28, NaNElement) {
    double x[]={std::numeric_limits<double>::quiet_NaN()};
    Matrix a=matrix_from_array(x,1,1); EXPECT_FALSE(matrix_is_zero(a,1)); free_matrix(a);
}
}