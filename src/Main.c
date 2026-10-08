#include "graphics/graphics.h"
#include "IO/input.h"
#include "pathfinder/pathfinder.h"
#include "graphics/ui.h"
#include "maze/MatrixGenerator.h"

#define MAZE_PIXELS 192

static node **matrix;

static int savedLength;
static int savedCost;

static int resultStatus[3];
static int resultSteps[3];
static int resultCost[3];

static const char *algorithmNames[4] = {
    "BFS", "DFS", "DIJKSTRA", "ALL"
};

void handle_interrupt(unsigned cause){
    (void)cause;
}

static void showTestMaze(int dim, int wallsOn){
    matrix = generateMaze(dim, wallsOn);

    if (matrix == 0)
        return;

    int cellSize = MAZE_PIXELS / dim;

    clearScreen();
    drawMaze(matrix, dim, 8, 24, cellSize);

    drawText(8, 4, "MAZERUNNER", COLOR_WHITE);
    drawNumber(80, 4, dim, COLOR_GREEN);

    drawInstructions();
}

void pathFound(node **maze, int dim, const int *reversePath, int length){
    savedLength = length;
    savedCost = 0;

    // Start och mål bidrar med kostnaden 0
    for (int i = 1; i < length - 1; i++) {
        int id = reversePath[i];
        int row = id / dim;
        int column = id % dim;

        savedCost += maze[row][column].weight;
    }

    drawSolution(maze, dim, reversePath, length, MAZE_PIXELS / dim);
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
        resultSteps[algorithm]  = savedLength - 1;
        resultCost[algorithm]   = savedCost;
    } else {
        resultStatus[algorithm] = result == -1 ? -1 : -2;
    }
    return result;
}

int main(void){
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

        // Återställ instruktionerna efter en tidigare jämförelse
        drawRectangle(208, 24, 112, 64, COLOR_BLACK);
        drawInstructions();

        if (input.algorithm == 3) {
            for (int i = 0; i < 3; i++)
                runAlgorithm(i, mazeSize);

            drawComparison(algorithmNames, resultStatus, resultSteps, resultCost);
            continue;
        }

        int result = runAlgorithm(input.algorithm, mazeSize);

        drawResult(algorithmNames[input.algorithm], result, savedLength, savedCost);
    }
}
