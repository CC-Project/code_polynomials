#include "config.h"
#include "../lib_data/data.h"
#include "src/poly.h"

Poly generator;
Poly* syndrome;

void test();

int main(int argc, char *argv[])
{
    generator = generator_to_poly();
    syndrome = make_syndrome();

    //test();

    Poly message = data_generate(K);
    data_set(2, 1, message);
    data_show(message);

    Poly coded_word = poly_encode(message);
    data_show(coded_word);
    data_set(6,1,coded_word); // Add an error
    data_show(coded_word);

    Poly decoded = poly_decode(coded_word);
    data_show(decoded);

    data_free(decoded);
    data_free(coded_word);
    data_free(message);


    uint16_t i = 0;
    for(i=0; i<N; i++)
        data_free(syndrome[i]);

    data_free(generator);
    return EXIT_SUCCESS;
}

void test