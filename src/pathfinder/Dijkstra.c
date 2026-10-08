#include <limits.h>
#include "pathfinder/pathfinder.h"

int dijkstra(node **matrix, int dim)
{
    if (!matrix || dim <= 0 || dim > 64)
        return -2;

    int count = dim * dim;
    int start = -1;
    int goal = -1;

    static int distance[MAX_PATH_NODES];
    static int parent[MAX_PATH_NODES];
    static int visited[MAX_PATH_NODES];

    /* Hitta start och mål. */
    for (int row = 0; row < dim; row++) {
        if (!matrix[row])
            return -2;

        for (int column = 0; column < dim; column++) {
            int weight = matrix[row][column].weight;

            if (weight == 'S')
                start = row * dim + column;
            else if (weight == 'D')
                goal = row * dim + column;
        }
    }

    if (start == -1 || goal == -1)
        return -2;

    for (int i = 0; i < count; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = 0;
    }

    distance[start] = 0;
    parent[start] = start;

    const int rowChange[4] = {-1, 1, 0, 0};
    const int columnChange[4] = {0, 0, -1, 1};

    while (1) {
        int current = -1;
        int bestDistance = INT_MAX;

        /* Välj den obesökta rutan med lägst kostnad. */
        for (int i = 0; i < count; i++) {
            if (!visited[i] && distance[i] < bestDistance) {
                current = i;
                bestDistance = distance[i];
            }
        }

        if (current == -1)
            break;

        visited[current] = 1;

        if (current == goal)
            break;

        int row = current / dim;
        int column = current % dim;

        node *n = &matrix[row][column];

        node *neighbors[4] = {
            n->above,
            n->below,
            n->left,
            n->right
        };

        for (int i = 0; i < 4; i++) {
            int nextRow = row + rowChange[i];
            int nextColumn = column + columnChange[i];

            if (nextRow < 0 || nextRow >= dim ||
                nextColumn < 0 || nextColumn >= dim)
                continue;

            int next = nextRow * dim + nextColumn;
            int weight = matrix[nextRow][nextColumn].weight;

            if (neighbors[i] != &matrix[nextRow][nextColumn] ||
                weight == '#' || visited[next])
                continue;

            /* Start och mål har kostnaden 0. */
            if (weight == 'S' || weight == 'D')
                weight = 0;

            if (weight < 0)
                return -2;

            /* Undvik overflow vid additionen. */
            if (distance[current] > INT_MAX - weight)
                continue;

            int newDistance = distance[current] + weight;

            if (newDistance < distance[next]) {
                distance[next] = newDistance;
                parent[next] = current;
            }
        }
    }

    if (distance[goal] == INT_MAX)
        return -1;
    int cost = distance[goal];
    int length = 0;

    /* Återskapa vägen från mål till start. */
    for (int current = goal; ; current = parent[current]) {
        distance[length++] = current;

        if (current == start)
            break;
    }
}