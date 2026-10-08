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

static void showTestMaze(int dim, int wallsOn)
{
    /* Förbered en labyrint med den valda storleken. */
    for (int row = 0; row < dim; row++) {
        matrix[row] = cells[row];

        for (int column = 0; column < dim; column++) {
            matrix[row][column].weight = 1;
        }
    }

    int middle = dim / 2;

    if (wallsOn) {
        /* Lodrät vägg med en öppning i mitten. */
        for (int row = 1; row < dim - 1; row++) {
            if (row != middle) {
                matrix[row][middle].weight = '#';
            }
        }

        /* Två ytterligare väggrutor. */
        matrix[1][middle + 2].weight = '#';
        matrix[2][middle + 2].weight = '#';
    }

    matrix[middle - 1][0].weight = 'S';
    matrix[middle + 1][dim - 1].weight = 'D';

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