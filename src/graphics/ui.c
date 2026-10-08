#include "graphics/ui.h"
#include "graphics/graphics.h"

void drawInstructions(void){
    int x = 208;

    drawText(x, 28, "SW1 SW0: ALGORITHM", COLOR_WHITE);
    drawText(x, 42, "00 BFS", COLOR_GRAY);
    drawText(x, 54, "01 DFS", COLOR_GRAY);
    drawText(x, 66, "10 DIJKSTRA", COLOR_GRAY);
    drawText(x, 78, "11 ALL", COLOR_GRAY);

    drawText(x, 100, "SW3 SW2: SIZE", COLOR_WHITE);
    drawText(x, 114, "00 8X8", COLOR_GRAY);
    drawText(x, 126, "01 16X16", COLOR_GRAY);
    drawText(x, 138, "10 32X32", COLOR_GRAY);
    drawText(x, 150, "11 64X64", COLOR_GRAY);

    drawText(x, 172, "SW4: WALLS", COLOR_WHITE);
    drawText(x, 186, "0 OFF", COLOR_GRAY);
    drawText(x, 198, "1 ON", COLOR_GRAY);

    drawText(x, 210, "SW5: NEW MAZE", COLOR_WHITE);
    drawText(x, 228, "BTN: RUN", COLOR_YELLOW);
}