#include "poly_codes.h"



int main(int argc, char *argv[])
{
    for(uint64_t i = 0; i<100000; i++)
    {
    Poly generator = generator_to_poly();
    Poly message = data_generate(K);
    data_set(0, 1, message);
    //data_set(1, 1, message);
    data_set(2, 1, message);
    //data_show(message);

    Poly coded_word = poly_encode(message);
    data_set(0,0,coded_word); //Add an error
    //data_show(coded_word);

    Poly decoded = poly_decode(coded_word);
    //data_show(decoded);

    data_free(decoded);
    data_free(coded_word);
    data_free(generator);
    data_free(message);
    //(x+1)(x^2+x+1) = X^3+X^2+X +X^2+X+1 = X^3 +1
    }
    return EXIT_SUCCESS;
}
