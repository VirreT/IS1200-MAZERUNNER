//-----------------
//---- Walls.c ----
//-----------------

#include <stdio.h>

#include "maze/MatrixGenerator.h"
#include "helpers/Randomizer.h"

#define NOFWALLS 10

void buildWalls(node **matrix, int dim){
    
    int wallCount = 0;

    if (wallCount < NOFWALLS){    

        int x = rng(0, dim - 1);
        int y = rng(0, dim - 1);

        if (matrix[x][y].weight != 'S' && matrix[x][y].weight != 'D'){
         
            matrix[x][y].weight = '#';
            wallCount++;
        
        }
    }
}

int main() {

    int size = 3;

    node **mtx = generateMatrix(size);

    linkMatrix(mtx, size);

    printMatrix(mtx, size);

    printNode(&mtx[1][1]);

    freeMatrix(mtx, size);

    return 0;
}