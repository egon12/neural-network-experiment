#include "neural_network.h"
#include "matrix/matrix.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void test_matrix_to_class() {

    matrix_t m;
    int out;

    matrix_init_int(&m, 3, 1, 1, 0, 0);
    matrix_to_class(m, &out);
    if (out != 1) {
        printf("Error: test not valid, out are %d?\n", out);
    }
    matrix_destroy(&m);

    matrix_init_int(&m, 3, 1, 0, 1, 0);
    matrix_to_class(m, &out);
    if (out != 2) {
        printf("Error: test not valid, out are %d?\n", out);
    }
    matrix_destroy(&m);

    matrix_init_int(&m, 3, 1, 0, 0, 1);
    matrix_to_class(m, &out);
    if (out != 3) {
        printf("Error: test not valid, out are %d?\n", out);
    }
    matrix_destroy(&m);

}

void test_class_to_matrix() {

    matrix_t actual;
    matrix_t expected;
    bool result;

    matrix_init_empty(&actual, 3, 1);
    matrix_init_int(&expected, 3, 1, 1, 0, 0);
    class_to_matrix(1, &actual);
    matrix_equals(actual, expected, &result);
    if (!result) {
        printf("Expected matrix:\n");
        matrix_print(expected);
        printf("Actual matrix:\n");
        matrix_print(actual);
    }
    matrix_destroy(&actual);
    matrix_destroy(&expected);

    matrix_init_empty(&actual, 3, 1);
    matrix_init_int(&expected, 3, 1, 0, 1, 0);
    class_to_matrix(2, &actual);
    matrix_equals(actual, expected, &result);
    if (!result) {
        printf("Expected matrix:\n");
        matrix_print(expected);
        printf("Actual matrix:\n");
        matrix_print(actual);
    }
    matrix_destroy(&actual);
    matrix_destroy(&expected);

    matrix_init_empty(&actual, 3, 1);
    matrix_init_int(&expected, 3, 1, 0, 0, 1);
    class_to_matrix(3, &actual);
    matrix_equals(actual, expected, &result);
    if (!result) {
        printf("Expected matrix:\n");
        matrix_print(expected);
        printf("Actual matrix:\n");
        matrix_print(actual);
    }
    matrix_destroy(&actual);
    matrix_destroy(&expected);



}

int main() {
    test_matrix_to_class();
    test_class_to_matrix();


    printf("tanh(1)= %f\n", tanh(1));

    matrix_t m;
    matrix_init(&m, 3, 1, 1.0, 0.0, 0.0);

    activation(m, &m);

    matrix_print(m);

}
