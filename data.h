#ifndef DATA_H
    #define DATA_H
    #include "utilities.h"

    struct Data
    {
        uint16_t data_number;   // Number of data contained in "data_array"
        uint8_t* data_array;    // Array of uint8_t containing data
    };

    // Data generation/free
    struct Data* data_generate(uint16_t data_number);
    void data_free(struct Data* d);

    // Data operations
    uint8_t data_get(uint16_t n, struct Data* d);               //Returns the n-th data stored. Starting from 0.
    void data_set(uint16_t n, uint8_t data, struct Data* d);    //Sets the n-th block of d to data
    void data_delete(uint16_t n, struct Data* d);               // Delete the n-th block of d

    uint8_t data_getBit(uint16_t n, struct Data* d);
    uint8_t data_getSequence(uint16_t n, uint8_t l, struct Data* d);
    void data_setBit(uint16_t n, uint8_t data, struct Data* d);
    void data_setSequence(uint16_t n, uint8_t l, uint8_t data, struct Data* d);

    #ifdef DEBUG
        // Prints out a data structure. Not adapted to AVR.
        void data_show(struct Data* d);
    #endif

#endif // DATA_H
