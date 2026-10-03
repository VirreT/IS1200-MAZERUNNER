//----------------------------
//---- StartDestination.c ----
//----------------------------

#ifndef STARTDESTINATION_H
#define STARTDESTINATION_H 
 
#include "maze/MatrixGenerator.h"

//Sets the start node in the matrix
void setStart(node **matrix, int dim);

//Sets the destination node in the matrix
void setDestination(node **matrix, int dim);

#endif