#include "data.h"

struct Data* poly_div(struct Data* poly); //Computes the euclidean division of poly by G. Results is: poly = q*g + r. Returns q.
struct Data* poly_encode(struct Data* message);
struct Data* poly_decode(struct Data* codeword);
uint8_t poly_check(struct Data* message);   //Check if given message is a codeword. Returns 0 if a codeword, something else if not.
