#include "helpers/randomizer.h"
#include <stdint.h>


// Written by Claude AI
#define TIMER_BASE 0x04000020

static uint32_t rng_state = 1;  // must never be 0

// Reads the current hardware timer value
uint32_t read_timer(void) {
    volatile uint16_t *t = (volatile uint16_t *) TIMER_BASE;
    t[4] = 0;                   // latch snapshot
    uint32_t lo = t[4];
    uint32_t hi = t[5];
    return (hi << 16) | lo;
}

// Seeds the generator (use clock)
void rng_seed(uint32_t seed) {
    
    if (seed == 0) {
        seed = 1;
    }
    rng_state = seed;
}

// Returns the next raw 32-bit pseudo-random value
uint32_t rng_next(x) {
    uint32_t x = rng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng_state = x;
    return x;
}

// Random number in [min, max]
uint32_t rng(uint32_t min, uint32_t max) {
    uint32_t seed = read_timer();

    return (rng_next(seed) % (max - min + 1)) + min;
}