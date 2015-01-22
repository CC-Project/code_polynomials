Library for error detection using polynomials
=============================================


Notations
=========
The symbols used are 0 and 1.  
BASE_L is the length of the elements in the base chosen. For instance, if set to 1, the set of words will be {0,1}. 
However, if BASE_L is set to 2, then the set of words will be {11, 10, 01, 00}. 
It must be set under 8.  
BASE_D is the number of elements in the set. 2^BASE_L = BASE_D.  
The data to transmit is composed of k characters.  
The length of the codewords is n.  
G is the generator polynomial.  
