#include "data.h"

typedef struct Data* Poly;
extern Poly* syndrome;

Poly data_copy(Poly word); // Returns a copy of length N
Poly generator_to_poly(void);

uint8_t poly_lead(Poly poly);
uint16_t poly_deg(Poly poly); // Returns the degree of the given polynomial.

void poly_add(Poly* x, Poly y); // Do x = x+y.
void data_rshift(Poly* word, uint16_t n); // The word given is assumed to be of length N.

/*
    Computes sca * poly, where sca is 1 or 0 (scalar).
    Returns a poly of degree N.
*/
Poly poly_mul_sca(uint8_t sca, Poly poly);


/*
    Returns G times poly. (Polynomial multiplication)
    poly is assumed to be of degree K.
*/
Poly poly_mul(Poly poly);


/*
    Computes the euclidean division of poly by G. Results is: poly = q*g + r.
    The poly given is assumed to be of length N.
    Returns a array containing the quotient and the remainder (in that order)
    The quotient is of length K.
*/
Poly* poly_div(Poly poly);


/*
    message is assumed to be og length K.
*/
Poly poly_encode(Poly message);

/*
    Check if given message if a codeword
*/
uint8_t poly_is_codeword(Poly message);

/*
    Check if given message is a codeword and decode it if possible.
    Returns the decoded message, or NULL is the given message was not a codeword.
    The given message is assumed to be of length N
*/
Poly poly_decode(Poly codedword); // Length of codedword is N


/*
    Set global variable syndrome
    to an array of syndrome
*/
Poly* make_syndrome();
