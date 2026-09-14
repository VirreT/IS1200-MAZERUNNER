#include <stdio.h>
#include <stdlib.h>

// Each node in the maze with a given weight, links to all adjacent nodes
typedef struct node {

    char weight;

    struct node* left;
    struct node* right;
    struct node* above;
    struct node* below;

} node;

// Generates a matrix (dim x dim) of nodes with random weights (1-20)
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

// Links all nodes in the matrix
void linkMatrix(node **matrix, int dim){

    for (int x = 0; x < dim; x++){   

        for (int y = 0; y < dim; y++){

            if (x > 0) {
                matrix[x][y].above = &matrix[x - 1][y];
            } else {
                matrix[x][y].above = NULL;
            }

            if (x < dim - 1) {
                matrix[x][y].below = &matrix[x + 1][y];
            } else {
                matrix[x][y].below = NULL;
            }

            if (y > 0) {
                matrix[x][y].left = &matrix[x][y - 1];
            } else {
                matrix[x][y].left = NULL;
            }

            if (y < dim - 1) {
                matrix[x][y].right = &matrix[x][y + 1];
            } else {
                matrix[x][y].right = NULL;
            }
        }
    }
}

// Frees the allocated memory for the matrix of nodes
void freeMatrix(node **matrix, int dim) {

    for (int x = 0; x < dim; x++) {
        free(matrix[x]);
    }

    free(matrix);
}

// Prints the matrix of nodes with their weights

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
    printNode(mtx, 4, 4);

    freeMatrix(mtx, size);
    return 0;
}