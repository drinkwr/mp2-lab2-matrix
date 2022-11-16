#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(10);
    m[0][0] = 1;
    TDynamicMatrix<int> m1(m);
    ASSERT_EQ(m[0][0],m1[0][0]);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(10);
    m[0][0] = 1;
    TDynamicMatrix<int> m1(m);
    ASSERT_NE(&m,&m1);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(4);

    EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(4);
      m[0][0] = 4;
      EXPECT_EQ(4, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(2);
    ASSERT_ANY_THROW(m.at(-2).at(-1) = 0);  //m[-1][-1] = 0);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(10);
    ASSERT_ANY_THROW(m.at(100).at(100) = 0);   //m[100][100] = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(10);
    ASSERT_NO_THROW (m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m(10);
    TDynamicMatrix<int> m1(10);
    ASSERT_NO_THROW (m = m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m(10);
    TDynamicMatrix<int> m1(5);
    m = m1;
    EXPECT_EQ(m.size(),m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m(10);
    TDynamicMatrix<int> m1(5);
    m1[0][0] = 5;
    m = m1;
    EXPECT_EQ(m[0][0], m1[0][0]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m(10);
    m[0][0] = 1;
    TDynamicMatrix<int> m1(10);
    m1[0][0] = 1;
    ASSERT_EQ(m == m1, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(10);
    m[0][0] = 1;
    ASSERT_EQ(m == m, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m(10);
    m[0][0] = 1;
    TDynamicMatrix<int> m1(5);
    m1[0][0] = 1;
    ASSERT_NE(m == m1, true);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    /*TDynamicMatrix<int> m1(2),m2(2),m3;
         m1[0][0] = 6;
         m2[0][0] = 4;
         m3 = m1 + m2;
         EXPECT_EQ(10, m3[0][0]);*/
    TDynamicMatrix<int> m(2);
    m[0][0] = 1;
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 2;
    TDynamicMatrix<int> m2(2);
    m2 = m + m1;
    ASSERT_EQ(true, m2[0][0] == 3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(10);
    m[0][0] = 1;
    TDynamicMatrix<int> m1(5);
    m1[0][0] = 1;
    ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1;
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 1;
    TDynamicMatrix<int> m2(2);
    m2 = m - m1;
    ASSERT_EQ(true, m2[0][0] == 0 );
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m(10);
    m[0][0] = 1;
    TDynamicMatrix<int> m1(5);
    m1[0][0] = 1;
    ASSERT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, can_multiply_matrix_to_scalar)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = m[0][1] = m[1][1] = m[1][0] = 1;
    TDynamicMatrix<int> m1(2);
    m1 = m * 2;
    EXPECT_EQ(m1[1][1], 2);
}

TEST(TDynamicMatrix, can_multiply_matrix_to_vector)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = m[0][1] = m[1][1] = m[1][0] = 1;
    TDynamicVector<int> v(2);
    v[0] = v[1] = 2;
    TDynamicVector<int> v1;
    v1 = m * v;
    EXPECT_EQ(v1[1], 4);
}
TEST(TDynamicMatrix, cant_multiply_matrix_to_vector_with_different_sizes)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = m[0][1] = m[1][1] = m[1][0] = 1;
    TDynamicVector<int> v(3);
    v[0] = v[1] = 2;
    TDynamicVector<int> v1;
    EXPECT_ANY_THROW(v1 = m * v);
}

TEST(TDynamicMatrix, can_multiply_matrix_to_matrix)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = m[0][1] = m[1][1] = m[1][0] = 1;
    TDynamicMatrix<int> m1(2);
    m1[0][0] = m1[0][1] = m1[1][1] = m1[1][0] = 2;
    TDynamicMatrix<int> m2(2);
    m2 = m * m1;
    EXPECT_EQ(m2[1][1], 4);
}
TEST(TDynamicMatrix, cant_multiply_matrix_to_matrix_with_different_sizes)
{
    TDynamicMatrix<int> m(2);
    TDynamicMatrix<int> m1(3);
    EXPECT_ANY_THROW(m * m1);
}
