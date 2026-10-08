#ifndef GRAPHICS_H
#define GRAPHICS_H

#define VGA_WIDTH 320
#define VGA_BUFFER_ROWS 480

#define COLOR_BLACK 0
#define COLOR_WHITE 255

void clearScreen(void);

void putPixel(int x, int y, unsigned char color);

void drawRectangle(int x, int y, int width, int height, unsigned char color);

void drawGrid(int x, int y, int rows, int columns, int cellSize, unsigned char color);

#endif
