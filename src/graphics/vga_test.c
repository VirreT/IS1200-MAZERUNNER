#include "graphics/graphics.h"
#include "IO/input.h"

#define MAX_SIZE 64
#define MAZE_PIXELS 192

static node cells[MAX_SIZE][MAX_SIZE];
static node *matrix[MAX_SIZE];

void handle_interrupt(unsigned cause)
{
    (void)cause;
}

static unsigned int randomState = 123456789u;

static unsigned int nextRandom(void){
    randomState ^= randomState << 13;
    randomState ^= randomState >> 17;
    randomState ^= randomState << 5;

    return randomState;
}

static void showTestMaze(int dim, int wallsOn)
{
    int middle = dim / 2;
    int startRow = middle - 1;
    int goalRow = middle + 1;

    for (int row = 0; row < dim; row++) {
        matrix[row] = cells[row];

        for (int column = 0; column < dim; column++) {
            /*
             * Skydda en sammanhängande väg:
             * från start till mitten,
             * ned till målets rad,
             * och sedan höger till mål.
             */
            int onSafePath =
                (row == startRow && column <= middle) ||
                (column == middle &&
                 row >= startRow && row <= goalRow) ||
                (row == goalRow && column >= middle);

            matrix[row][column].weight = 1;

            /* Ungefär 25 % väggar utanför den skyddade vägen. */
            if (wallsOn && !onSafePath) {
                if (nextRandom() % 100 < 25) {
                    matrix[row][column].weight = '#';
                }
            }
        }
    }

    matrix[startRow][0].weight = 'S';
    matrix[goalRow][dim - 1].weight = 'D';

    int cellSize = MAZE_PIXELS / dim;

    clearScreen();
    drawMaze(matrix, dim, 60, 20, cellSize);
}

int main(void)
{
    InputState input;

    input_init();
    input_update(&input);

    /* Visa de inställningar som gäller vid uppstart. */
    showTestMaze(8 << input.sizeChoice, input.wallsOn);

    while (1) {
        input_update(&input);

        if (input.startPressed) {
            int mazeSize = 8 << input.sizeChoice;

            showTestMaze(mazeSize, input.wallsOn);
        }
    }
}