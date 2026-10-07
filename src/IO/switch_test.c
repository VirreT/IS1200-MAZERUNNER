#include "dtekv-lib.h"


int get_sw(void);

int get_btn(void);

/* Krävs av kursens boot.S.
   Testet aktiverar inga avbrott. */
void handle_interrupt(unsigned cause)
{
    (void)cause;
}

int main(void)
{
    int previousSw = -1;
    int previousButton = get_btn();

    while (1) {
        int sw = get_sw();

        if (sw != previousSw) {
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

            int button = get_btn();

            if (button && !previousButton) {
                print("START: algoritm ");
                print_dec(sw & 0x3);
                print("\n");
            }

            previousButton = button;
    }
}