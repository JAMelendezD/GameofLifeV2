// -----------------------------------------------------------------------------
// gameoflife.c : Conways game of life in C.
// -----------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../include/matrix.h"

#define FRAMES 10000

void usage(char *name) {
    fprintf(stderr, "Usage: %s --help --rows <N> --cols <N> --fps <f>\n", name);
    exit(1);
}

int main(int argc, char **argv) {
    
    int fps = 10;
    int rows = 50;
    int cols = 50;

    for (int iarg = 1; iarg < argc; iarg++) {
        
        if (strcmp(argv[iarg], "--help") == 0) {
            usage(argv[0]);
        }
        else if (strcmp(argv[iarg], "--fps") == 0) {
            if (iarg + 1 == argc) {
                fprintf(stderr, "Error: Missing the fps.\n");
                usage(argv[0]);
            }
            iarg++;
            if (sscanf(argv[iarg], "%d", &fps) != 1 || fps < 1) {
                fprintf(stderr, "Error: Invalid measurement time: %s\n",
                        argv[iarg]);
                usage(argv[0]);
            }
        } 
        else if (strcmp(argv[iarg], "--rows") == 0) {
            if (iarg + 1 == argc) {
                fprintf(stderr, "Error: Missing number of rows.\n");
                usage(argv[0]);
            }
            iarg++;
            if (sscanf(argv[iarg], "%d", &rows) != 1 || rows < 1) {
                fprintf(stderr, "Error: Invalid number of rows: %s\n",
                        argv[iarg]);
                usage(argv[0]);
            }
        } 
        else if (strcmp(argv[iarg], "--cols") == 0) {
            if (iarg + 1 == argc) {
                fprintf(stderr,
                        "Error: Missing number of cols.\n");
                usage(argv[0]);
            }
            iarg++;
            if (sscanf(argv[iarg], "%d", &cols) != 1 || cols < 1) {
                fprintf(stderr, "Error: Invalid number of cols: %s\n",
                        argv[iarg]);
                usage(argv[0]);
            }
        } 
        else {
            fprintf(stderr, "Error: Unknown argument: %s\n", argv[iarg]);
            usage(argv[0]);
        }
    }

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
