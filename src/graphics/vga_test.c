#include "graphics/graphics.h"

#define TEST_SIZE 8

static node cells[TEST_SIZE][TEST_SIZE];
static node *matrix[TEST_SIZE];

void handle_interrupt(unsigned cause)
{
    (void)cause;
}

int main(void)
{
    /* Varje pekare i matrix pekar på en rad i cells. */
    for (int row = 0; row < TEST_SIZE; row++) {
        matrix[row] = cells[row];

        for (int column = 0; column < TEST_SIZE; column++) {
            matrix[row][column].weight = 1;
        }
    }

    /* En vägg i kolumn 3, med en öppning på rad 4. */
    for (int row = 1; row < 7; row++) {
        if (row != 4) {
            matrix[row][3].weight = '#';
        }
    }

    /* Två ytterligare väggrutor. */
    matrix[1][5].weight = '#';
    matrix[2][5].weight = '#';

    /* Start på vänster sida och mål på höger sida. */
    matrix[3][0].weight = 'S';
    matrix[5][7].weight = 'D';

    clearScreen();
    drawMaze(matrix, TEST_SIZE, 60, 20, 24);

    while (1) {
    }
}