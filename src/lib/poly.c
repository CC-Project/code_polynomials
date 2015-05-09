#include "../include/polynome.h"

Poly data_copy(struct Data* word)
{
    Poly copy = data_generate(N);
    for(uint16_t i = 0; i<word->data_number; i++)
        data_set(i, data_get(i, word), copy);

    return copy;
}

Poly generator_to_poly(void)
{
    Poly poly = data_generate(N);
    for(uint16_t i = 0; i < M + 1; i++)
        data_set(i, G&(1<<i), poly);

    return poly;
}

void data_rshift(Poly* word, uint16_t n)
{
    Poly message_mul = data_generate(N);
    for(uint16_t i = 0; i < N; i++)
       data_set((i+n)%N, data_get(i, *word), message_mul);

    data_free(*word);
    *word = message_mul;
}

uint16_t poly_deg(Poly poly)
{
    uint16_t n = poly->data_number;
    while(n > 1) // n > 1 to work with the zero polynomial
        if(data_get(n - 1, poly) == 1)
            break;
        else
            n--;

    return n - 1;
}

uint8_t poly_lead(Poly poly)
{
    uint16_t d = poly_deg(poly);

    return data_get(d, poly);
}

void poly_add(Poly* x, Poly y)
{
    for(uint16_t i = 0; i < N; i++)
        data_set(i, data_get(i, *x) ^ data_get(i, y), *x);
}

Poly poly_mul_sca(uint8_t sca, Poly poly)
{
    Poly result = data_generate(N);

    if (sca)
        for(uint16_t i = 0; i< poly->data_number; i++)
            data_set(i, data_get(i, poly), result);

    return result;
}

Poly poly_mul(Poly poly)
{
    Poly result = data_generate(N);
    Poly temp = NULL; // Degree N

    for(uint16_t i = 0; i<N+1; i++)
    {
        uint8_t j = G & (1 << i);
        temp = poly_mul_sca(j, poly);
        data_rshift(&temp, i);
        poly_add(&result, temp);
        data_free(temp);
    }

    return result;
}

Poly* poly_div(Poly poly)
{
    //a = G*q + r
    Poly generator = generator_to_poly();
    Poly a = data_copy(poly);
    Poly q = data_generate(N); // Check the size

    uint16_t deg_a = poly_deg(a);
    uint16_t i = deg_a - M;

    while(deg_a >= M)
    {
        Poly g_copy = data_copy(generator);
        data_rshift(&g_copy, i);
        poly_add(&a, g_copy);
        deg_a = poly_deg(a);
        data_free(g_copy);
        data_set(i, 1, q);
        i = deg_a - M;
    }

    data_free(generator);
    Poly* result = malloc(2*sizeof(Poly));
    result[0] = q;
    result[1] = a;

    return result; // Returns the couple (quotient, remainder)
}

Poly poly_encode(Poly message)
{
    // Move the bits to the right by K: X^n times Message
    Poly poly = data_copy(message);
    data_rshift(&poly, M);
    Poly* tmp = poly_div(poly);
    Poly encoded_word = poly_mul(tmp[0]);

    data_free(poly);
    data_free(tmp[0]);
    data_free(tmp[1]);
    free(tmp);

    return encoded_word;
}

Poly poly_decode(Poly message)
{
    uint8_t codeword = 1;
    Poly* result = poly_div(message);

    for(uint16_t i = 0; i < result[1]->data_number; i++)
        if (data_get(i, result[1]) != 0)
        {
            codeword = 0;
            break;
        }

    data_free(result[0]);
    data_free(result[1]);
    free(result);

    if(!codeword)
        return NULL;
    else
    {
        Poly decoded_message = data_generate(K);

        for(uint16_t j = 0; j < decoded_message->data_number; j++)
            data_set(j, data_get(j+M, message), decoded_message);

        return decoded_message;
    }
}
