#ifndef MATRIX_H
#define MATRIX_H 1

#include <stdbool.h>

/**
 * Type Definition
 */
struct matrix_s {
    int col;
    int row;
    double *content;
};

typedef struct matrix_s matrix_t;


/**
 * Function Definition
 */
int matrix_init(matrix_t *matrix, int col, int row, ...);

int matrix_init_empty(matrix_t *matrix, int col, int row);

int matrix_init_int(matrix_t *matrix, int col, int row, ...);

int matrix_destroy(matrix_t *matrix);

int matrix_print(matrix_t matrix);

int matrix_set(matrix_t *matrix, int x, int y, double value);

int matrix_get(matrix_t matrix, int x, int y, double *out);

int matrix_equals(matrix_t matrix_1, matrix_t matrix_2, bool *out);

int matrix_add(matrix_t matrix_1, matrix_t matrix_2, matrix_t *result);

int matrix_multiply(matrix_t matrix_1, matrix_t matrix_2, matrix_t *result);

int matrix_dot_scalar(matrix_t matrix, double scalar, matrix_t *result);

int matrix_apply_closure(matrix_t matrix, void (*func)(double, double*), matrix_t *result);

int matrix_horizontal_concat(matrix_t matrix_1, matrix_t matrix_2, matrix_t *result);

#endif
