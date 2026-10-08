#include "maze/MatrixGenerator.h"
#include "maze/startDestination.h"
#include "maze/walls.h"

#define MAX_SIZE 64

static node cells[MAX_SIZE][MAX_SIZE];
static node *matrix[MAX_SIZE];

static unsigned int randomState = 123456789u;

static unsigned int nextRandom(void)
{
    randomState ^= randomState << 13;
    randomState ^= randomState >> 17;
    randomState ^= randomState << 5;

    return randomState;
}

node **generateMaze(int dim, int wallsOn)
{
    if (dim < 8 || dim > MAX_SIZE)
        return 0;

    for (int row = 0; row < dim; row++) {
        matrix[row] = cells[row];

        for (int column = 0; column < dim; column++) {
            node *n = &matrix[row][column];

            n->weight = 1 + nextRandom() % 20;

            n->above = row > 0
                ? &cells[row - 1][column] : 0;
            n->below = row < dim - 1
                ? &cells[row + 1][column] : 0;
            n->left = column > 0
                ? &cells[row][column - 1] : 0;
            n->right = column < dim - 1
                ? &cells[row][column + 1] : 0;
        }
    }

    setStart(matrix, dim);
    setDestination(matrix, dim);

    if (wallsOn)
        buildWalls(matrix, dim, nextRandom);

    return matrix;
}