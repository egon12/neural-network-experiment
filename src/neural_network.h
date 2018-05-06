#include "matrix/matrix.h"

/**
 * Only for matrix 3 x 1
 * only binary input?
 */
int matrix_to_class(matrix_t matrix, int* output);

int class_to_matrix(int input, matrix_t *matrix);

int activation(matrix_t input, matrix_t *output);

int activation_derivative(matrix_t input, matrix_t *output);


