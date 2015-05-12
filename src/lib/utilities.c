#include "utilities.h"

#ifdef __AVR__
    int freeRam()
    {
      extern int __heap_start, *__brkval;
      int v;
      return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
    }
#else
    char bin_to_ascii(uint8_t bin)
    {
        if (bin)
            return 49; //'1'
        else
            return 48; //'0'
    }

    uint8_t ascii_to_bin(char bin)
    {
        if (bin == 48)
            return 0;
        else
            return 1;
    }
#endif

#ifdef DEBUG
    void print_var_bits(uint8_t var)
    {
        #ifdef __AVR__
            uart_tx_str("0b");
            for(int8_t i = 0; i < 7; i++)
                uart_tx_char((var >> i) & 1 + 0x30 ); // 0x30 is the offset needed to print the appropriate number
        #else
            printf("0b");
            for(int8_t i = 0; i <7; i++)
                printf( "%d", (var >> i) & 1 );
        #endif
    }
#endif

uint8_t error(char* str)
{
    #ifdef __AVR__
        uart_tx_str(str);
        uart_newline();
        abort();
    #else
        fprintf(stderr, str);
        fprintf(stderr, "\r\n"); // New line
        system("PAUSE>NUL");
        exit(EXIT_FAILURE);
    #endif // __AVR__
}

uint16_t int_pow(uint16_t a, uint16_t b)
{
    uint16_t r = 1;

    for(uint16_t i = 0; i < b; i++)
        r = r * a;

    return r;
}

uint8_t opposite_bit(uint8_t bit)
{
    return (bit == 0) ? 1 : 0;
}
