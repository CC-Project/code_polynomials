#include "../include/utilities.h"

#ifdef __AVR__
    void uart_init(void)
    {
        UBRR0L = BAUD_RATE; 						//Set baud rate to 38400. Assuming internal clock is 16MHz
        UCSR0C = (1 << UCSZ00 ) | (1 << UCSZ01 ); 	//8 bits characters,
        UCSR0B = (1 << RXEN0 ) | (1 << TXEN0 );		// Turn on the transmission and reception circuitry
    }

    void uart_tx_char(char c)
    {
        while( !(UCSR0A & (1 << UDRE0)) ); //Wait until UDR empty
        UDR0 = c;
    }

    void uart_tx_str(int8_t* str)
    {
        while(*str)
            uart_tx_char(*str++);
        uart_newline();
    }

    void uart_newline(void)
    {
        uart_tx_char('\r');
        uart_tx_char('\n');
    }

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
            uart_tx_str("0b")
            for(int8_t i = 0; i < 7; i++)
                uart_tx_char((var >> i) & 1 + 0x30 ); //0x30 is the offset needed to print the appropriate number
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
        fprintf(stderr, "\r\n"); //New line
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
