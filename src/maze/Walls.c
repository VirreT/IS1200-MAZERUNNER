//----------------------------
//--------- walls.c ----------
//----------------------------



#include "maze/walls.h"

void buildWalls(node **matrix, int dim,
                unsigned int (*randomValue)(void))
{
    if (!matrix || !randomValue || dim <= 0)
        return;

    int segments = dim * dim / 25;

    if (segments < 5)
        segments = 5;

    for (int segment = 0; segment < segments; segment++) {
        int row = (int)(randomValue() % (unsigned int)dim);
        int column = (int)(randomValue() % (unsigned int)dim);
        int vertical = (int)(randomValue() % 2u);

        int length =
            2 + (int)(randomValue() %
                      (unsigned int)(dim / 8 + 2));

        /* Längre sträckor får ibland en öppning. */
        int gap = -1;

        if (length >= 5)
            gap = 1 + (int)(randomValue() %
                            (unsigned int)(length - 2));

        for (int k = 0; k < length; k++) {
            int r = row + (vertical ? k : 0);
            int c = column + (vertical ? 0 : k);

            if (r >= dim || c >= dim)
                break;

            if (k == gap)
                continue;

            if (matrix[r][c].weight != 'S' &&
                matrix[r][c].weight != 'D')
                matrix[r][c].weight = '#';
        }
    }
}