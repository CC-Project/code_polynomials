#include "config_polynomials.h"
#include "../lib_data/data.h"
#include "src/poly.h"
    #ifdef __AVR__
        uint16_t syndrome[N+1] PROGMEM= { {0}, {1}, {2}, {4}, {3}, {7}, {5}, {6} };
    #else
        uint16_t syndrome[N+1] = { {0}, {1}, {2}, {4}, {3}, {7}, {5}, {6} };
    #endif // __AVR__
Poly generator;
void test();

int main(int argc, char *argv[])
{
    poly_init_generator();
    make_syndrome();

    printf("Message: ");
    Poly message = data_generate(K);
    data_set(0, 1, message);
    data_set(1, 1, message);
    poly_show(message);

    printf("Coded word: ");
    Poly coded_word = poly_encode(message);
    poly_show(coded_word);
    data_set(4,1,coded_word); // Add an error
    printf("Modified codeword: ");
    poly_show(coded_word);

    Poly decoded = poly_decode(coded_word);
    printf("Decoded word: ");
    poly_show(decoded);

    data_free(decoded);
    data_free(coded_word);
    data_free(message);

    data_free(generator);

    return EXIT_SUCCESS;
}


void test()
{
    Poly m = data_generate(N);
    Poly r = poly_remainder(m);
    data_free(m);
    data_free(r);
}
