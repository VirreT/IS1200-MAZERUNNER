
#include "maze/MatrixGenerator.h"
#include "maze/startDestination.h"

#include "IO/input.h"
#include "dtekv-lib.h"


int bfs(node **matrix, int dim);
int dfs(node **matrix, int dim);
int dijkstra(node **matrix, int dim);
void buildWalls(node **matrix, int dim);

void handle_interrupt(unsigned cause)
{
    (void)cause;
}

int main(void){
    
    input_init();

    InputState input;

    node **matrix = 0;
    int mazeSize = 0;

    int previousSizeChoice = -1; // Is used to create matrix at start
    int previousWallsOn = -1;
    int previousAlgorithm = -1;

    while(1){

        input_update(&input);

        int algorithm = input.algorithm;           // SW0-SW1
        int sizeChoice = input.sizeChoice;   //SW2-SW3
        int wallsOn = input.wallsOn;      //SW4

        int sizeChanged = sizeChoice != previousSizeChoice;

        int wallsChanged = wallsOn != previousWallsOn;

        /**
         * Generate matrix at start or when size is changed
         */
        if (sizeChanged || wallsChanged){
            if (matrix != 0){
                freeMatrix(matrix, mazeSize);
            }

            mazeSize = 8 << sizeChoice;
            matrix = generateMatrix(mazeSize);

            if(matrix == 0){
                print("Could not create matrix. \n");
                return 1;
            }

            linkMatrix(matrix, mazeSize);
            setStart(matrix, mazeSize);
            setDestination(matrix, mazeSize);

            if(wallsOn){
                buildWalls(matrix, mazeSize);
            }

            print("New labrinth: ");
            print_dec(mazeSize);
            print(" x ");
            print_dec(mazeSize);

            print(" | Vaggar: ");
            print_dec(wallsOn);
            print("\n");

            previousSizeChoice = sizeChoice;
            previousWallsOn = wallsOn;
        }

        if (algorithm != previousAlgorithm) {
            print("Chosen algoritm: ");

            switch (algorithm) {
                case 0:
                    print("BFS\n");
                    break;

                case 1:
                    print("DFS\n");
                    break;

                case 2:
                    print("Dijkstra\n");
                    break;

                case 3:
                    print("Comparison\n");
                    break;
            }

            previousAlgorithm = algorithm;
        }

        if (input.startPressed){
            switch (algorithm){
                case 0:
                print("BFS chosen\n");
                bfs(matrix, mazeSize);
                break;

                case 1:
                print("DFS chosen\n");
                dfs(matrix, mazeSize);
                break;

                case 2:
                print("Dijkstra chosen\n");
                dijkstra(matrix, mazeSize);
                break;

                case 3:
                print("Comparison chosen\n");
                print("BFS chosen\n");
                bfs(matrix, mazeSize);
                
                print("DFS chosen\n");
                dfs(matrix, mazeSize);

                print("Dijkstra chosen\n");
                dijkstra(matrix, mazeSize);
                break;
                
            }
            print("Done! \n");   
        }
    }
}