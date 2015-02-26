#include "data.h"

typedef struct Data* Poly;
typedef struct Data* Polynome;

Polynome data_copy(Polynome word); //Returns a copy of length N
Polynome generator_to_poly(void);

uint8_t poly_lead(Polynome poly);
uint16_t poly_deg(Polynome poly); //Returns the degree of the given polynomial.

void poly_add(Polynome* x, Polynome y); //Do x = x+y.
void data_rshift(Polynome* word, uint16_t n); //The word given is assumed to be of length N.

/*
    Computes sca * poly, where sca is 1 or 0 (scalar).
    Returns a poly of degree N.
*/
Polynome poly_mul_sca(uint8_t sca, Polynome poly);


/*
    Returns G times poly. (Polynomial multiplication)
    poly is assumed to be of degree K.
*/
Polynome poly_mul(Polynome poly);


/*
    Computes the euclidean division of poly by G. Results is: poly = q*g + r.
    The poly given is assumed to be of length N.
    Returns a array containing the quotient and the remainder (in that order)
    The quotient is of length K.
*/
Polynome* poly_div(Polynome poly);


/*
    message is assumed to be og length K.
*/
Polynome poly_encode(Polynome message);


/*
    Check if given message is a codeword and decode it if possible.
    Returns the decoded message, or NULL is the given message was not a codeword.
    The given message is assumed to be of length N
*/
Polynome poly_decode(Polynome codedword); //Length of codedword is N
