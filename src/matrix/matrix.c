#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define EPSILON 0.0000001

int matrix_init(matrix_t *matrix, int col, int row, ...) {
    va_list args;
    va_start(args, row);
    matrix->content = malloc(row * col * sizeof(double));
    for (int i=0; i < col * row; i++) {
        *((double *)(matrix->content + i)) = va_arg(args, double);
    }
    va_end(args);

    matrix->col = col;
    matrix->row = row;

    return 0;
}

int matrix_init_empty(matrix_t *matrix, int col, int row) {
    matrix->content = calloc(row * col, sizeof(double));
    matrix->col = col;
    matrix->row = row;
    return 0;
}

int matrix_init_int(matrix_t *matrix, int col, int row, ...) {
    va_list args;
    va_start(args, row);
    matrix->content = malloc(row * col * sizeof(double));
    for (int i=0; i < col * row; i++) {
        *((double *)(matrix->content + i)) = (double) va_arg(args, int);
    }
    va_end(args);

    matrix->col = col;
    matrix->row = row;
    return 0;
}


int matrix_destroy(matrix_t *matrix) {
    free(matrix->content);
    return 0;
}


int matrix_print(matrix_t matrix) {
    printf("Matrix col: %d, row: %d, content:\n", matrix.col, matrix.row);
    for (int y=0; y < matrix.row; y++) {
        for (int x=0; x < matrix.col; x++) {
            int pos = y * matrix.col + x;
            double *value = (double *)(matrix.content + pos);
            printf("%6.1f ", *value);
        }
        puts("");
    }
    puts("End");
    return 0;
}

int matrix_set(matrix_t *matrix, int x, int y, double value) {
    if (x < 0 || x > matrix->col) {
        return -1;
    }

    if (y < 0 || y > matrix->row) {
        return -1;
    }

    int pos = y * matrix->col + x;
    double *pt = (double *)(matrix->content + pos);
    *pt = value;
    return 0;
}


int matrix_get(matrix_t matrix, int x, int y, double *out) {
    if (x < 0 || x > matrix.col) {
        return -1;
    }

    if (y < 0 || y > matrix.row) {
        return -1;
    }

    int pos = y * matrix.col + x;
    *out = *((double *)(matrix.content + pos));
    return 0;
}

int matrix_equals(matrix_t matrix_1, matrix_t matrix_2, bool *out) {

    if (matrix_1.col != matrix_2.col) {
        *out = false;
        return 0;
    }

    if (matrix_1.row != matrix_2.row) {
        *out = false;
        return 0;
    }

    for (int y=0; y < matrix_1.row; y++) {
        for (int x=0; x < matrix_1.col; x++) {
            int pos = y * matrix_1.col + x;
            double *value1 = (double *)(matrix_1.content + pos);
            double *value2 = (double *)(matrix_2.content + pos);
            if ( fabs(*value1 - *value2) > EPSILON ) {
                *out = false;
                return 0;
            }
        }
    }
    *out = true;
    return 0;
}


int matrix_add(matrix_t matrix_1, matrix_t matrix_2, matrix_t *result) {

    if (matrix_1.col != matrix_2.col) {
        return -1;
    }

    if (matrix_1.row != matrix_2.row) {
        return -1;
    }

    for (int y=0; y < matrix_1.row; y++) {
        for (int x=0; x < matrix_1.col; x++) {
            int pos = y * matrix_1.col + x;
            double value1 = *((double *)(matrix_1.content + pos));
            double value2 = *((double *)(matrix_2.content + pos));
            *((double *)(result->content + pos)) = value1 + value2;
        }
    }
    return 0;
}

int matrix_multiply(matrix_t matrix_1, matrix_t matrix_2, matrix_t *result) {
    if (matrix_1.col != matrix_2.row) {
        return -1;
    }

    if (result->row != matrix_1.row) {
        return -2;
    }

    if (result->col != matrix_2.col) {
        return -3;
    }

    int m = matrix_1.col;
    double v1, v2, total;

    for (int y = 0; y < matrix_1.row; y++) {
        for (int x = 0; x < matrix_2.col; x++) {
            total = 0.0;

            for (int i=0; i<m; i++) {
                matrix_get(matrix_1, i, y, &v1);
                matrix_get(matrix_2, x, i, &v2);

                total += v1 * v2;
            }

            matrix_set(result, x, y, total);
        }
    }

    return 0;
}

int matrix_dot_scalar(matrix_t matrix, double scalar, matrix_t *result) {
    for (int y=0; y < matrix.row; y++) {
        for (int x=0; x < matrix.col; x++) {
            int pos = y * matrix.col + x;
            double value1 = *((double *)(matrix.content + pos));
            *((double *)(result->content + pos)) = value1 * scalar;
        }
    }
    return 0;
}


int matrix_apply_closure(matrix_t matrix, void (*func)(double, double*), matrix_t *result) {
    for (int y=0; y < matrix.row; y++) {
        for (int x=0; x < matrix.col; x++) {
            int pos = y * matrix.col + x;
            func(
                *((double *)(matrix.content + pos)),
                ((double *)(result->content + pos))
                );
        }
    }
    return 0;
}

int matrix_horizontal_concat(matrix_t matrix_1, matrix_t matrix_2, matrix_t *result) {

  if (matrix_1.row != matrix_2.row) {
      return -1;
  }

  if (result->col != (matrix_1.col + matrix_2.col)) {
      return -2;
  }

  if (result->row != matrix_1.row) {
      return -3;
  }

  double value = 0;

  for (int y=0; y<matrix_1.row; y++) {
    for (int x=0; x< matrix_1.col; x++) {
      matrix_get(matrix_1, x, y, &value);
      matrix_set(result, x, y, value);
    }
  }

  for (int y=0; y<matrix_2.row; y++) {
    for (int x=0; x< matrix_2.col; x++) {
      matrix_get(matrix_2, x, y, &value);
      matrix_set(result, x+matrix_1.col, y, value);
    }
  }

  return 0;
}
