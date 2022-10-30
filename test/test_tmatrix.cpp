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
    TDynamicMatrix<int> m(10);
    ASSERT_ANY_THROW (m[-1][-1] = 0);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(10);
    ASSERT_ANY_THROW (m[100][100] = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(10);
    ASSERT_NO_THROW (m = m);
}

/*TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m(10);
    TDynamicMatrix<int> m1(10);
    ASSERT_NO_THROW (m = m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  ADD_FAILURE();
}
*/
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
    TDynamicMatrix<int> m(10);
    m[0][0] = 1;
    TDynamicMatrix<int> m1(10);
    m1[0][0] = 1;
    ASSERT_NO_THROW(m + m1);
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
    TDynamicMatrix<int> m(10);
    m[0][0] = 1;
    TDynamicMatrix<int> m1(10);
    m1[0][0] = 1;
    ASSERT_NO_THROW(m - m1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m(10);
    m[0][0] = 1;
    TDynamicMatrix<int> m1(5);
    m1[0][0] = 1;
    ASSERT_ANY_THROW(m - m1);
}

