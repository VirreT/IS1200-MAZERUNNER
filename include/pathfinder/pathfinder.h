#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "maze/MatrixGenerator.h"

#define MAX_PATH_NODES 4096

int bfs(node **matrix, int dim);
int dfs(node **matrix, int dim);
int dijkstra(node **matrix, int dim);

/* Algoritmen lämnar sin funna väg till huvudprogrammet. */
void pathFound(node **matrix, int dim,
               const int *reversePath, int length);

#endif