#include "graphics/graphics.h"

static volatile unsigned char *VGA = (volatile unsigned char *)0x08000000;

void clearScreen(void){
    // Rensa samma buffertområde som i kursens demo
    for (int i = 0; i < VGA_WIDTH * VGA_BUFFER_ROWS; i++) {
        VGA[i] = COLOR_BLACK;
    }
}

void putPixel(int x, int y, unsigned char color){
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_BUFFER_ROWS) {
        return;
    }

    VGA[y * VGA_WIDTH + x] = color;
}

void drawRectangle(int x, int y, int width, int height, unsigned char color)
{
    for (int row = 0; row < height; row++){
        for (int column = 0; column < width; column++){
            putPixel(x + column, y + row, color);
        }
    }
}

void drawGrid(int x, int y, int rows, int columns, int cellSize, unsigned char color)
{
    if (rows <= 0 || columns <= 0 || cellSize <= 0){
        return;
    }

    int width = columns * cellSize;
    int height = rows * cellSize;

    // Horisontella linjer, inklusive ytterkanterna
    for (int row = 0; row <= rows; row++) {
        drawRectangle(x, y + row * cellSize, width + 1, 1, color);
    }

    /* Vertikala linjer, inklusive ytterkanterna. */
    for (int column = 0; column <= columns; column++){
        drawRectangle(x + column * cellSize, y, 1, height + 1, color);
    }
}

void drawMaze(node **matrix, int dim, int x, int y, int cellSize)
{
    if (!matrix || dim <= 0 || cellSize < 2)
        return;

    for (int row = 0; row < dim; row++){
        for (int column = 0; column < dim; column++){
            int value = matrix[row][column].weight;
            unsigned char color = COLOR_BLACK;

            if (value == '#') {
                color = COLOR_WHITE;
            } else if (value == 'S') {
                color = COLOR_GREEN;
            } else if (value == 'D') {
                color = COLOR_RED;
            }

            int pixelX = x + column * cellSize;
            int pixelY = y + row * cellSize;

            // Fyll rutans insida och lämna plats för rutnätet
            drawRectangle(pixelX + 1, pixelY + 1, cellSize - 1, cellSize - 1, color);
            drawCellWeight(pixelX, pixelY, cellSize, (unsigned int)value, COLOR_WHITE); // shows weight on each node
        }
    }

    drawGrid(x, y, dim, dim, cellSize, COLOR_GRAY);
}

