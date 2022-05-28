#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/matrix.h"


#define ROWS 6
#define COLS 6
#define FRAMES 100
#define MAXCHAR 20
#define OUTLEN 8
#define ANSI_COLOR_RED   "\x1b[38;2;255;0;0;208m"
#define ANSI_COLOR_GREEN "\x1b[38;2;0;255;0;208m"
#define ANSI_COLOR_RESET "\x1b[0m"

void print_results(char *name, bool outcome) {
    
    printf("%*s:\t", OUTLEN, name);

    if (outcome == false) {
        printf(ANSI_COLOR_RED "Failed\n" ANSI_COLOR_RESET);
    }
    else {
        printf(ANSI_COLOR_GREEN "Passed\n" ANSI_COLOR_RESET);
    }
}

void run (Matrix *m, void (*f)(Matrix *m) ) {
    for (int frame = 0; frame < FRAMES; frame++) {
        (*f)(m);
    }
}

int main(int argc, char **argv) {

    Matrix *m = matrix_create(ROWS, COLS);
    char *name = (char*)malloc(MAXCHAR * sizeof(char));
    bool result = false;
    
    printf("Testing matrix_conways_torus\n");

    sprintf(name, "Block");
    matrix_fill_num(m, 0);
    m->entries[2][2] = 1;
    m->entries[2][3] = 1;
    m->entries[3][2] = 1;
    m->entries[3][3] = 1;
    Matrix* cm1 = matrix_copy(m);
    run(m, matrix_conway_torus);
    result = matrix_compare(m, cm1);
    print_results(name, result);
    matrix_free(cm1);

    sprintf(name, "Beehive");
    matrix_fill_num(m, 0);
    m->entries[2][1] = 1;
    m->entries[1][2] = 1;
    m->entries[3][2] = 1;
    m->entries[1][3] = 1;
    m->entries[3][3] = 1;
    m->entries[2][4] = 1;
    Matrix* cm2 = matrix_copy(m);
    run(m, matrix_conway_torus);
    result = matrix_compare(m, cm2);
    print_results(name, result);
    matrix_free(cm2);

    sprintf(name, "Loaf");
    matrix_fill_num(m, 0);
    m->entries[2][1] = 1;
    m->entries[1][2] = 1;
    m->entries[3][2] = 1;
    m->entries[1][3] = 1;
    m->entries[4][3] = 1;
    m->entries[2][4] = 1;
    m->entries[3][4] = 1;
    Matrix* cm3 = matrix_copy(m);
    run(m, matrix_conway_torus);
    result = matrix_compare(m, cm3);
    print_results(name, result);
    matrix_free(cm3);

    sprintf(name, "Boat");
    matrix_fill_num(m, 0);
    m->entries[2][2] = 1;
    m->entries[3][2] = 1;
    m->entries[1][3] = 1;
    m->entries[3][3] = 1;
    m->entries[2][4] = 1;
    Matrix* cm4 = matrix_copy(m);
    run(m, matrix_conway_torus);
    result = matrix_compare(m, cm4);
    print_results(name, result);
    matrix_free(cm4);

    sprintf(name, "Ship");
    matrix_fill_num(m, 0);
    m->entries[2][2] = 1;
    m->entries[3][2] = 1;
    m->entries[1][3] = 1;
    m->entries[3][3] = 1;
    m->entries[2][4] = 1;
    m->entries[1][4] = 1;
    Matrix* cm5 = matrix_copy(m);
    run(m, matrix_conway_torus);
    result = matrix_compare(m, cm5);
    print_results(name, result);
    matrix_free(cm5);

    sprintf(name, "Diagonal");
    matrix_fill_num(m, 0);
    m->entries[1][1] = 1;
    m->entries[2][2] = 1;
    m->entries[3][3] = 1;
    m->entries[4][4] = 1;
    Matrix* cm6 = matrix_copy(m);
    run(m, matrix_conway_torus);
    result = matrix_compare(m, cm6);
    print_results(name, !result);
    matrix_free(cm6);

    matrix_free(m);

}
