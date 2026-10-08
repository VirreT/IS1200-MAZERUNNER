#ifndef GRAPHICS_H
#define GRAPHICS_H
#define COLOR_YELLOW 0xFC

#include "maze/MatrixGenerator.h"

#define VGA_WIDTH 320
#define VGA_BUFFER_ROWS 480

#define COLOR_BLACK 0
#define COLOR_WHITE 255
#define COLOR_RED   0xE0
#define COLOR_GREEN 0x1C
#define COLOR_GRAY  0x49

void clearScreen(void);
void putPixel(int x, int y, unsigned char color);

void drawRectangle(int x, int y, int width, int height, unsigned char color);

void drawGrid(int x, int y, int rows, int columns, int cellSize, unsigned char color);

void drawMaze(node **matrix, int dim, int x, int y, int cellSize);



void drawText(int x, int y, const char *text, unsigned char color);

void drawNumber(int x, int y, unsigned int number, unsigned char color);

void drawCellWeight(int x, int y, int cellSize, unsigned int weight, unsigned char color);

#endif