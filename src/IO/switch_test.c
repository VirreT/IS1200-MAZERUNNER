int get_sw(void);

/* Krävs av kursens boot.S.
   Testet aktiverar inga avbrott. */
void handle_interrupt(unsigned cause)
{
    (void)cause;
}

int main(void)
{
    volatile unsigned int *leds =
        (volatile unsigned int *)0x04000000;

    while (1) {
        *leds = (unsigned int)get_sw() & 0x3FF;
    }
}