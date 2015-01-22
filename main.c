#include "poly_codes.h"

int main(int argc, char *argv[])
{
    struct Data* message = data_generate(K);
    data_set(0, 1, message);
    data_set(1, 1, message);

    struct Data* coded_message = poly_encode(message);
    struct Data* decoded_message = poly_decode(coded_message);
    data_show(message); data_show(coded_message);
    printf("%d", poly_check(coded_message));

    data_free(message);
    data_free(coded_message);
    //data_free(decoded_message);

    return EXIT_SUCCESS;
}
