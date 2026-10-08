#include "graphics/graphics.h"
#include "IO/input.h"
#include "pathfinder/pathfinder.h"

#include "maze/walls.h"
#include "maze/startDestination.h"
#include "graphics/ui.h"

#define MAX_SIZE 64
#define MAZE_PIXELS 192

static node cells[MAX_SIZE][MAX_SIZE];
static node *matrix[MAX_SIZE];

void handle_interrupt(unsigned cause)
{
    (void)cause;
}

static unsigned int randomState = 123456789u;

static const char *algorithmNames[4] = {
    "BFS", "DFS", "DIJKSTRA", "ALL"
};

static int savedPath[MAX_PATH_NODES];
static int savedLength;
static int savedCost;

static int resultStatus[3];
static int resultSteps[3];
static int resultCost[3];

static unsigned int nextRandom(void){
    randomState ^= randomState << 13;
    randomState ^= randomState >> 17;
    randomState ^= randomState << 5;

    return randomState;
}

static void showTestMaze(int dim, int wallsOn)
{



    for (int row = 0; row < dim; row++) {
        matrix[row] = cells[row];

        for (int column = 0; column < dim; column++) {
            /*
             * Skydda en sammanhängande väg:
             * från start till mitten,
             * ned till målets rad,
             * och sedan höger till mål.
             */
            

            matrix[row][column].weight = 1 + nextRandom() % 20; //if only 1 all nodes = 1, now random up to 20

            node *n = &matrix[row][column];

            n->above = row > 0 ? &cells[row - 1][column] : 0;
            n->below = row < dim - 1 ? &cells[row + 1][column] : 0;
            n->left = column > 0 ? &cells[row][column - 1] : 0;
            n->right = column < dim - 1 ? &cells[row][column + 1] : 0;
        }
    }
            
    setStart(matrix, dim);
    setDestination(matrix, dim);

    if (wallsOn){
        buildWalls(matrix, dim, nextRandom);
    }


    int cellSize = MAZE_PIXELS / dim;

    clearScreen();

    // Labyrint till vänster, instruktioner till höger
    drawMaze(matrix, dim, 8, 24, cellSize);

    drawText(8, 4, "MAZERUNNER", COLOR_WHITE);
    drawNumber(80, 4, dim, COLOR_GREEN);

    drawInstructions();
}


void pathFound(node **maze, int dim, const int *reversePath, int length){
    savedLength = length;
    savedCost = 0;

    int cellSize = MAZE_PIXELS / dim;

    /* Start och mål bidrar med kostnaden 0. */
    for (int i = 1; i < length - 1; i++) {
        int id = reversePath[i];
        int row = id / dim;
        int column = id % dim;

        savedCost += maze[row][column].weight;

        drawRectangle(8 + column * cellSize + 1, 24 + row * cellSize + 1, cellSize - 1, cellSize - 1, COLOR_YELLOW);
        drawCellWeight(8 + column * cellSize, 24 + row * cellSize, cellSize, (unsigned int)maze[row][column].weight,COLOR_BLACK);
    }
}

static int runAlgorithm(int algorithm, int dim){
    savedLength = 0;
    savedCost = 0;

    drawMaze(matrix, dim, 8, 24, MAZE_PIXELS / dim);

    int result = -2;

    switch (algorithm) {
        case 0:
            result = bfs(matrix, dim);
            break;
        case 1:
            result = dfs(matrix, dim);
            break;
        case 2:
            result = dijkstra(matrix, dim);
            break;
        default:
            return -2;
    }

    if (result >= 0 && savedLength > 0) {
        resultStatus[algorithm] = 0;
        resultSteps[algorithm] = savedLength - 1;
        resultCost[algorithm] = savedCost;
    } else {
        resultStatus[algorithm] = result == -1 ? -1 : -2;
    }

    return result;
}

static void drawComparison(void){
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

int main(void)
{
    InputState input;

    input_init();
    input_update(&input);

    showTestMaze(8 << input.sizeChoice, input.wallsOn);

    int previousSizeChoice = input.sizeChoice;
    int previousWallsOn = input.wallsOn;

    while (1) {
        input_update(&input);

        if (!input.startPressed)
            continue;

        int mazeSize = 8 << input.sizeChoice;

        if (input.sizeChoice != previousSizeChoice || input.wallsOn != previousWallsOn || input.newMaze) {

            showTestMaze(mazeSize, input.wallsOn);

            previousSizeChoice = input.sizeChoice;
            previousWallsOn = input.wallsOn;
        } else {
            drawMaze(matrix, mazeSize, 8, 24, MAZE_PIXELS / mazeSize);
        }

        drawRectangle(208, 0, 112, 24, COLOR_BLACK);
        drawRectangle(8, 226, 192, 10, COLOR_BLACK);

        /* Återställ instruktionerna efter en tidigare jämförelse. */
        drawRectangle(208, 24, 112, 64, COLOR_BLACK);
        drawInstructions();

        if (input.algorithm == 3) {
            for (int i = 0; i < 3; i++)
                runAlgorithm(i, mazeSize);

            drawComparison();
            continue;
        }

        int result = runAlgorithm(input.algorithm, mazeSize);

        drawText(208, 4, algorithmNames[input.algorithm], COLOR_WHITE);

        if (result >= 0 && savedLength > 0) {
            drawText(8, 228, "STEPS", COLOR_WHITE);
            drawNumber(50, 228, (unsigned int)(savedLength - 1), COLOR_YELLOW);

            drawText(90, 228, "COST", COLOR_WHITE);
            drawNumber(126, 228, (unsigned int)savedCost,COLOR_YELLOW);
        } else if (result == -1) {
            drawText(208, 14, "NO PATH", COLOR_RED);
        } else {
            drawText(208, 14, "ERROR", COLOR_RED);
        }
    }
}
