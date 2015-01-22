#include "data.h"

// Data generation/free
struct Data* data_generate(uint16_t data_number)
{
    //Allocates memory for the struct
    struct Data* d = malloc(sizeof(struct Data));
    if (d == NULL)
         error("ERROR : data_generate : Dynamic allocation not possible for the data structure");

    //Allocates memory for the array
    uint16_t n = (BASE_L * data_number - 1)/8 + 1; // Number of byte needed
    d->data_array = calloc(n,sizeof(uint8_t)); //Automatically sets the bits to zero
    if (d->data_array == NULL)
         error("ERROR : data_generate : Dynamic allocation not possible for the array");

    //Sets the data_number field
    d->data_number = data_number;

    return d;
}

void data_free(struct Data* d)
{
    free(d->data_array);
    free(d);
}



// Data operations
uint8_t data_get(uint16_t n, struct Data* d)
{
    if(n < d->data_number)
    {
        /*
            If log2(n) is an integer, then all the sequence is on a table, so we can make a fast get-method
            Else, we must get the bits one by one and recreate the sequence
        */

        if(BASE_L == 1 || BASE_L == 2 || BASE_L == 4 || BASE_L == 8) // If a power of 2.
        {
            uint16_t i = BASE_L * n;     // First bit containing the data. First bit is 0, to 7.
            uint8_t it = i % 8;     // First bit in the byte containing the data

            uint8_t data = d->data_array[i / 8];

            data <<= it;
            data >>= (8 - BASE_L);

            return data;
        }
        else
            return data_getSequence(BASE_L * n, BASE_L, d);
    }
    else
        error("ERROR: Incorect data number. Function data_get");
    return EXIT_FAILURE;
}

void data_set(uint16_t n, uint8_t data, struct Data* d)
{
    if(n < d->data_number)
    {
        if(BASE_L == 1 || BASE_L == 2 || BASE_L == 4 || BASE_L == 8) // If it is a power of 2
        {
            if(0 <= data && data <= BASE_D - 1)
            {
                uint16_t i = BASE_L * n;    // First bit containing the data. First bit is 0, to 7.
                uint8_t it = i % 8;         // First bit in the byte containing the data

                uint8_t data1 = d->data_array[i / 8]; uint8_t data2 = d->data_array[i / 8];
                data1 >>= 8 - it; data1 <<= 8 - it;
                data2 <<= it + BASE_L; data2 >>= it + BASE_L;

                d->data_array[i / 8] = ((data) << (8 - BASE_L - it)) | (data1 | data2);
            }
            else
                error("ERROR: Incorect data value. Function data_set");
        }
        else
            data_setSequence(BASE_L * n, BASE_L, data, d);
    }
    else
        error("ERROR: Incorect data number. Function data_set.");
}

void data_delete(uint16_t n, struct Data* d)
{
    if (0 <= n && n < d->data_number)
    {
        for(uint16_t i = n; i < d->data_number - 1; i++)
            data_set(i, data_get(i + 1, d), d);

        /*
            Determines wether or not it is necessary to allocate a new block of memory.
            Number of byte needed. Taken from data_generate: floor((d->data_base.l * d->data_number - 1)/8) + 1
        */
        uint16_t a = (BASE_L * (d->data_number - 1) - 1)/8 + 1;
        uint16_t b = (BASE_L * (d->data_number / 8)) + 1;

        if(a < b)
            d->data_array = realloc(d->data_array, a);
        else
            data_set(d->data_number - 1, 0, d);

        d->data_number -= 1;
    }
    else
        error("ERROR: Deleting a wrong block. Function data_delete.");
}




uint8_t data_getBit(uint16_t n, struct Data* d)
{
    if(n <= d->data_number * BASE_L)
    {
        uint8_t data = d->data_array[n / 8];

        data <<= (n % 8);
        data >>= 7;

        return data;
    }
    else
        return error("ERROR: Incorect data number. Function data_getBit.");
    return EXIT_FAILURE;
}

uint8_t data_getSequence(uint16_t n, uint8_t l, struct Data* d)
{
    if(n + (l - 1) < d->data_number * BASE_L)
    {
        uint8_t result = 0;
        for(uint8_t i = 0; i < l; i++)
        {
            result <<= 1;
            result |= data_getBit(n + i, d);
        }

        return result;
    }
    else
        error("ERROR: Incorect data number. Function data_getSequence.");
    return EXIT_FAILURE;
}

void data_setBit(uint16_t n, uint8_t data, struct Data* d)
{
    if(n < d->data_number * BASE_L)
    {
        if(0 <= data && data <= 1)
        {
            uint8_t it = n % 8;     // First bit in the byte containing the data
            uint8_t data1 = d->data_array[n / 8]; uint8_t data2 = d->data_array[n / 8];

            data1 >>= 8 - it; data1 <<= 8 - it;
            data2 <<= it + 1; data2 >>= it + 1;

            d->data_array[n / 8] = ((data) << (7 - it)) | (data1 | data2);
        }
        else
            error("ERROR: Incorect data value. Function data_setBit.");
    }
    else
        error("ERROR: Incorect data number. Function data_setBit.");
}

void data_setSequence(uint16_t n, uint8_t l, uint8_t data, struct Data* d)
{
    if(n + (l - 1) < d->data_number * BASE_L)
    {
        if(0 <= data && data <= BASE_D - 1)
        {
            //Put the sequence to replace in a data
            struct Data * dBis = data_generate(1);
            dBis->data_array[0] = data;

            for(uint8_t i = 0; i < l; i++)
                data_setBit((n + (l - 1)) - i, data_getBit((8 - 1) - i, dBis), d);

            data_free(dBis);
        }
        else
            error("ERROR: Incorect data value. Function data_setSequence.");
    }
    else
        error("ERROR: Incorect data number. Function data_setSequence.");
}



#ifdef DEBUG
    void data_show(struct Data* d)
    {
        uint8_t data;
        #ifdef __AVR__

        #else
            printf("\nShow %d data :\n", d->data_number);
            for(uint16_t i = 0; i < d->data_number; i++)
            {
                data = data_get(i, d);
                printf("%d ", data);
                printf(" | ");
                print_var_bits(data);
                printf("\n");
            }
            printf("\n\n");
        #endif // __AVR__
    }
#endif
