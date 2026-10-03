#include <stdio.h>
#include <stdlib.h>

#include "maze/MatrixGenerator.h"
#include "maze/StartDestination.h"

int get_sw(void);
int get_btn(void);
int bfs(node **matrix, int dim);

int main(void){
    int previousButton = 0;
    int previousWallsOn = 0;
    int previousSizeChoice = -1; // Is used to create matrix at start

    int mtxSize = 0;
    node **matrix = NULL;

    while(1){
        int sw = get_sw();
        int button = get_btn();

        int algorithm = sw & 0x3;           // SW0-SW1
        int sizeChoice = (sw >> 2) & 0x3;   //SW2-SW3
        int wallsOn = (sw >> 4) & 0x1;      //SW4

        int sizeChanged = sizeChoice != previousSizeChoice;

        /**
         * Generate matrix at start or when size is changed
         */
        if (sizeChanged){
            if (matrix != NULL){
                freeMatrix(matrix, mtxSize);
            }

            mtxSize = 8 << sizeChoice;
            matrix = generateMatrix(mtxSize);
            linkMatrix(matrix, mtxSize);

            setStart(matrix, mtxSize);
            setDestination(matrix, mtxSize);

            printMatrix(matrix, mtxSize);
            printNode(&matrix[1][1]);
            
            printf("Size: %d x %d\n", mtxSize, mtxSize);
        }


        /* 
         * Generate walls when SW4 is tunred on, 
         * or when a new matrix is generated with SW4 tuned on
         */
        if (wallsOn && (sizeChanged || !previousWallsOn)){
            // Anropa väggfunktion med matrix och mtxSize här
        }       
        
        
        /* Remove walls when SW4 is turned off
         * A new matrix has already been made without walls
         */    
        if (!wallsOn && previousWallsOn && !sizeChanged){
                // anropa funktion som tar bort väggarna
        }        
        
        /*
         * Choose what algorithm to run 
         */
        if (button && !previousButton){
            switch (algorithm){
                case 0:
                printf("BFS vald\n");
                bfs(matrix, mtxSize);
                break;

                case 1:
                printf("DFS vald\n");
                // Anropa DFS här
                break;

                case 2:
                printf("Djikstra vald\n");
                // Anropa Djikstra här
                break;

                case 3:
                printf("Jamforelselage valt\n");
                // Kör och jämför algortimerna här
                break;
            }
        }
        previousSizeChoice = sizeChoice;
        previousWallsOn = wallsOn;
        previousButton = button; // Prevents the program to restart whilst the button is being pressed down
    }
}