#include <stdio.h>
#include <stdlib.h>

//TODO: Define pointers to each node adjacent (left, right, above, below)

//Each node in the maze with a given random weight
typedef struct node {
    char weight;
} node;


//Generates a matrix of nodes with random weights (1-20)
node **generateMatrix(int dim) {
    node **matrix = malloc(dim * sizeof(node *));
    for (int x = 0; x < dim; x++) {
        matrix[x] = malloc(dim * sizeof(node));
        for (int y = 0; y < dim; y++) {
            matrix[x][y].weight = (rand() % 20) + 1;
        }
    }
    return matrix;
}

//Frees the allocated memory for the matrix of nodes
void freeMatrix(node **matrix, int dim) {
    for (int x = 0; x < dim; x++) {
        free(matrix[x]);
    }
    free(matrix);
}

//Prints the matrix of nodes with their weights
void printMatrix(node **matrix, int dim){
    for (int x = 0; x < dim; x++) {
        for (int y = 0; y < dim; y++) {
            printf("[%2d] ", matrix[x][y].weight);
        }
        printf("\n");
    }
}

int main(void) {
    int size = 8;
    node **mtx = generateMatrix(size);

    printMatrix(mtx, size);

    freeMatrix(mtx, size);
    return 0;
}