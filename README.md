Library for error detection using polynomials
=============================================
See http://en.wikipedia.org/wiki/Polynomial_code for details.

This module implement the polynomials correcting codes. The example will be the Golay Code.

Todo
====
Use the correct amount of data in data_generate.  
Use XOR operation for poly_div.  

Notations and configuration
=========
The symbols used are 0 and 1.  
The data to transmit is composed of K characters.  
The length of the codewords is N.  
G is the generator polynomial, of length M.
