#define FOREVER for(;;)
#define getIndex(param) param - 'A'

#include "complex.h"

/* 
	This function valiadtes a read_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void read_comp_exec(struct complex params[], char input[]);

/* 
	This function valiadtes a print_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void print_comp_exec(struct complex params[], char input[]);

/* 
	This function valiadtes an add_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void add_comp_exec(struct complex params[], char input[]);

/* 
	This function valiadtes a sub_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void sub_comp_exec(struct complex params[], char input[]);

/* 
	This function valiadtes a mult_comp_real command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void mult_comp_real_exec(struct complex params[], char input[]);

/* 
	This function valiadtes a mult_comp_img command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void mult_comp_img_exec(struct complex params[], char input[]);

/* 
	This function valiadtes a mult_comp_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void mult_comp_comp_exec(struct complex params[], char input[]);

/* 
	This function valiadtes an abs_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void abs_comp_exec(struct complex params[], char input[]);

/* 
	This function valiadtes a stop command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void stop_exec(struct complex params[], char input[]);

/* 
	This function returns whether a given param is valid.
	parameters:
	param - the parameter to check.
	
*/
int isValidParam(char param);

/* 
	This function prints a given error message.
	parameters:
	errorMsg - the error message to print.
	
*/
void alertError(char errorMsg[]);

/*
	This function reads the line from the user, and executes the right function if it found a known
	command name. Else, it returns an error.
	parameters:
	params - the complex parameters.
*/
void executeCommand(struct complex params[]);

/*
	This function checks if a line is only whitespaces.
	parameters:
	input - the input line.
*/
int isWhiteSpaceOnly(char input[]);