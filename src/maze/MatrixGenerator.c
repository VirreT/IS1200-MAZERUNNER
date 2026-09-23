//-------------------------
//--- MatrixGenerator.c ---
//-------------------------

#include <stdio.h>
#include <stdlib.h>
#include "maze/MatrixGenerator.h"

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
            
            // Link left
            if (x > 0) {
                matrix[x][y].above = &matrix[x - 1][y];
            } else {
                matrix[x][y].above = NULL;
            }

            // Link right
            if (x < dim - 1) {
                matrix[x][y].below = &matrix[x + 1][y];
            } else {
                matrix[x][y].below = NULL;
            }

            // Link below
            if (y > 0) {
                matrix[x][y].left = &matrix[x][y - 1];
            } else {
                matrix[x][y].left = NULL;
            }

            // Link above
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


// Prints weights of a given node
void printNode(node *n) {

    if (n == NULL) {
        printf("Node is NULL\n");
        return;
    }

    printf("Node [%2d]:\n", n->weight);

    if (n->above != NULL) {
        printf("  Above: [%2d]\n", n->above->weight);
    } else {
        printf("  Above: NULL\n");
    }

    if (n->below != NULL) {
        printf("  Below: [%2d]\n", n->below->weight);
    } else {
        printf("  Below: NULL\n");
    }

    if (n->left != NULL) {
        printf("  Left:  [%2d]\n", n->left->weight);
    } else {
        printf("  Left:  NULL\n");
    }

    if (n->right != NULL) {
        printf("  Right: [%2d]\n", n->right->weight);
    } else {
        printf("  Right: NULL\n");
    }
}