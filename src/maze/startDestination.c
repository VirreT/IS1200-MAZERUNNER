//----------------------------
//---- StartDestination.c ----
//----------------------------


#include "maze/startDestination.h"

void setStart(node **matrix, int dim)
{
    matrix[dim / 2 - 1][0].weight = 'S';
}

void setDestination(node **matrix, int dim)
{
    matrix[dim / 2 + 1][dim - 1].weight = 'D';
}