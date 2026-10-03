//----------------------
//---- Randomizer.h ----
//----------------------

#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <stdint.h>

// Reads the current hardware timer value
uint32_t read_timer(void);

// Seeds the generator (use clock)
void rng_seed(uint32_t seed);

// Returns the next raw 32-bit pseudo-random value
uint32_t rng_next(void);

// Random number in [min, max]
uint32_t rng(uint32_t min, uint32_t max);

#endif