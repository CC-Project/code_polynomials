#include "poly_codes.h"

struct Data* poly_div(struct Data* poly)
{
    if(BASE_L == 1)
    {

    }
    else
        error("poly_div: Not implemented\n")
}

struct Data* poly_encode(struct Data* message)
{
    //Move the bits to the right by K: X^n times M
    struct Data* message_mul = data_generate(N);
    if(BASE_L == 1)
    {
        for(uint16_t i=0; i<message->data_number; i++)
        {
           data_set(i+K, data_get(i, message), message_mul);
        }

        struct Data* data_word = poly_div(message_mul);
        data_free(message_mul);
    }
    else
        error("poly_encode: Not implemented\n")

    return encoded_message;
}

struct Data* poly_decode(struct Data* codeword)
{
    return NULL;
}

uint8_t poly_check(struct Data* message)
{
    return 1;
}
