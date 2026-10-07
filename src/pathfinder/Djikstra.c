
//-----------------------------------
//---- Partly Written by ChatGPT ----
//-----------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include "maze/MatrixGenerator.h"

int dijkstra(node **matrix, int dim) {

    if (matrix == NULL || dim <= 0 || dim > INT_MAX / dim) {
        printf("Dijkstra: invalid matrix or size.\n");
        return -2;
    }

    int count = dim * dim;
    int start = -1;
    int goal = -1;

    /* Hitta start och mål */
    for (int row = 0; row < dim; row++) {

        if (matrix[row] == NULL) {
            printf("Dijkstra: missing matrix row.\n");
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
        printf("Dijkstra: start S or destination D is missing.\n");
        return -2;
    }

    if ((size_t)count > SIZE_MAX / sizeof(int)) {
        printf("Dijkstra: matrix is too large.\n");
        return -2;
    }

    /*
     * distance[i] = billigaste kända kostnad från start till i.
     * parent[i] = föregående ruta på billigaste vägen.
     * visited[i] = om den slutgiltiga kostnaden har fastställts.
     */
    int *distance = malloc((size_t)count * sizeof(int));
    int *parent = malloc((size_t)count * sizeof(int));
    int *visited = calloc((size_t)count, sizeof(int));

    if (distance == NULL || parent == NULL || visited == NULL) {
        free(distance);
        free(parent);
        free(visited);

        printf("Dijkstra: memory allocation failed.\n");
        return -2;
    }

    for (int i = 0; i < count; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    distance[start] = 0;
    parent[start] = start;

    /* Ordning: ovanför, nedanför, vänster, höger */
    const int rowChange[4] = {-1, 1, 0, 0};
    const int colChange[4] = {0, 0, -1, 1};

    while (1) {

        /*
         * Hitta den obesökta noden med minst distance.
         */
        int current = -1;
        int bestDistance = INT_MAX;

        for (int i = 0; i < count; i++) {

            if (!visited[i] && distance[i] < bestDistance) {
                bestDistance = distance[i];
                current = i;
            }
        }

        /*
         * Ingen nåbar nod återstår.
         */
        if (current == -1) {
            break;
        }

        /*
         * Den billigaste vägen till current är nu slutgiltig.
         */
        visited[current] = 1;

        /*
         * Målet är klart.
         */
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
             * Hoppa över:
             * - felaktig/saknad länk
             * - vägg
             * - redan färdigbehandlad nod
             */
            if (neighbors[i] != &matrix[nextRow][nextCol] ||
                matrix[nextRow][nextCol].weight == '#' ||
                visited[next]) {
                continue;
            }

            /*
             * S och D kostar 0 att gå in i.
             * Övriga celler använder sin weight som kostnad.
             */
            int weight;

            if (matrix[nextRow][nextCol].weight == 'S' ||
                matrix[nextRow][nextCol].weight == 'D') {
                weight = 0;
            } else {
                weight = matrix[nextRow][nextCol].weight;
            }

            /*
             * Dijkstra fungerar endast med icke-negativa vikter.
             */
            if (weight < 0) {
                printf("Dijkstra: negative weight is not allowed.\n");

                free(distance);
                free(parent);
                free(visited);

                return -2;
            }

            /*
             * Undvik overflow i:
             * distance[current] + weight
             */
            if (distance[current] > INT_MAX - weight) {
                continue;
            }

            int newDistance = distance[current] + weight;

            /*
             * Hittat en billigare väg.
             */
            if (newDistance < distance[next]) {
                distance[next] = newDistance;
                parent[next] = current;
            }
        }
    }

    if (distance[goal] == INT_MAX) {
        printf("Dijkstra: no path found.\n");

        free(distance);
        free(parent);
        free(visited);

        return -1;
    }

    /*
     * Återanvänd distance-arrayen för att lagra vägen
     * från mål till start.
     */
    int length = 0;

    for (int current = goal; ; current = parent[current]) {

        distance[length++] = current;

        if (current == start) {
            break;
        }
    }

    /* Skriv ut vägen från start till mål */
    printf("Dijkstra path: ");

    for (int i = length - 1; i >= 0; i--) {

        int id = distance[i];

        printf("(%d,%d)%s",
               id / dim,
               id % dim,
               i > 0 ? " -> " : "\n");
    }

    printf("Cost: %d\n", distance[goal]);

    int cost = distance[goal];

    free(distance);
    free(parent);
    free(visited);

    return cost;
}