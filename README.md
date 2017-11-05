# Pima CC CIS265 Week #16 Project B

(C99) Write a program that converts a complex number in cartesian coordinates to polar form. The user will enter a and b (the real and imaginary parts of the number); the program will display the values of r and theta.

This program has functions that compute the norm & argument of a complex number:

* The norm of a complex number (a + bi) is the square of its modulus. The modulus of a complex number is a measure of the length of the vector representing the complex number. The modulus of a complex number a + bi is sqrt(a^2 + b^2), written |a + bi|.

* The argument is the angle that the complex vector makes with the positive real axis in the complex plane. For a complex number a + bi, the argument is equal to arctan(b/a). The angle has a positive sense when measured in a counterclockwise direction from the positive real axis and a negative sense when measured in a clockwise direction. The principal values are greater than –pi and less than or equal to +pi.  Note: GNU GCC contains this function.


Notes:
1. Because of the different handling of complex numbers between MSVC and GNU, I decide to write the program for both.
2. Compiled with MS Visual Studio 2017 Community (v141) and eclipse GNU GCC 5.3.0, using C language options.

*Submitted in partial fulfillment of the requirements of PCC CIS-265.*

