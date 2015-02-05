#include "poly_codes.h"

struct Data* data_copy(struct Data* word)
{
    struct Data* copy = data_generate(N);
    for(uint16_t i = 0; i<word->data_number; i++)
        data_set(i, data_get(i, word), copy);
    return copy;
}

void data_rshift(struct Data** word, uint16_t n)
{
    struct Data* message_mul = data_generate(N);

    for(uint16_t i=0; i<N; i++)
    {
       data_set((i+n)%N, data_get(i, *word), message_mul);
    }

    data_free(*word);
    *word = message_mul;
}

struct Data* generator_to_poly(void)
{
    struct Data* poly = data_generate(N);
    for(uint16_t i = 0; i<M+1; i++)
        data_set(i, G&(1<<i), poly);
    return poly;
}

uint16_t poly_deg(struct Data* poly)
{
    uint16_t n = poly->data_number;
    uint8_t m = 1; //Invariant de boucle.
    while( n > 1 && m){ //n>1 to work with the zero polynomial
        if(data_get(n-1, poly) == 1){
            m = 0;
        }
        else{
            n--;
        }

    }
    return n-1;
}

uint8_t poly_lead(struct Data* poly)
{
    uint16_t d = poly_deg(poly);
    return data_get(d,poly);
}

void poly_add(struct Data** x, struct Data* y)
{
    for(uint16_t i = 0; i<N; i++)
        data_set(i,data_get(i,*x)^data_get(i,y), *x);
}

struct Data* poly_mul_sca(uint8_t sca, struct Data* poly)
{
    struct Data* result = data_generate(N);
    if (sca)
    {
        for(uint16_t i = 0; i< poly->data_number; i++)
            data_set(i, data_get(i, poly), result);
    }
    return result;
}

struct Data* poly_mul(struct Data* poly)
{
    struct Data* result = data_generate(N);
    struct Data* temp = NULL; //Degree N

    for(uint16_t i = 0; i<M+1; i++)
    {
        uint8_t j = G & (1 << i);
        temp = poly_mul_sca(j, poly);
        data_rshift(&temp, i);
        poly_add(&result, temp);
        data_free(temp);
    }
    return result;
}

struct Data* poly_div(struct Data* poly)
{
    /*
        a = G*q + r
    */
    struct Data* q = data_generate(N);
    struct Data* a = data_copy(poly);
    uint16_t deg_a = poly_deg(a);
    struct Data* generator = generator_to_poly();

    while( deg_a >= M)
    {
        if(deg_a == M)
        {
            poly_add(&a,generator);
            deg_a = poly_deg(a);
        }
        else
        {
            struct Data* copy = data_copy(generator);
            data_rshift(&copy, 1);
            poly_add(&a, copy);
            deg_a = poly_deg(a);
            data_free(copy);
        }
    }

    data_free(q);
    data_free(generator);
    return a; //Returns the remainder
}

struct Data* poly_encode(struct Data* message)
{
    //Move the bits to the right by K: X^n times Message
    struct Data* message_mul = data_generate(N);

    //data_shift

    struct Data* data_word = poly_div(message_mul);
    data_free(message_mul);

    return data_word;
}

struct Data* poly_decode(struct Data* codedword)
{
    return NULL;
}

uint8_t poly_check(struct Data* message)
{
    return 1;
}
