//-------------------------
//--- MatrixGenerator.h ---
//-------------------------

#ifndef MATRIX_GENERATOR_H
#define MATRIX_GENERATOR_H

// Each node in the maze with a given weight, links to all adjacent nodes
typedef struct node {

    char weight;

    struct node* left;
    struct node* right;
    struct node* above;
    struct node* below;

} node;

// Generates a matrix (dim x dim) of nodes with random weights (1-20)
node **generateMatrix(int dim);

// Links all nodes in the matrix
void linkMatrix(node **matrix, int dim);

// Frees the allocated memory for the matrix of nodes
void freeMatrix(node **matrix, int dim);

// Prints the matrix of nodes with their weights
void printMatrix(node **matrix, int dim);

// Prints weights of a given node
void printNode(node *n);

#endif