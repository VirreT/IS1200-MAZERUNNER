//----------------------------
//---- StartDestination.c ----
//----------------------------

#include <stdio.h>

#include "maze/MatrixGenerator.h"
#include "helpers/Randomizer.h"
#include "maze/StartDestination.h"
 
 
 //Sets the start node in the matrix
 void setStart(node **matrix, int dim) {
    matrix[0][rng(0, dim - 1)].weight = 'S';
}

//Sets the destination node in the matrix
 void setDestination(node **matrix, int dim) {
    matrix[dim - 1][rng(0, dim - 1)].weight = 'D';
}