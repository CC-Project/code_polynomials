#include "config.h"
#include "../lib_data/data.h"
#include "src/poly.h"

extern Poly* syndrome;

int main(int argc, char *argv[])
{
    Poly* syndrome = make_syndrome();

    Poly message = data_generate(K);
    data_set(0, 1, message);
    data_set(1, 1, message);
    data_set(2, 1, message);
    data_show(message);

    Poly coded_word = poly_encode(message);
    data_set(0,1,coded_word); // Add an error
    data_show(coded_word);

    Poly decoded = poly_decode(coded_word);
    data_show(decoded);

    data_free(decoded);
    data_free(coded_word);
    data_free(message);
    //(x+1)(x^2+x+1) = X^3+X^2+X +X^2+X+1 = X^3 +1

    return EXIT_SUCCESS;
}
