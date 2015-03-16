#ifndef UTILITIES_H
    #define UTILITIES_H
    #pragma once

    #include "../../config.h"

    #ifdef __AVR__
        void uart_init(void);
        void uart_tx_char(char c);
        void uart_tx_str(int8_t* str);
        void uart_newline(void);
        int freeRam(); //Returns the memory available
    #else
        #include <inttypes.h>
        #include <stdlib.h>
        #include <stdio.h>
        char bin_to_ascii(uint8_t bin);
        uint8_t ascii_to_bin(char bin);
    #endif

    #ifdef DEBUG
           void print_var_bits(uint8_t var);
    #endif

    uint8_t error(char* str); // Exit the program with the error code EXIT_FAILED
    uint16_t int_pow(uint16_t a, uint16_t b);   //Computes a^b
    uint8_t opposite_bit(uint8_t bit);

#endif // UTILITIES_H
