#ifndef DATA_H
    #define DATA_H
    #pragma once

    #ifndef __AVR__
        #include <inttypes.h>
        #include <stdlib.h>
    #endif // __AVR__

    #include "utilities.h"
    #include "../../config.h"

    struct Data
    {
        uint16_t data_number;   // Number of data contained in "data_array"
        uint8_t* data_array;    // Array of uint8_t containing data
    };

    // Data generation/free
    struct Data* data_generate(uint16_t data_number);

    // Data operations
    uint8_t data_get(uint16_t n, struct Data* d);               //Returns the n-th data stored. Starting from 0.
    void data_set(uint16_t n, uint8_t data, struct Data* d);    //Sets the n-th block of d to data={0,1}
    void data_delete(uint16_t n, struct Data* d);               // Delete the n-th block of d
    void data_free(struct Data* d);

    #ifdef DEBUG
        // Prints out a data structure. Not adapted to AVR.
        void data_show(struct Data* d);
    #endif
#endif // DATA_H
