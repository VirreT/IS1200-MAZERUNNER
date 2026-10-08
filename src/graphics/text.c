#include "graphics/graphics.h"

/* Varje tecken består av 7 rader med 5 pixlar. */
static const unsigned char letters[26][7] = {
    {14,17,17,31,17,17,17}, /* A */
    {30,17,17,30,17,17,30}, /* B */
    {14,17,16,16,16,17,14}, /* C */
    {30,17,17,17,17,17,30}, /* D */
    {31,16,16,30,16,16,31}, /* E */
    {31,16,16,30,16,16,16}, /* F */
    {14,17,16,23,17,17,14}, /* G */
    {17,17,17,31,17,17,17}, /* H */
    {31,4,4,4,4,4,31},      /* I */
    {7,2,2,2,18,18,12},    /* J */
    {17,18,20,24,20,18,17}, /* K */
    {16,16,16,16,16,16,31}, /* L */
    {17,27,21,21,17,17,17}, /* M */
    {17,25,21,19,17,17,17}, /* N */
    {14,17,17,17,17,17,14}, /* O */
    {30,17,17,30,16,16,16}, /* P */
    {14,17,17,17,21,18,13}, /* Q */
    {30,17,17,30,20,18,17}, /* R */
    {15,16,16,14,1,1,30},   /* S */
    {31,4,4,4,4,4,4},      /* T */
    {17,17,17,17,17,17,14}, /* U */
    {17,17,17,17,17,10,4},  /* V */
    {17,17,17,21,21,21,10}, /* W */
    {17,17,10,4,10,17,17},  /* X */
    {17,17,10,4,4,4,4},    /* Y */
    {31,1,2,4,8,16,31}     /* Z */
};

static const unsigned char digits[10][7] = {
    {14,17,19,21,25,17,14},
    {4,12,4,4,4,4,14},
    {14,17,1,2,4,8,31},
    {30,1,1,14,1,1,30},
    {2,6,10,18,31,2,2},
    {31,16,16,30,1,1,30},
    {14,16,16,30,17,17,14},
    {31,1,2,4,8,8,8},
    {14,17,17,14,17,17,14},
    {14,17,17,15,1,1,14}
};

void drawText(int x, int y, const char *text,
              unsigned char color)
{
    while (*text) {
        char c = *text++;
        const unsigned char *glyph = 0;

        if (c >= 'a' && c <= 'z')
            c -= 'a' - 'A';

        if (c >= 'A' && c <= 'Z')
            glyph = letters[c - 'A'];
        else if (c >= '0' && c <= '9')
            glyph = digits[c - '0'];

        drawRectangle(x, y, 6, 7, COLOR_BLACK);

        for (int row = 0; row < 7; row++) {
            unsigned int bits = glyph ? glyph[row] : 0;

            if (c == '-' && row == 3)
                bits = 14;
            else if (c == ':' && (row == 2 || row == 4))
                bits = 4;
            else if (c == '=' && (row == 2 || row == 4))
                bits = 14;

            for (int column = 0; column < 5; column++) {
                if (bits & (1u << (4 - column)))
                    putPixel(x + column, y + row, color);
            }
        }

        x += 6;
    }
}

void drawNumber(int x, int y, unsigned int number, unsigned char color){
    char text[11];
    int length = 0;

    do {
        text[length++] = '0' + number % 10;
        number /= 10;
    } while (number);

    for (int i = 0; i < length / 2; i++) {
        char temp = text[i];
        text[i] = text[length - 1 - i];
        text[length - 1 - i] = temp;
    }

    text[length] = '\0';
    drawText(x, y, text, color);
}

void drawCellWeight(int x, int y, int cellSize, unsigned int weight, unsigned char color)
{
    if (cellSize < 12 || weight < 1 || weight > 20)
        return;

    int count = weight < 10 ? 1 : 2;
    int textWidth = count * 6 - 1;

    int textX = x + 1 + (cellSize - 1 - textWidth) / 2;
    int textY = y + 1 + (cellSize - 1 - 7) / 2;

    for (int digit = 0; digit < count; digit++) {
        int number;

        if (count == 2 && digit == 0)
            number = weight / 10;
        else
            number = weight % 10;

        for (int row = 0; row < 7; row++) {
            for (int column = 0; column < 5; column++) {
                if (digits[number][row] & (1u << (4 - column))) {
                    putPixel(textX + digit * 6 + column,
                             textY + row, color);
                }
            }
        }
    }
}

