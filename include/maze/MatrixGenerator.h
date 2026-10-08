#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

typedef struct node {
    int weight;
    struct node *above;
    struct node *below;
    struct node *left;
    struct node *right;
} node;

node **generateMaze(int dim, int wallsOn);

#endif