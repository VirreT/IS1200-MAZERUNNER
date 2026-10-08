
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!! Written by ChatGPT !!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#include "pathfinder/pathfinder.h"
#include "maze/MatrixGenerator.h"

int dfs(node **matrix, int dim) {

    if (matrix == NULL || dim <= 0 || dim > INT_MAX / dim) {
        printf("DFS: invalid matrix or size.\n");
        return -2;
    }

    int count = dim * dim;
    int start = -1;
    int goal = -1;

    /* Hitta start och mål */
    for (int row = 0; row < dim; row++) {

        if (matrix[row] == NULL) {
            printf("DFS: missing matrix row.\n");
            return -2;
        }

        for (int col = 0; col < dim; col++) {

            if (matrix[row][col].weight == 'S') {
                start = row * dim + col;
            } else if (matrix[row][col].weight == 'D') {
                goal = row * dim + col;
            }
        }
    }

    if (start == -1 || goal == -1) {
        printf("DFS: start S or destination D is missing.\n");
        return -2;
    }

    if ((size_t)count > SIZE_MAX / sizeof(int)) {
        printf("DFS: matrix is too large.\n");
        return -2;
    }

    /*
     * stack lagrar rutornas index.
     * parent lagrar föregående ruta längs sökvägen.
     * parent == -1 betyder att rutan inte är besökt.
     */
    int *stack = malloc((size_t)count * sizeof(int));
    int *parent = malloc((size_t)count * sizeof(int));

    if (stack == NULL || parent == NULL) {
        free(stack);
        free(parent);
        printf("DFS: memory allocation failed.\n");
        return -2;
    }

    for (int i = 0; i < count; i++) {
        parent[i] = -1;
    }

    int top = 0;

    stack[top++] = start;
    parent[start] = start;

    /* Ordning: ovanför, nedanför, vänster, höger */
    const int rowChange[4] = {-1, 1, 0, 0};
    const int colChange[4] = {0, 0, -1, 1};

    while (top > 0) {

        int current = stack[--top];

        if (current == goal) {
            break;
        }

        int row = current / dim;
        int col = current % dim;

        node *cur = &matrix[row][col];

        node *neighbors[4] = {
            cur->above,
            cur->below,
            cur->left,
            cur->right
        };

        /*
         * Lägg grannar i stacken.
         *
         * Eftersom stacken är LIFO kommer den sista insatta
         * grannen att undersökas först.
         */
        for (int i = 0; i < 4; i++) {

            int nextRow = row + rowChange[i];
            int nextCol = col + colChange[i];

            /* Hoppa över koordinater utanför matrisen */
            if (nextRow < 0 || nextRow >= dim ||
                nextCol < 0 || nextCol >= dim) {
                continue;
            }

            int next = nextRow * dim + nextCol;

            /*
             * Hoppa över saknad länk, vägg eller besökt ruta.
             */
            if (neighbors[i] != &matrix[nextRow][nextCol] ||
                matrix[nextRow][nextCol].weight == '#' ||
                parent[next] != -1) {
                continue;
            }

            /* Markera besökt direkt när rutan läggs i stacken */
            parent[next] = current;
            stack[top++] = next;
        }
    }

    if (parent[goal] == -1) {
        printf("DFS: no path found.\n");
        free(stack);
        free(parent);
        return -1;
    }

    /*
     * Återanvänd stacken för att lagra vägen
     * från mål till start.
     */
    int length = 0;

    for (int current = goal; ; current = parent[current]) {

        stack[length++] = current;

        if (current == start) {
            break;
        }
    }

    /* Skriv ut vägen från start till mål */
    printf("DFS path: ");

    for (int i = length - 1; i >= 0; i--) {

        int id = stack[i];

        printf("(%d,%d)%s",
               id / dim,
               id % dim,
               i > 0 ? " -> " : "\n");
    }

    int steps = length - 1;

    printf("Steps: %d\n", steps);

    free(stack);
    free(parent);

    return steps;
}