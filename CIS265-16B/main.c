/*************************************************************************
* Title: (CIS265_16B) Complex Number Cartesian/Polar Converter
* File: main.c
* Author: James Eli
* Date: 9/24/2017
*
* (C99) Write a program that converts a complex number in Cartesian
* coordinates to polar form. The user will enter a and b (the real and
* imaginary parts of the number); the program will display the values of
* r and theta.
*
* Notes:
*  (1) Because of the different handling of complex numbers between MSVC 
*      and GNU, I decide to write the program for both compilers.
*  (2) Compiled with MS Visual Studio 2017 Community (v141) and eclipse
*      GNU GCC 5.3.0, using C language options.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   09/24/2017: Initial release. JME
*************************************************************************/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _USE_MATH_DEFINES // Allows inclusion of M_PI definition.
#include <math.h>
#include <complex.h>
#include <fenv.h>

#define MIN_AMOUNT             -9999.99 // Min input value (double).
#define MAX_AMOUNT             9999.99  // Max input value (double).
#define MAXIMUM_INPUT_ATTEMPTS 3        // Max acceptable attempts before aborting.

#ifdef __GNUC__
#define COMPLEX double complex // GNU C version of complex number.

#elif _MSC_VER
#define COMPLEX _Dcomplex      // MSVC version of complex number.
#define carg cargument         // MSVC has no carg() function, however GNU GCC does.
#define sscanf sscanf_s        // Use MSVC secure version of sscanf.
#endif

// Convert radians to degrees.
#define degrees(r) (r * (180. / M_PI)) 

/*
* The norm of a complex number (a + bi) is the square of its modulus. The modulus of 
* a complex number is a measure of the length of the vector representing the complex 
* number. The modulus of a complex number a + bi is sqrt(a^2 + b^2), written |a + bi|.
*/
double cnorm(COMPLEX z) 
{ 
	// Catch all floating point exceptions.
	feclearexcept(FE_ALL_EXCEPT);
	
	// Calculate rho.
	double n = sqrt(creal(z) * creal(z) + cimag(z) * cimag(z));
	
	// Check fp exceptions.
	int fpeRaised = fetestexcept(FE_ALL_EXCEPT);
	if (fpeRaised == FE_UNDERFLOW || fpeRaised == FE_INVALID) 
	{
		fputs("Fatal math error occured.\n", stderr);
		exit(EXIT_FAILURE);
	}
	feclearexcept(FE_ALL_EXCEPT);
	
	// Force result to be double.
	return (double)n; 
}

/*
 * The argument is the angle that the complex vector makes with the positive real axis in the 
 * complex plane. For a complex number a + bi, the argument is equal to arctan(b/a). The angle 
 * has a positive sense when measured in a counterclockwise direction from the positive real 
 * axis and a negative sense when measured in a clockwise direction. The principal values are 
 * greater than –pi and less than or equal to +pi.  Note: GNU GCC contains this function.
 */
double cargument(COMPLEX z) 
{
	// Catch all floating point exceptions.
	feclearexcept(FE_ALL_EXCEPT);

	// Calculate theta.
	double arg = atan(cimag(z) / creal(z));
	
	// Check fp exceptions.
	int fpeRaised = fetestexcept(FE_ALL_EXCEPT);
	if (fpeRaised == FE_DIVBYZERO || fpeRaised == FE_INVALID) 
	{
		fputs("Fatal math error (divide by zero?).\n", stderr);
		exit(EXIT_FAILURE);
	}
	feclearexcept(FE_ALL_EXCEPT);

	// Force result to be double.
	return (double)arg;
}

// Input floating point number.
bool inputFloat(const char *prompt, double *value) 
{
	int attempts = MAXIMUM_INPUT_ATTEMPTS; // Input attempt counter.
	bool retVal = false;                   // Success/fail flag (assume fail).

	// Assert attempts valid non-zero, positive number.
	assert(attempts > 0); 

	// Attempt only so many inputs.
	while (attempts--) 
	{
		char input[9]; // Holds user input as string.
		double d;      // Temporary holds user input (double).
											   
		// Prompt and grab user input.
		fputs(prompt, stdout);
		if (!fgets(input, sizeof input, stdin)) 
		{
			fputs("\nFatal program error!\n", stderr);
			exit(EXIT_FAILURE);
		}
		else if (!strchr(input, '\n')) 
		{
			// input too long, eat remainder.
			while (fgets(input, sizeof input, stdin) && !strchr(input, '\n'))
				; // Empty body.
		
			fputs("Too many characters input.\n", stdout);
		}
		else 
		{
			// Catch special case of null input.
			if (strlen(input) <= 1)
				continue;

			// Attempt to convert from string to float, and validate.
			if (sscanf(input, "%lf", &d)) 
			{
				if (d >= MIN_AMOUNT && d <= MAX_AMOUNT) 
				{
					*value = d;
					retVal = true;
					// Exit.
					break; 
				}
				else
				{
					fprintf(stdout, "Value entered is outside allowable range (%0.2f - %0.2f)\n", MIN_AMOUNT, MAX_AMOUNT);
				}
			}
			else
			{
				fputs("Invalid input.\n", stdout);
			}
		}
	}
	
	return retVal;
}

int main(void) 
{
	COMPLEX z;            // Complex number.
	double real, imagine; // Holds user input used to define complex number (z).

	// Required to make eclipse console output work properly.
	setvbuf(stdout, NULL, _IONBF, 0);
	fflush(stdout);

	fputs("This program converts a complex number from cartesian to polar form.\n", stdout);
	fputs("A cartesian complex number has the form of (a + bi).\n", stdout);

	if (inputFloat("Enter real part (a): ", &real) && inputFloat("Enter imaginary part (b): ", &imagine)) 
	{

#ifdef __GNUC__
		z = real + imagine * I;
#elif _MSC_VER
		z = _DCOMPLEX_(real, imagine);
#endif
		
		// Display results.
		fprintf(stdout, "Polar form of (%g + %gi) = ", real, imagine);
		fprintf(stdout, "%.2f (theta-degrees) + %.2f (r)\n\n", degrees(carg(z)), cnorm(z) );
	}
}
