#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#include "maze/MatrixGenerator.h"

/*
 * Returnerar:
 * >= 0: antal steg till målet
 *   -1: ingen väg finns
 *   -2: fel, exempelvis saknad start eller minnesbrist
 */
int bfs(node **matrix, int dim) {
    if (matrix == NULL || dim <= 0 || dim > INT_MAX / dim) {
        printf("BFS: invalid matrix or size.\n");
        return -2;
    }

    int count = dim * dim;
    int start = -1;
    int goal = -1;

    /* Hitta start och mål */
    for (int row = 0; row < dim; row++) {
        if (matrix[row] == NULL) {
            printf("BFS: missing matrix row.\n");
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
        printf("BFS: start S or destination D is missing.\n");
        return -2;
    }

    if ((size_t)count > SIZE_MAX / sizeof(int)) {
        printf("BFS: matrix is too large.\n");
        return -2;
    }

    /*
     * Kön lagrar rutornas index.
     * parent lagrar föregående ruta längs sökvägen.
     * parent == -1 betyder att rutan inte är besökt.
     */
    int *queue = malloc((size_t)count * sizeof(int));
    int *parent = malloc((size_t)count * sizeof(int));

    if (queue == NULL || parent == NULL) {
        free(queue);
        free(parent);
        printf("BFS: memory allocation failed.\n");
        return -2;
    }

    for (int i = 0; i < count; i++) {
        parent[i] = -1;
    }

    int head = 0;
    int tail = 0;

    queue[tail++] = start;
    parent[start] = start;

    /* Ordning: ovanför, nedanför, vänster, höger */
    const int rowChange[4] = {-1, 1, 0, 0};
    const int colChange[4] = {0, 0, -1, 1};

    while (head < tail) {
        int current = queue[head++];

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
             * Även en NULL-länk faller bort i första kontrollen.
             */
            if (neighbors[i] != &matrix[nextRow][nextCol] ||
                matrix[nextRow][nextCol].weight == '#' ||
                parent[next] != -1) {
                continue;
            }

            /* Markera besökt direkt när rutan läggs i kön */
            parent[next] = current;
            queue[tail++] = next;
        }
    }

    if (parent[goal] == -1) {
        printf("BFS: no path found.\n");
        free(queue);
        free(parent);
        return -1;
    }

    /* Återanvänd kön för att lagra vägen från mål till start */
    int length = 0;

    for (int current = goal; ; current = parent[current]) {
        queue[length++] = current;

        if (current == start) {
            break;
        }
    }

    /* Skriv ut vägen från start till mål */
    printf("BFS path: ");

    for (int i = length - 1; i >= 0; i--) {
        int id = queue[i];

        printf("(%d,%d)%s",
               id / dim,
               id % dim,
               i > 0 ? " -> " : "\n");
    }

    int steps = length - 1;
    printf("Steps: %d\n", steps);

    free(queue);
    free(parent);

    return steps;
}