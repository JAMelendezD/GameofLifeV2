#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"
#include <time.h>

#define MAXCHAR 100

int main(int argc, char **argv) {
    
    if (argc < 5) {
        printf("Missing arguments\n");
        printf("It should be run as ./gameoflife rows cols frames fps\n");
        printf("Rows and cols determine the grid size\n");
        printf("Frames how long to run for and fps the frames per second\n");
        exit(-1);
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int frames = atoi(argv[3]);
    int fps = atoi(argv[4]);
    char *fname = (char*)malloc(MAXCHAR * sizeof(char));

    Matrix *world = matrix_create(rows, cols);
    matrix_fill(world);
    matrix_print(world, fps);

    printf("Started simulation\n");
    printf("Frame = %06d", 0);
    clock_t start = clock();
    for (int frame = 1; frame < frames + 1; frame++) {
        matrix_conway_torus(world);
        printf("Frame = %06d", frame);
        matrix_print(world, fps);
    }
    printf("Finished simulation in: %6.2f seconds\n",
            ((double)clock() - start)/CLOCKS_PER_SEC);

    /*
    Matrix *world = matrix_create(rows, cols);
    matrix_fill(world);
    sprintf(fname, "%06d.txt", 0);
    matrix_save(world, fname);

    printf("Started simulation\n");
    clock_t start = clock();
    for (int frame = 1; frame < frames + 1; frame++) {
        matrix_conway(world);
        sprintf(fname, "%06d.txt", frame);
        matrix_save(world, fname);
    }
    printf("Finished simulation in: %6.2f seconds\n",
            ((double)clock() - start)/CLOCKS_PER_SEC);

    */

    matrix_free(world);
    free(fname);

    return 0;
}