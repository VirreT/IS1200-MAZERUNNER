#include <stdint.h>
#include <stdio.h>

#define TIMER_BASE 0x04000020

//reads current hardware timer value
uint32_t read_timer(void) {
    volatile uint16_t *t = (volatile uint16_t *) TIMER_BASE;
    t[4] = 0;                          // write to snapshot to latch a snapshot
    uint32_t lo = t[4];                // snapshot
    uint32_t hi = t[5];                // snapshot
    return (hi << 16) | lo;
}

static uint32_t rng_state = 1;   // must never be 0

//Seeds the given seed (will use clock)
void rng_seed(uint32_t seed) {
    rng_state = seed;

    if (seed == 0) {
        rng_state = 1; // Ensure the state is never zero
    }
}

uint32_t rng_next(void) {
    uint32_t x = rng_state;
    x ^= x << 13;
    x ^= x >> 17; 
    x ^= x << 5;
    rng_state = x;
    return x;
}

// Random number in [min, max]
uint32_t rng(uint32_t min, uint32_t max) {
    return (rng_next() % (max - min + 1)) + min;
}


int main() {
    rng_seed(4342); // Seed the rng with a specific value (clock when intergrating to DTEK-V)

    int sum = 0;
    int count = 0;

    for (int i = 0; i < 1000; i++) {
        uint32_t random_num = rng(0, 10);
        printf("%u\n", random_num);
        sum += random_num;
        count++;
    }

    printf("Sum: %d, Count: %d\n", sum, count);
    printf("Mean: %.2f\n", (double)sum / count);

    return 0;
}