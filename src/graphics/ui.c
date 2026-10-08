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

void drawComparison(const char *const algorithmNames[], const int resultStatus[], const int resultSteps[], const int resultCost[]){
    /* Tabellen ersätter algoritminstruktionerna. */
    drawRectangle(208, 24, 112, 64, COLOR_BLACK);

    drawText(208, 4, "ALL", COLOR_WHITE);
    drawText(208, 28, "ALG", COLOR_WHITE);
    drawText(262, 28, "S", COLOR_WHITE);
    drawText(286, 28, "C", COLOR_WHITE);

    for (int i = 0; i < 3; i++) {
        int y = 42 + i * 12;

        drawText(208, y, algorithmNames[i], COLOR_WHITE);

        if (resultStatus[i] == 0) {
            drawNumber(262, y, resultSteps[i], COLOR_YELLOW);
            drawNumber(286, y, resultCost[i], COLOR_YELLOW);
        } else {
            drawText(262, y,
                     resultStatus[i] == -1 ? "NO PATH" : "ERROR",
                     COLOR_RED);
        }
    }

    drawRectangle(8, 226, 192, 10, COLOR_BLACK);
    drawText(8, 228, "S STEPS  C COST", COLOR_WHITE);
}