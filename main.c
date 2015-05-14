#include "config.h"
#include "../lib_data/data.h"
#include "src/poly.h"

Poly generator;
Poly* syndrome;

int main(int argc, char *argv[])
{
    syndrome = make_syndrome();
    generator = generator_to_poly();
    Poly message = data_generate(K);
    data_set(0, 1, message);
    data_show(message);

    Poly coded_word = poly_encode(message);
    data_set(3,0,coded_word); // Add an error
    data_show(coded_word);

    Poly decoded = poly_decode(coded_word);
    data_show(decoded);

    data_free(decoded);
    data_free(coded_word);
    data_free(message);

    uint16_t i = 0;
    for(i=0; i<N; i++)
        data_free(syndrome[i]);

    data_free(message);
    data_free(generator);
    return EXIT_SUCCESS;
}
