#include <stdio.h>
#include <stdlib.h>

#include "maze/MatrixGenerator.h"


int main(){
    int mtxSize = 8;

    node **matrix = generateMatrix(mtxSize);
    linkMatrix(matrix, mtxSize);
    printMatrix(matrix, mtxSize);
    printNode(&matrix[1][1]);

    freeMatrix(matrix, mtxSize);
    
    return 0;
}