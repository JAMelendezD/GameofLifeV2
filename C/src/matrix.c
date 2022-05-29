#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/matrix.h"

#define ANSI_COLOR_DEAD   "\x1b[38;2;10;9;59;208m\x1b[48;2;5;5;20;208m"
#define ANSI_COLOR_RESET  "\x1b[0m"
#define ANSI_COLOR_ALIVE  "\x1b[38;2;255;228;181;208m\x1b[48;2;5;5;20;208m"

Matrix* matrix_create(int row, int col) {

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = row;
    matrix->cols = col;
    matrix->entries = malloc(row * sizeof(short*));

    for (int i = 0; i < row; i++){
        matrix->entries[i] = malloc(col * sizeof(short));
    }
    return matrix;
}

void matrix_free(Matrix *m) {

	for (int i = 0; i < m->rows; i++) {
		free(m->entries[i]);
	}
	free(m->entries);
    free(m);
	m = NULL;
}

Matrix* matrix_copy(Matrix *m) {

	Matrix* cm = matrix_create(m->rows, m->cols);

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			cm->entries[i][j] = m->entries[i][j];
		}
	}
	return cm;
}

void matrix_fill(Matrix *m) {    

    srand(time(0));

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->entries[i][j] = rand() % 2;
        }
    }
}

void matrix_fill_num(Matrix *m, int n) {    

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->entries[i][j] = n;
        }
    }
}

void matrix_print(Matrix *m, int fps) {

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            if (m->entries[i][j] == 0) {
                printf(ANSI_COLOR_DEAD "\u25A0 " ANSI_COLOR_RESET);
            }
            else {
                printf(ANSI_COLOR_ALIVE "\u25A0 " ANSI_COLOR_RESET);
            }
        }
        printf("\n");    
    }

    usleep((1.0/fps)*pow(10, 6));
    printf("\x1b[%dF", m->rows+1);
    printf("\n");
}

void matrix_conway_torus(Matrix *m) {    
    
    // Can be improved to not do % so many times
    // Memory wise also to operate on bits

    Matrix* cm = matrix_copy(m);
    int rs = m->rows;
    int cs = m->cols;

    for (int i = 0; i < rs; i++) {
        for (int j = 0; j < cs; j++) {
            int state = cm->entries[i][j];                 
            int neis = cm->entries[(i + rs) % rs][(j + cs + 1) % cs] +
                       cm->entries[(i + rs) % rs][(j + cs - 1) % cs] +
                       cm->entries[(i + rs + 1) % rs][(j + cs) % cs] +
                       cm->entries[(i + rs - 1) % rs][(j + cs) % cs] +
                       cm->entries[(i + rs + 1) % rs][(j + cs + 1) % cs] +
                       cm->entries[(i + rs - 1) % rs][(j + cs - 1) % cs] +
                       cm->entries[(i + rs + 1) % rs][(j + cs - 1) % cs] +
                       cm->entries[(i + rs - 1) % rs][(j + cs + 1) % cs];

            if (state == 1) {
                if (neis != 2 && neis != 3) {
                    m->entries[i][j] = 0;
                }
            }
            else {
                if (neis == 3) {
                    m->entries[i][j] = 1;
                }  
            }
        }
    }
    matrix_free(cm);
}

bool matrix_compare(Matrix *m1, Matrix *m2) {

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->cols; j++) {
            if (m1->entries[i][j] != m2->entries[i][j]) {
                return false;
            }
        }
    }
    return true;
}