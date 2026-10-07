#define VGA_WIDTH 320
#define VGA_BUFFER_ROWS 480

static volatile unsigned char *VGA =
    (volatile unsigned char *)0x08000000;

void handle_interrupt(unsigned cause)
{
    (void)cause;
}

void clearScreen(void)
{
    /* Samma buffertstorlek som i kursens demo. */
    for (int i = 0; i < VGA_WIDTH * VGA_BUFFER_ROWS; i++) {
        VGA[i] = 0;
    }
}

void putPixel(int x, int y, unsigned char color)
{
    if (x < 0 || x >= VGA_WIDTH ||
        y < 0 || y >= VGA_BUFFER_ROWS) {
        return;
    }

    VGA[y * VGA_WIDTH + x] = color;
}

void drawRectangle(int x, int y, int width, int height,
                   unsigned char color)
{
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            putPixel(x + col, y + row, color);
        }
    }
}

int main(void)
{
    volatile unsigned char *VGA =
        (volatile unsigned char *)0x08000000;

    /* Svart bakgrund. */
    for (int i = 0; i < 320 * 480; i++) {
        VGA[i] = 0;
    }

    /* Fem vita rader. */
    for (int i = 0; i < 320 * 5; i++) {
        VGA[320 * 118 + i] = 255;
    }

    /* Vit rektangel. */
    for (int y = 40; y < 90; y++) {
        for (int x = 40; x < 120; x++) {
            VGA[y * 320 + x] = 255;
        }
    }

    while (1) {
    }
}