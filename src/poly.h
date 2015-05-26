#include "../config.h"
#include "../../lib_data/data.h"

typedef struct Data* Poly;
extern Poly generator;
#ifdef CORR
    extern Poly* syndrome;
#endif




/**
 *  Returns a copy of the given data. The size is the same
**/
struct Data* data_copy(struct Data* word);




/**
 *  Init the Poly structure associated with
 *  the generator polynomial G (defined in config.h)
**/
void poly_init_generator(void);



/**
 *  Returns true if both polynomials are equals, false otherwise.
 *  Both polynomials are assumed to be of same degree.
**/
uint8_t poly_equality(Poly a, Poly b);



/**
 *  Returns the degree of the given polynomial.
**/
uint16_t poly_deg(Poly poly);



/**
 *  Adds to polynomials in F_2[X].
 *  x must have a degree greater or equal to the degree of y.
 *  The result is stored in x.
**/
void poly_add(Poly* x, Poly y); // Do x = x+y.



/**
 *  Returns the remainder of the euclidean division of poly by G.
 *  The remainder is of length K.
**/
Poly poly_remainder(Poly poly);




/**
 *  Encode message using the specified G polynomial.
 *  message is assumed to be of length K.
**/
Poly poly_encode(Poly message);


/**
 *  Check if given message if a codeword.
 *  Returns a boolean.
**/
uint8_t poly_is_codeword(Poly message);




/**
 *  If given polynomial allows to correct the data only.
**/
#ifdef CORR
    /**
     *  Returns the decoded message.
     *  The given codeword is assumed to be of length N.
    **/
    Poly poly_decode(Poly codedword);


    /**
     *  Set global variable syndrome to an array of syndrome.
     *  The syndrome is printed if DEBUG is defined.
    **/
    void make_syndrome();
#endif


#ifdef DEBUG
    // Prints out a data structure.
    void poly_show(struct Data* d);
#endif
