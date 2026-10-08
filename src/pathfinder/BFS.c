/* Anpassad med hjälp av ChatGPT. */
#include "pathfinder/pathfinder.h"

int bfs(node **matrix, int dim)
{
    if (!matrix || dim <= 0 || dim > 64)
        return -2;

    int count = dim * dim;
    int start = -1;
    int goal = -1;

    static int queue[MAX_PATH_NODES];
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

    /* -1 betyder att rutan inte har upptäckts. */
    for (int i = 0; i < count; i++)
        parent[i] = -1;

    int head = 0;
    int tail = 0;

    queue[tail++] = start;
    parent[start] = start;

    const int rowChange[4] = {-1, 1, 0, 0};
    const int columnChange[4] = {0, 0, -1, 1};

    while (head < tail) {
        int current = queue[head++];

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
            queue[tail++] = next;
        }
    }

    if (parent[goal] == -1)
        return -1;

    /* Återanvänd kön för vägen från mål till start. */
    int length = 0;

    for (int current = goal; ; current = parent[current]) {
        queue[length++] = current;

        if (current == start)
            break;
    }

    /* Lämna vägen till huvudprogrammet. */
    pathFound(matrix, dim, queue, length);

    return length - 1;
}