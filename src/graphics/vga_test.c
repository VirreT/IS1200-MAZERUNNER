#include "graphics/graphics.h"
#include "IO/input.h"
#include "pathfinder/pathfinder.h"

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

static void drawInstructions(void)
{
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

    drawText(x, 220, "BTN: APPLY CHANGES", COLOR_YELLOW);
}

static void showTestMaze(int dim, int wallsOn)
{
    int middle = dim / 2;
    int startRow = middle - 1;
    int goalRow = middle + 1;

    for (int row = 0; row < dim; row++) {
        matrix[row] = cells[row];

        for (int column = 0; column < dim; column++) {
            /*
             * Skydda en sammanhängande väg:
             * från start till mitten,
             * ned till målets rad,
             * och sedan höger till mål.
             */
            int onSafePath = (row == startRow && column <= middle) || (column == middle && row >= startRow && row <= goalRow) || (row == goalRow && column >= middle);

            matrix[row][column].weight = 1 + nextRandom() % 20; //if only 1 all nodes = 1, now random up to 20

            node *n = &matrix[row][column];

            n->above = row > 0 ? &cells[row - 1][column] : 0;
            n->below = row < dim - 1 ? &cells[row + 1][column] : 0;
            n->left = column > 0 ? &cells[row][column - 1] : 0;
            n->right = column < dim - 1 ? &cells[row][column + 1] : 0;

            /* Ungefär 25 % väggar utanför den skyddade vägen. */
            if (wallsOn && !onSafePath) {
                if (nextRandom() % 100 < 25) {
                    matrix[row][column].weight = '#';
                }
            }
        }
    }
    matrix[startRow][0].weight = 'S';
    matrix[goalRow][dim - 1].weight = 'D';

    int cellSize = MAZE_PIXELS / dim;

    clearScreen();

    // Labyrint till vänster, instruktioner till höger
    drawMaze(matrix, dim, 8, 24, cellSize);

    drawText(8, 4, "MAZERUNNER", COLOR_WHITE);
    drawNumber(80, 4, dim, COLOR_GREEN);

    drawInstructions();
}


void pathFound(node **maze, int dim,
               const int *reversePath, int length)
{
    (void)maze;

    int cellSize = MAZE_PIXELS / dim;

    /* Hoppa över mål och start så att deras färger behålls. */
    for (int i = 1; i < length - 1; i++) {
        int id = reversePath[i];
        int row = id / dim;
        int column = id % dim;

        drawRectangle(
            8 + column * cellSize + 1,
            24 + row * cellSize + 1,
            cellSize - 1,
            cellSize - 1,
            COLOR_YELLOW
        );
    }
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

        if (input.startPressed) {
            int mazeSize = 8 << input.sizeChoice;

            if (input.sizeChoice != previousSizeChoice || input.wallsOn != previousWallsOn) {

                showTestMaze(mazeSize, input.wallsOn);

                previousSizeChoice = input.sizeChoice;
                previousWallsOn = input.wallsOn;
            } 
            else {
                
            /* Rita om samma labyrint och ta bort den gamla gula vägen. */
            drawMaze(matrix, mazeSize, 8, 24, MAZE_PIXELS / mazeSize);
            }

            /* Rensa tidigare algoritmnamn och resultat. */
            drawRectangle(208, 0, 112, 24, COLOR_BLACK);

            if (input.algorithm == 0 || input.algorithm == 1) {
                int steps;

                if (input.algorithm == 0) {
                    steps = bfs(matrix, mazeSize);
                    drawText(208, 4, "BFS", COLOR_WHITE);
                } 
                else {
                    steps = dfs(matrix, mazeSize);
                    drawText(208, 4, "DFS", COLOR_WHITE);
                }

                if (steps >= 0) {
                    drawNumber(238, 4,
                               (unsigned int)steps, COLOR_YELLOW);
                } 
                else if (steps == -1) {
                    drawText(238, 4, "NO PATH", COLOR_RED);
                } 
                else {
                    drawText(238, 4, "ERROR", COLOR_RED);
                }
            } 
            else if (input.algorithm == 2) {
                int cost = dijkstra(matrix, mazeSize);

                drawText(208, 4, "DIJKSTRA", COLOR_WHITE);

                if (cost >= 0) {
                    drawText(208, 14, "COST", COLOR_WHITE);
                    drawNumber(244, 14, (unsigned int)cost, COLOR_YELLOW);
                } 
                else if (cost == -1) {
                    drawText(208, 14, "NO PATH", COLOR_RED);
                } 
                else {
                    drawText(208, 14, "ERROR", COLOR_RED);
                }
            }
        }
    }
}
