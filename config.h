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

    //Generator polynomial
    #define G 0b1011 //Hamming (7,4,3)
    #define M 3 // Length of the generator polynomial G.
    #define N 7
    #define K N-M // Length of data words

#endif // CONFIG_H
