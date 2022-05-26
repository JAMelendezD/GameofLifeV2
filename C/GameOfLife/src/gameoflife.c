// -----------------------------------------------------------------------------
// gameoflife.c : Conways game of life in C.
// -----------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"

#define FRAMES 1000000

int main(int argc, char **argv) {
    
    if (argc < 4) {
        printf("Missing arguments\n");
        printf("It should be run as ./gameoflife rows cols fps\n");
        printf("Rows and cols determine the grid size and then the fps\n");
        exit(-1);
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int fps = atoi(argv[3]);

    Matrix *world = matrix_create(rows, cols);
    matrix_fill(world);
    matrix_print(world, fps);

    for (int frame = 0; frame < FRAMES; frame++) {
        matrix_conway_torus(world);
        matrix_print(world, fps);
    }

    matrix_free(world);
    return 0;
}