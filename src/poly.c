#include "poly.h"

struct Data* data_copy(struct Data* word)
{
    uint16_t i = 0;
    Poly copy = data_generate(word->data_number);
    for(i = 0; i<word->data_number; i++)
        data_set(i, data_get(i, word), copy);

    return copy;
}



void poly_init_generator(void)
{
    uint16_t i = 0;
    generator = data_generate(M+1);
    for(i = 0; i < M + 1; i++)
        data_set(i, G&(1<<i), generator);
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



uint16_t poly_deg(Poly poly)
{
    uint16_t n = poly->data_number;
    while(n > 1 && data_get(n-1, poly) == 0) // n > 1 to work with the zero polynomial
            n--;
    return n - 1;
}



void poly_add(Poly* x, Poly y)
{
    uint16_t i = 0;
    for(i = 0; i < y->data_number; i++)
        data_set(i, data_get(i, *x) ^ data_get(i, y), *x);
}



Poly poly_remainder(Poly poly)
{
    //a = G*q + r
    uint32_t i = poly_deg(poly);
    uint16_t g = poly_deg(generator);

    Poly a = data_copy(poly);

    if(i >= g)
    {
        uint16_t j = 0;

        while(i>0 && i>= g)
        {
            for(j=0; j<=g; j++){
                data_set(i-j, data_get(i-j, a) ^ data_get(g - j, generator), a);
            }
            i = poly_deg(a);
        }
    }

    // Copy a in remainder (need a size of K)
    Poly remainder = data_generate(K);
    i = 0;

    for(i = 0; i<K; i++)
        data_set(i, data_get(i, a), remainder);
    data_free(a);

    return remainder; // Returns the couple (quotient, remainder)
}




Poly poly_encode(Poly message)
{
    uint16_t i = 0;

    // Copy the message make it of length N
    Poly poly = data_generate(N);
    for(i = 0; i<K; i++)
        data_set(i, data_get(i, message), poly);

    // Shift bits by M bits to the left
    Poly encoded_word = data_generate(poly->data_number);
    for(i = 0; i < poly->data_number; i++)
       data_set((i+M)%poly->data_number, data_get(i, poly), encoded_word);
    data_free(poly);

    // Add the remainder
    Poly tmp = poly_remainder(encoded_word);
    poly_add(&encoded_word, tmp);
    data_free(tmp);

    return encoded_word;
}



uint8_t poly_is_codeword(Poly message)
{
    uint8_t codeword = 1;
    Poly result = poly_remainder(message);

    uint16_t i = 0;
    for(i = 0; i < K; i++)
        if (data_get(i, result) != 0)
        {
            codeword = 0;
            break;
        }

    #ifdef DEBUG
    if(codeword)
        printf("No errors detected.\n");
    else
        printf("Error detected.\n");

    #endif // DEBUG
    data_free(result);
    return codeword;
}




#ifdef CORR
Poly poly_decode(Poly message)
{
    uint16_t i = 0;

    //If there was an error, locate the faulty bit
    if(!poly_is_codeword(message))
    {
        Poly res = poly_remainder(message);

        while(i < N)
        {
            if(poly_equality(syndrome[i], res)) //We located the faulty bit
            {
                #ifdef DEBUG
                    printf("Bit %d is faulty.\nCorrect codeword was: ", i);
                #endif

                //Correction
                Poly tmp = data_generate(message->data_number);
                data_set(i, 1, tmp);
                poly_add(&message, tmp);
                data_free(tmp);

                #ifdef DEBUG
                    poly_show(message);
                #endif // DEBUG

                i = N; //Exit the loop
            }
            else
                i++;
        }
    }

    //Decode the message by getting rid of the M last bits
    Poly decoded_message = data_generate(K);
    for(i = 0; i < decoded_message->data_number; i++)
        data_set(i, data_get(i+M, message), decoded_message);

    return decoded_message;
}

void make_syndrome()
{
    #ifdef DEBUG
        printf("Building syndrome array...\n");
    #endif
    syndrome = malloc((N+1)*sizeof(Poly));
    uint16_t i = 0;
    for(i=0; i<=N; i++)
    {
        Poly tmp = data_generate(N+1);
        data_set(i, 1, tmp);
        Poly div = poly_remainder(tmp);
        syndrome[i] = data_copy(div);
        #ifdef DEBUG
            data_show(syndrome[i]);
        #endif
        data_free(div);
        data_free(tmp);
    }

    #ifdef DEBUG
        printf("Syndrome array built. \n\n\n\n\n");
    #endif
}
#endif


#ifdef DEBUG
    void poly_show(struct Data* d)
    {
        uint16_t i;
        #ifdef __AVR__
            if(d == NULL)
                uart_tx_str("data == NULL\r\n");
            else
            {
                for(i = d->data_number-1; i  < d->data_number; i--)
                {
                    char str[5];
                    sprintf(str, "%d", data_get(i, d));
                    uart_tx_str(str);
                }
                uart_newline();
            }
        #else
            if(d == NULL)
                printf("\ndata == NULL\n");
            else
            {
                printf("(");
                for(i = d->data_number-1; i  < d->data_number; i--)
                    printf("%d ", data_get(i, d));
                printf(")\n\n");
            }
        #endif // __AVR__
    }
#endif
