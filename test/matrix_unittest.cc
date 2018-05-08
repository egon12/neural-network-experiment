#include <gtest/gtest.h>

extern "C" {
#include <matrix/matrix.h>
}

TEST(matrix, matrix_equals_result_equals) {

    matrix_t m1, m2;
    matrix_init(&m1, 3, 3,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
        );

    matrix_init(&m2, 3, 3,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
        );

    bool result;
    matrix_equals(m1, m2, &result);

    EXPECT_TRUE(result);

    matrix_destroy(&m1);
    matrix_destroy(&m2);
}


TEST(matrix, matrix_equals_result_not_equals) {

    matrix_t m1, m2;
    matrix_init(&m1, 3, 3,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
        );

    matrix_init(&m2, 3, 3,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 0.0
        );

    bool result;
    matrix_equals(m1, m2, &result);

    EXPECT_FALSE(result);

    matrix_destroy(&m1);
    matrix_destroy(&m2);
}

TEST(matrix, matrix_init_empty) {
    matrix_t m1, m2;
    matrix_init(&m1, 2, 3,
        0.0, 0.0, 
        0.0, 0.0, 
        0.0, 0.0
        );

    matrix_init_empty(&m2, 2, 3);

    bool result;
    matrix_equals(m1, m2, &result);

    EXPECT_TRUE(result);

    matrix_destroy(&m1);
    matrix_destroy(&m2);
}


TEST(matrix, matrix_init_int) {
    matrix_t m1, m2;
    matrix_init(&m1, 3, 3,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
        );

    matrix_init_int(&m2, 3, 3,
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
        );

    bool result;
    matrix_equals(m1, m2, &result);

    EXPECT_TRUE(result);

    matrix_destroy(&m1);
    matrix_destroy(&m2);
}

TEST(matrix, matrix_row_col_not_equals) {
    matrix_t m1, m2;
    matrix_init(&m1, 3, 2,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0
        );

    matrix_init(&m2, 2, 3,
        1.0, 2.0,
        3.0, 4.0,
        5.0, 6.0
        );

    bool result;
    matrix_equals(m1, m2, &result);

    EXPECT_FALSE(result);

    matrix_destroy(&m1);
    matrix_destroy(&m2);
}


TEST(matrix, matrix_add_matrix) {
    matrix_t m1, m2, m3;
    matrix_init(&m1, 3, 3,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
        );

    matrix_init(&m2, 3, 3,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0
        );

    matrix_init(&m3, 3, 3,
        2.0, 3.0, 4.0,
        5.0, 6.0, 7.0,
        8.0, 9.0, 10.0
        );
    

    matrix_add(m1, m2, &m1);
    bool result;
    matrix_equals(m1, m3, &result);

    EXPECT_TRUE(result);

    matrix_destroy(&m1);
    matrix_destroy(&m2);
    matrix_destroy(&m3);
}

TEST(matrix, matrix_dot_scalar) {

    matrix_t m1, m2;

    matrix_init(&m1, 3, 3,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
        );


    matrix_init(&m2, 3, 3,
        3.0, 6.0, 9.0,
        12.0, 15.0, 18.0,
        21.0, 24.0, 27.0
        );
    
    matrix_dot_scalar(m1, 3.0, &m1);
    bool result;
    matrix_equals(m1, m2, &result);

    ASSERT_TRUE(result);

    matrix_destroy(&m1);
    matrix_destroy(&m2);

}

void func(double in, double *out) {
    *out = (in) / 2;
}

TEST(matrix, matrix_closure) {
    matrix_t m1, m2;

    matrix_init(&m1, 3, 3,
        2.0, 2.0, 4.0,
        4.0, 6.0, 6.0,
        8.0, 8.0, 8.0
        );

    matrix_init(&m2, 3, 3,
        1.0, 1.0, 2.0,
        2.0, 3.0, 3.0,
        4.0, 4.0, 4.0
        );

    matrix_apply_closure(m1, &func, &m1);

    bool result;

    matrix_equals(m1, m2, &result);

    ASSERT_TRUE(result);

    matrix_destroy(&m1);
    matrix_destroy(&m2);
}

