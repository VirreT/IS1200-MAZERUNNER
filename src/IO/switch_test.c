#include "dtekv-lib.h"


int get_sw(void);

int get_btn(void);

/* Krävs av kursens boot.S.
   Testet aktiverar inga avbrott. */
void handle_interrupt(unsigned cause){
    (void)cause;
}

int main(void){
    volatile unsigned int *timerStatus   = (volatile unsigned int *)0x04000020;
    volatile unsigned int *timerControl  = (volatile unsigned int *)0x04000024;
    volatile unsigned int *timer_periodl = (volatile unsigned int *)0x04000028;
    volatile unsigned int *timer_periodh = (volatile unsigned int *)0x0400002C;

    *timerControl = 0x8; // STOP
    
    *timer_periodl = 0xC6BF;
    *timer_periodh = 0x002D;

    *timerStatus = 0;
    *timerControl = 0x6; // START and CONT

    int sw = get_sw() & 0x1F;
    int candidateSw = sw;
    int stableReads = 0;
    int previousSw = -1;
    int previousButton = get_btn();

    while (1) {
        // Check switches every time 100ms has passed
        if (*timerStatus & 0x1) {
            *timerStatus = 0;

            int rawSw = get_sw() & 0x1F;

            if (rawSw != candidateSw) {
                candidateSw = rawSw;
                stableReads = 1;
            } else if (stableReads < 2) {
                stableReads++;
            }

            // Godkänn två lika avläsningar 100 ms isär
            if (stableReads == 2 && candidateSw != previousSw) {
                sw = candidateSw;

                int algorithm = sw & 0x3;
                int sizeChoice = (sw >> 2) & 0x3;
                int wallsOn = (sw >> 4) & 0x1;
                int mazeSize = 8 << sizeChoice;

                print("Algoritm: ");
                print_dec(algorithm);

                print(" | Storlek: ");
                print_dec(mazeSize);

                print(" | Vaggar: ");
                print_dec(wallsOn);

                print("\n");

                previousSw = sw;
            }
        }

        // Kontrollera knappen varje varv i loopen
        int button = get_btn();

        if (button && !previousButton) {
            print("START: algoritm ");
            print_dec(sw & 0x3);
            print("\n");
        }

        previousButton = button;
    }
}
