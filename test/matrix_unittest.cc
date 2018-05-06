#include <gtest/gtest.h>

extern "C" {
#include <matrix/matrix.h>
}

TEST(matrix, matrix_equals_result_equals) {

    matrix_t m1, m2;
    matrix_init_int(&m1, 3, 3,
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
        );

    matrix_init_int(&m2, 3, 3,
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
        );

    bool result;
    matrix_equals(m1, m2, &result);

    EXPECT_TRUE(result);
}


TEST(matrix, matrix_equals_result_not_equals) {

    matrix_t m1, m2;
    matrix_init_int(&m1, 3, 3,
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
        );

    matrix_init_int(&m2, 3, 3,
        1, 2, 3,
        4, 5, 6,
        7, 8, 0
        );

    bool result;
    matrix_equals(m1, m2, &result);

    EXPECT_FALSE(result);
}


int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
