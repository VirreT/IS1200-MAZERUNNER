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
    volatile unsigned int *timerStatus     = (volatile unsigned int *)0x04000020;
    volatile unsigned int *timerControl    = (volatile unsigned int *)0x04000024;
    volatile unsigned int *timerPeriodLow  = (volatile unsigned int *)0x04000028;
    volatile unsigned int *timerPeriodHigh =(volatile unsigned int *)0x0400002C;

    /* 30 MHz enligt LAB3: 300 000 klockcykler = 10 ms. */
    unsigned int period = 300000u - 1u;

    *timerControl = 0x8; // Stoppa timern
    *timerPeriodLow = period & 0xFFFF;
    *timerPeriodHigh = period >> 16;
    *timerStatus = 0;
    *timerControl = 0x6; // Starta kontinuerligt utan avbrott

    int sw = get_sw() & 0x1F;
    int candidateSw = sw;
    int stableReads = 0;
    int previousSw = -1;
    int previousButton = get_btn();

    while (1) {
        if (*timerStatus & 0x1) {
            *timerStatus = 0;

            int rawSw = get_sw() & 0x1F;

            if (rawSw != candidateSw) {
                candidateSw = rawSw;
                stableReads = 1;
            } else if (stableReads < 3) {
                stableReads++;
            }

            if (stableReads == 3 && candidateSw != previousSw) {
                sw = candidateSw;

                print("Algoritm: ");
                print_dec(sw & 0x3);

                print(" | Storlek: ");
                print_dec(8 << ((sw >> 2) & 0x3));

                print(" | Vaggar: ");
                print_dec((sw >> 4) & 0x1);

                print("\n");

                previousSw = sw;
            }
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