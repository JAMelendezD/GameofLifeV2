#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/matrix.h"

//#define ANSI_COLOR_DEAD   "\x1b[38;2;90;10;10;208m"
#define ANSI_COLOR_DEAD   "\x1b[38;2;10;9;59;208m\x1b[48;2;5;5;20;208m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_ALIVE  "\x1b[38;2;255;228;181;208m\x1b[48;2;5;5;20;208m"

Matrix* matrix_create(int row, int col) {

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = row;
    matrix->cols = col;
    matrix->entries = malloc(row * sizeof(int*));

    for (int i = 0; i < row; i++){
        matrix->entries[i] = malloc(col * sizeof(int));
    }
    return matrix;
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

void matrix_free(Matrix *m) {

	for (int i = 0; i < m->rows; i++) {
		free(m->entries[i]);
	}
	free(m);
	m = NULL;
}

void matrix_print(Matrix *m, int fps) {
    
    printf("\n"); 

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            if (m->entries[i][j] == 0) {
                printf(ANSI_COLOR_DEAD "\u25A0 " ANSI_COLOR_RESET);
                //printf("🍑");
            }
            else {
                printf(ANSI_COLOR_ALIVE "\u25A0 " ANSI_COLOR_RESET);
                //printf("🍆");
            }
        }
        printf("\n");    
    }

    usleep((1.0/fps)*pow(10, 6));

    for (int i = 0; i < m->rows + 1; i++) {
        printf("\x1b[1A\x1b[2K");
    }

}

Matrix* matrix_copy(Matrix *m) {

	Matrix* mat = matrix_create(m->rows, m->cols);

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			mat->entries[i][j] = m->entries[i][j];
		}
	}
	return mat;
}

void matrix_conway_torus(Matrix *m) {    
    
    // Can be improved to not do % so many times

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


void matrix_conway(Matrix *m) {    
    
    Matrix* cm = matrix_copy(m);
    
    int rs = m->rows;
    int cs = m->cols;

    for (int i = 0; i < rs; i++) {
        m->entries[i][0] = 0;
        m->entries[i][cs - 1] = 0;
    }

    for (int j = 0; j < cs; j++) {
        m->entries[0][j] = 0;
        m->entries[rs - 1][j] = 0;
    }

    for (int i = 1; i < rs - 1; i++) {
        for (int j = 1; j < cs - 1; j++) {
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

void matrix_save(Matrix *m, char *file_string) {
    
    FILE *fp = fopen(file_string, "w");
    
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            fprintf(fp, "%d ", m->entries[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
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
