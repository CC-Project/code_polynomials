#ifndef CONFIG_H
    #define CONFIG_H
    #define DEBUG // If enable, debugging routines will be compiled

	// The following preprocessor code selects the architecture
	#ifdef __AVR__
        #warning AVR plateform selected
        #define BAUD_RATE 0x19      // 38400
		#define F_CPU	16000000UL  // CPU clock frequency
    #else
        #warning Windows plateform selected
        #include <inttypes.h>
        #include <stdlib.h>
	#endif

    // Hamming (7,4,3)
    #define G 0b1011
    #define N 7
    #define K 4 // Length of data words
    #define M 3 // Length of the generator polynomial G.
    #define CORR
    #define ERR_BITS 1

    // Perfect binary Golay code (23,12,7)
//    #define G 0b110001110101
//    #define N 23
//    #define K 12
//    #define M 11
//    #define CORR
//    #define ERR_BITS 2

#endif // CONFIG_H
