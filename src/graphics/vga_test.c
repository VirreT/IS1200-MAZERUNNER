#include "graphics/graphics.h"

void handle_interrupt(unsigned cause)
{
    (void)cause;
}

int main(void)
{
    clearScreen();

    /*
     * Position: x = 60, y = 20
     * Rutnät: 8 rader och 8 kolumner
     * Avstånd mellan linjerna: 24 pixlar
     */
    drawGrid(60, 20, 8, 8, 24, COLOR_WHITE);

    while (1) {
    }
}