
#ifndef UI_H
#define UI_H
#include "maze/MatrixGenerator.h"

void drawInstructions(void);

void drawComparison(const char *const algorithmNames[], const int resultStatus[], const int resultSteps[], const int resultCost[]);

void drawSolution(node **maze, int dim, const int *reversePath, int length, int cellSize);

#endif