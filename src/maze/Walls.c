#include <stdio.h>

#include "maze/MatrixGenerator.h"

int main() {

    int size = 3;

    node **mtx = generateMatrix(size);

    linkMatrix(mtx, size);

    printMatrix(mtx, size);

    printNode(&mtx[1][1]);

    freeMatrix(mtx, size);

    return 0;
}