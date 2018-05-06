#include "neural_network.h"
#include <stdio.h>
#include <math.h>

int matrix_to_class(matrix_t matrix, int* output) {

    double n1, n2, n3;

    matrix_get(matrix, 0, 0, &n1);
    matrix_get(matrix, 1, 0, &n2);
    matrix_get(matrix, 2, 0, &n3);

    if (n1 == 1 && n2 == 0 && n3 == 0) {
        *output = 1;
        return 0;
    }

    if (n1 == 0 && n2 == 1 && n3 == 0) {
        *output = 2;
        return 0;
    }

    if (n1 == 0 && n2 == 0 && n3 == 1) {
        *output = 3;
        return 0;
    }
    return 0;
}

int class_to_matrix(int input, matrix_t *matrix) {

    switch(input) {
        case 1:
            matrix_set(matrix, 0, 0, 1.0);
            return 0;
        case 2:
            matrix_set(matrix, 1, 0, 1.0);
            return 0;
        case 3:
            matrix_set(matrix, 2, 0, 1.0);
            return 0;
    }

    return 0;
}

void activation_single(double in, double *out) {
    *out = (tanh(in) + 1.0) / 2.0;
}

void activation_derivative_single(double in, double *out) {
    *out = (1 - (tanh(in) * tanh(in))) / 2.0;
}

int activation(matrix_t input, matrix_t *output) {
    matrix_apply_closure(input, &activation_single, output);
    return 0;
}

int activiation_derivative(matrix_t input, matrix_t *output) {
    matrix_apply_closure(input, &activation_single, output);
    return 0;
}

