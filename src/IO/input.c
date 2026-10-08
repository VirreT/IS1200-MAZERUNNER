
#include "IO/input.h"

int get_sw(void);
int get_btn(void);

static int stableSw;
static int candidateSw;
static int stableReads;
static int previousButton;

void input_init(void)
{
    volatile unsigned int *timerStatus     = (volatile unsigned int *)0x04000020;
    volatile unsigned int *timerControl    = (volatile unsigned int *)0x04000024;
    volatile unsigned int *timer_periodl  = (volatile unsigned int *)0x04000028;
    volatile unsigned int *timer_periodh = (volatile unsigned int *)0x0400002C;

    *timerControl = 0x8;
    
    *timer_periodl = 0xC6BF;
    *timer_periodh = 0x002D;
    
    *timerStatus = 0;
    *timerControl = 0x6;

    stableSw = get_sw() & 0x3F;
    candidateSw = stableSw;
    stableReads = 0;
    previousButton = get_btn();
}

void input_update(InputState *input)
{
    volatile unsigned int *timerStatus =
        (volatile unsigned int *)0x04000020;

    if (*timerStatus & 0x1) {
        *timerStatus = 0;

        int rawSw = get_sw() & 0x3F;

        if (rawSw != candidateSw) {
            candidateSw = rawSw;
            stableReads = 1;
        } else if (stableReads < 2) {
            stableReads++;
        }

        if (stableReads == 2) {
            stableSw = candidateSw;
        }
    }

    input->algorithm = stableSw & 0x3;
    input->sizeChoice = (stableSw >> 2) & 0x3;
    input->wallsOn = (stableSw >> 4) & 0x1;
    input->newMaze = (stableSw >> 5) & 1;

    int button = get_btn();

    input->startPressed = button && !previousButton;
    previousButton = button;
}

