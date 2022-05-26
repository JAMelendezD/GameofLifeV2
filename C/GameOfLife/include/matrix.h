#pragma once
#include <stdbool.h>

typedef struct {
    short **entries;
    int rows;
    int cols;
}   Matrix;

Matrix* matrix_create(int row, int col);
void matrix_fill(Matrix *m);
Matrix* matrix_copy(Matrix *m);
void matrix_fill_num(Matrix *m, int n);
void matrix_free(Matrix *m);
void matrix_print(Matrix *m, int fps);
void matrix_save(Matrix *m, char* file_string);
void matrix_conway_torus(Matrix *m);
void matrix_conway(Matrix *m);
bool matrix_compare(Matrix *m1, Matrix *m2);