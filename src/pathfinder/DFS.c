#include "pathfinder/pathfinder.h"

int dfs(node **matrix, int dim)
{
    if (!matrix || dim <= 0 || dim > 64)
        return -2;

    int count = dim * dim;
    int start = -1;
    int goal = -1;

    static int stack[MAX_PATH_NODES];
    static int parent[MAX_PATH_NODES];

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

    for (int i = 0; i < count; i++)
        parent[i] = -1;

    int top = 0;

    stack[top++] = start;
    parent[start] = start;

    const int rowChange[4] = {-1, 1, 0, 0};
    const int columnChange[4] = {0, 0, -1, 1};

    while (top > 0) {
        /* Ta den senast tillagda rutan. */
        int current = stack[--top];

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

            if (neighbors[i] != &matrix[nextRow][nextColumn] ||
                matrix[nextRow][nextColumn].weight == '#' ||
                parent[next] != -1)
                continue;

            parent[next] = current;
            stack[top++] = next;
        }
    }

    if (parent[goal] == -1)
        return -1;

    /* Återanvänd stacken för vägen från mål till start. */
    int length = 0;

    for (int current = goal; ; current = parent[current]) {
        stack[length++] = current;

        if (current == start)
            break;
    }

    pathFound(matrix, dim, stack, length);

    return length - 1;
}