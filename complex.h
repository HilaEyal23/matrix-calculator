#define MAX_LEN 81
#define NUM_OF_PARAMS 6
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


typedef struct complex{
	double re, im;
} complex;

/* 
   This function reads values into a complex number 
   parameters: 
   param - the parameter to insert it to.
   re - the real value to insert.
   im - the imaginary value to insert.
*/
void read_comp(complex *param, double re, double im);

/* 
   This function prints a complex number 
   parameters: 
   param - the parameter to print.
*/
void print_comp(complex *param);

/* 
   This function adds 2 complex numbers.
   parameters: 
   param - first operand.
   param1 - second operand.
*/
struct complex add_comp(complex *param, complex *param1);

/* 
   This function substracts 2 complex numbers.
   parameters: 
   param - first operand.
   param1 - second operand.
*/
struct complex sub_comp(complex *param, complex *param1);

/* 
   This function multiplies a complex number by a real value.
   parameters: 
   param - the complex number.
   re - the real value.
*/
struct complex mult_comp_real(complex *param, double re);

/* 
   This function multiplies a complex number by an image value.
   parameters: 
   param - the complex number.
   re - the real value.
*/
struct complex mult_comp_img(complex *param, double im);

/* 
   This function multiplies a complex number by another complex number.
   parameters: 
   param - first complex number.
   param1 - second complex number.
*/
struct complex mult_comp_comp(complex *param, complex *param1);

/* 
   This function returns the absolute value of a complex number.
   parameters: 
   param - the complex number.
*/
struct complex abs_comp(complex *param);

/*
   This function stops the execution of the program.
*/
void stop();




