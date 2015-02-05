#include "poly_codes.h"

int main(int argc, char *argv[])
{
    struct Data* generator = generator_to_poly();

    struct Data* message = data_generate(N);
    data_set(0, 1, message);
    data_set(3, 1, message);
    data_show(message);

    struct Data* codeword = poly_div(message);
    data_show(codeword);

    data_free(codeword);
    data_free(generator);
    data_free(message);
    //(x+1)(x^2+x+1) = X^3+X^2+X +X^2+X+1 = X^3 +1

    /*
    struct Data* coded_message = poly_encode(message);
    struct Data* decoded_message = poly_decode(coded_message);
    data_show(message); data_show(coded_message);
    printf("%d", poly_check(coded_message));

    data_free(message);
    data_free(coded_message);
    //data_free(decoded_message);
    */
    return EXIT_SUCCESS;
}
