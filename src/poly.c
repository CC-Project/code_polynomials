#include "poly.h"

Poly data_copy(struct Data* word)
{
    Poly copy = data_generate(word->data_number);
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

uint8_t poly_equality(Poly a, Poly b)
{
    uint8_t i = 0;
    uint16_t d = a->data_number;
    while(i < d)
    {
        if(data_get(i, a) == data_get(i, b))
            i++;
        else
            i = d+1;
    }
    return (i == d+1) ? 0 : 1;
}

void data_rshift(Poly* word, uint16_t n)
{
    Poly message_mul = data_generate((*word)->data_number);
    uint16_t i = 0;
    for(i = 0; i < (*word)->data_number; i++)
       data_set((i+n)%(*word)->data_number, data_get(i, *word), message_mul);

    data_free(*word);
    *word = message_mul;
}

uint16_t poly_deg(Poly poly)
{
    uint16_t n = poly->data_number;
    while(n > 1 && data_get(n-1, poly) == 0) // n > 1 to work with the zero polynomial
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
    uint32_t m = ((*x)->data_number <= y->data_number) ? (*x)->data_number : y->data_number; // Simple min func
    for(uint16_t i = 0; i < m; i++)
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
    uint32_t i = poly_deg(poly);
    uint16_t g = poly_deg(generator);

    Poly* result = malloc(2*sizeof(Poly));
    Poly q = data_generate(abs(i - g) + 1);
    Poly a = data_copy(poly);

    if(i >= g)
    {
        uint16_t j = 0;

        while(i>0 && i>= g)
        {
            data_set(i-g, 1, q);
            for(j=0; j<=g; j++){
                data_set(i-j, data_get(i-j, a) ^ data_get(g - j, generator), a);
            }
            i = poly_deg(a);
        }
    }

    //Copy a in remainder (nedd a size of K)
    Poly remainder = data_generate(K);
    i = 0;

    for(i=0; i<K; i++)
        data_set(i, data_get(i, a), remainder);

    data_free(a);
    result[0] = q;
    result[1] = remainder;

    return result; // Returns the couple (quotient, remainder)
}

Poly poly_encode(Poly message)
{
    //Copy the message make it of length N
    Poly poly = data_generate(N);
    for(uint16_t i = 0; i<message->data_number; i++)
        data_set(i, data_get(i, message), poly);

    data_rshift(&poly, M);

    Poly* tmp = poly_div(poly);
    Poly encoded_word = poly_mul(tmp[0]);

    data_free(poly);
    data_free(tmp[0]);
    data_free(tmp[1]);
    free(tmp);

    return encoded_word;
}

uint8_t poly_is_codeword(Poly message)
{
    uint8_t codeword = 1;
    Poly* result = poly_div(message);

    uint16_t i = 0;
    for(i = 0; i < result[1]->data_number; i++)
        if (data_get(i, result[1]) != 0)
        {
            codeword = 0;
            break;
        }

    data_free(result[0]);
    data_free(result[1]);
    free(result);
    return codeword;
}


Poly poly_decode(Poly message)
{
    //If there was an error, locate the faulty bit
    if(!poly_is_codeword(message))
    {
        #ifdef DEBUG
            printf("Error detected\r\n");
        #endif
        Poly* res = poly_div(message);
        uint16_t i = 0;
        while(i < N)
        {
            if(poly_equality(syndrome[i], res[1])) //We located the faulty bit
            {
                #ifdef DEBUG
                    printf("Bit %d is faulty.\nCorrect codeword was:\n", i);
                #endif

                //Correction
                Poly tmp = data_generate(message->data_number);
                data_set(i, 1, tmp);
                poly_add(&message, tmp);
                data_free(tmp);

                #ifdef DEBUG
                    data_show(message);
                #endif // DEBUG

                i = N; //Exit the loop
            }
            else
                i++;
        }
    }
    #ifdef DEBUG
    else
    {
        printf("No errors detected\r\n");
    }
    #endif

    //Decode the message by getting rid of the M last bits
    Poly decoded_message = data_generate(K);
    for(uint16_t j = 0; j < decoded_message->data_number; j++)
        data_set(j, data_get(j+M, message), decoded_message);

    return decoded_message;
}

Poly* make_syndrome()
{
    #ifdef DEBUG
        printf("Building syndrome array...\n");
    #endif
    Poly* synd = malloc((N+1)*sizeof(Poly));
    uint16_t i = 0;
    for(i=0; i<=N; i++)
    {
        Poly tmp = data_generate(N+1);
        data_set(i,