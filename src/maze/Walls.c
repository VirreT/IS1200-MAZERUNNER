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

        for (int x = 0; x < dim; x++){
         
            for (int y = 0; y < dim; y++){
                
                if(rng(1, 100) <= 20){ // 20% chance of placing a wall
                    
                    if(matrix[x][y].weight != 'S' && matrix[x][y].weight != 'D'){
                        matrix[x][y].weight = '#';
                    }
                }

            }
   
        }

        wallCount++;
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