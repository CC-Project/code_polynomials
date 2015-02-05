#include "data.h"

struct Data* data_copy(struct Data* word); //Returns a copy of length N
void data_rshift(struct Data** word, uint16_t n); //The word given is assumed to be of length N.

struct Data* generator_to_poly(void);
uint8_t poly_lead(struct Data* poly);
uint16_t poly_deg(struct Data* poly); //Returns the degree of the given polynomial.
void poly_add(struct Data** x, struct Data* y); //Do x = x+y.

/*
    Computes sca * poly, where sca is 1 or 0 (scalar).
    Returns a poly of degree N.
*/
struct Data* poly_mul_sca(uint8_t sca, struct Data* poly);

/*
    Returns G times poly. (Polynomial multiplication)
    poly is assumed to be of degree K.
*/
struct Data* poly_mul(struct Data* poly);

/*
    Computes the euclidean division of poly by G. Results is: poly = q*g + r. Returns remainder r.
    The poly given is assumed to be of length N.
*/
struct Data* poly_div(struct Data* poly);

struct Data* poly_encode(struct Data* message);
struct Data* poly_decode(struct Data* codedword); //Length of codedword is N
uint8_t poly_check(struct Data* message);   //Check if given message is a codeword. Returns 0 if a codeword, something else if not.
