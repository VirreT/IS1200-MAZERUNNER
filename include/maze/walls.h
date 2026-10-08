#ifndef WALLS_H
#define WALLS_H

#include "maze/MatrixGenerator.h"

void buildWalls(node **matrix, int dim, unsigned int (*randomValue)(void));

#endif