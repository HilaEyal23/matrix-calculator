#include "exec.h"

/* 
	This function returns whether a given param is valid.
	parameters:
	param - the parameter to check.
	
*/
int isValidParam(char param){
	return param >= 'A' && param <= 'F';
}

/* 
	This function prints a given error message.
	parameters:
	errorMsg - the error message to print.
	
*/
void alertError(char errorMsg[]){
	fprintf(stderr, "%s\n", errorMsg);
}


/* 
	This function valiadtes a read_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void read_comp_exec(struct complex params[], char input[]){	
	int i = 0, j = 0, paramIndex = 0;
	char number[MAX_LEN];
	double num1, num2;
	char param;
	num1 = num2 = 0;

	for(; isalpha((input)[i]) || (input)[i] == '_'; i++); /* skipping the command */
	
	if(input[i] == ','){
		alertError("Illegal comma"); 
		return;	
	}
	
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the parameter */
	
	if(!isValidParam(param = input[i])){
		if(input[i] == ','){ 
			alertError("Invalid comma"); 
			return;
		}
		else { 
			if(input[i + 1] == '\n' || input[i + 1] == EOF || input[i + 1] == 0) alertError("Missing parameter.");
			else alertError("Undefined complex variable.");
			return; 
		}
	}	
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the comma */
	
	if(input[i] != ',') { 
		if(input[i] == 0 || input[i] == '\n' || input[i] == EOF) alertError("Missing parameter");
		else alertError("Missing comma"); 
		return; 
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the number */
	
	while(isdigit(input[i]) || input[i] == '.' || input[i] == '-') number[j++] = input[i++]; /* getting all the digits of the number. */
	
	if(input[i] == ',' && j == 0){
		alertError("Multiple consecutive commas");
		return;
	}
	
	number[j] = '\0';
	num1 = atof(number); /* converting to a number */
	if(j == 0){ 
		alertError("Wrong parameters, second parameter should be a number."); 
		return; 
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the comma */
	
	if(input[i++] != ',') { 
		if(input[i] == 0 || input[i] == '\n' || input[i] == EOF) alertError("Missing parameter");
		else alertError("Missing comma"); 
		return; 
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the number */
	
	j = 0;
	while(isdigit(input[i]) || input[i] == '.' || input[i] == '-') number[j++] = input[i++];  /* getting all the digits of the number. */
	
	if(input[i] == ',' && j == 0){
		alertError("Multiple consecutive commas");
		return;
	}
	
	number[j] = '\0';
	num2 = atof(number); /* converting to a number */
	if(j == 0){ 
		alertError("Wrong parameters, third parameter should be a number."); 
		return; 
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the \n (in case it's valid) */
	
	if(input[i] != '\n' && input[i] != EOF && input[i] != '\0'){
		alertError("Extraneous text after command.");
		return;
	}
	
	paramIndex =  getIndex(param);
	read_comp(&params[paramIndex], num1, num2);
}

/* 
	This function valiadtes a print_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void print_comp_exec(struct complex params[], char input[]){
	int i = 0, paramIndex = 0;
	char param;

	for(; isalpha((input)[i]) || (input)[i] == '_'; i++); /* skipping the command */
	
	if(input[i] == ','){
		alertError("Illegal comma"); 
		return;	
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the parameter */
	
	if(!isValidParam(param = input[i])){
		if(input[i] == ','){ 
			alertError("Invalid comma"); 
			return;
		}
		else { 
			if(!isalpha(param) && (input[i + 1] == '\n' || input[i + 1] == EOF || input[i + 1] == 0))
				 alertError("Missing parameter.");
			else alertError("Undefined complex variable.");
			return; 
		}
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the \n (in case it's valid) */
	
	if(input[i] != '\n' && input[i] != EOF && input[i] != '\0'){
		alertError("Extraneous text after command.");
		return;
	}
	
	paramIndex = getIndex(param);
	print_comp(&params[paramIndex]);
}

/* 
	This function valiadtes an add_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void add_comp_exec(struct complex params[], char input[]){
	int i = 0, paramIndex = 0, param1Index = 0;
	char param, param1;
	struct complex res;
	
	for(; isalpha((input)[i]) || (input)[i] == '_'; i++); /* skipping the command */
	
	if(input[i] == ','){
		alertError("Illegal comma"); 
		return;	
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the parameter */
	
	if(!isValidParam(param = input[i])){
		if(input[i] == ','){ 
			alertError("Invalid comma"); 
			return;
		}
		else { 
			if(input[i + 1] == '\n' || input[i + 1] == EOF || input[i + 1] == 0) alertError("Missing parameter.");
			else alertError("Undefined complex variable.");
			return; 
		}
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the comma */
	
	if(input[i] != ',') { 
		if(input[i] == 0 || input[i] == '\n' || input[i] == EOF) alertError("Missing parameter");
		else alertError("Missing comma"); 
		return; 
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the parameter */
	
	if(!isValidParam(param1 = input[i])){
		if(input[i] == ','){ 
			alertError("Multiple consecutive commas"); 
			return;
		}
		else { 
			if(param1 == '\n' || param1 == EOF || param1 == 0) alertError("Missing parameter.");
			else alertError("Undefined complex variable.");
			return; 
		}
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the \n (in case it's valid) */
	
	if(input[i] != '\n' && input[i] != EOF && input[i] != '\0'){
		alertError("Extraneous text after command.");
		return;
	}
	
	paramIndex =  getIndex(param);
	param1Index = getIndex(param1);
	res = add_comp(&params[paramIndex], &params[param1Index]);
	print_comp(&res);
}

/* 
	This function valiadtes a sub_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void sub_comp_exec(struct complex params[], char input[]){
	int i = 0, paramIndex = 0, param1Index = 0;
	char param, param1;
	struct complex res;

	for(; isalpha((input)[i]) || (input)[i] == '_'; i++); /* skipping the command */
	
	if(input[i] == ','){
		alertError("Illegal comma"); 
		return;	
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the parameter */
	
	if(!isValidParam(param = input[i])){
		if(input[i] == ','){ 
			alertError("Invalid comma"); 
			return;
		}
		else { 
			if(input[i + 1] == '\n' || input[i + 1] == EOF || input[i + 1] == 0) alertError("Missing parameter.");
			else alertError("Undefined complex variable.");
			return; 
		}
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the comma */
	
	if(input[i] != ',') { 
		if(input[i] == 0 || input[i] == '\n' || input[i] == EOF) alertError("Missing parameter");
		else alertError("Missing comma"); 
		return; 
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the parameter */
	
	if(!isValidParam(param1 = input[i])){
		if(input[i] == ','){ 
			alertError("Multiple consecutive commas"); 
			return;
		}
		else { 
			if(param1 == '\n' || param1 == EOF || param1 == 0) alertError("Missing parameter.");
			else alertError("Undefined complex variable."); 
			return; 
		}
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the \n (in case it's valid) */
	
	if(input[i] != '\n' && input[i] != EOF && input[i] != '\0'){
		alertError("Extraneous text after command.");
		return;
	}
	
	paramIndex =  getIndex(param);
	param1Index = getIndex(param1);
	res = sub_comp(&params[paramIndex], &params[param1Index]);
	print_comp(&res);
}

/* 
	This function valiadtes a mult_comp_real command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void mult_comp_real_exec(struct complex params[], char input[]){
	int i = 0, j = 0, paramIndex = 0;
	char number[MAX_LEN];
	double num1;
	char param;
	struct complex res;

	for(; isalpha((input)[i]) || (input)[i] == '_'; i++); /* skipping the command */
	
	if(input[i] == ','){
		alertError("Illegal comma"); 
		return;	
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the parameter */
	
	if(!isValidParam(param = input[i])){
		if(input[i] == ','){ 
			alertError("Invalid comma"); 
			return;
		}
		else { 
			if(input[i + 1] == '\n' || input[i + 1] == EOF || input[i + 1] == 0) alertError("Missing parameter.");
			else alertError("Undefined complex variable.");
			return; 
		}
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the comma */
	
	if(input[i] != ',') { 
		if(input[i] == 0 || input[i] == '\n' || input[i] == EOF) alertError("Missing parameter");
		else alertError("Missing comma"); 
		return; 
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the number */
	
	while(isdigit(input[i]) || input[i] == '.' || input[i] == '-') number[j++] = input[i++]; /* getting all the digits of the number. */
	
	if(input[i] == ',' && j == 0){
		alertError("Multiple consecutive commas");
		return;
	}
	
	number[j] = '\0';
	num1 = atof(number); /* converting to a number */
	if(j == 0){ 
		alertError("Wrong parameters, second parameter should be a number."); 
		return; 
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the \n (in case it's valid) */
	
	if(input[i] != '\n' && input[i] != EOF && input[i] != '\0'){
		alertError("Extraneous text after command.");
		return;
	}
	
	paramIndex =  getIndex(param);
	res = mult_comp_real(&params[paramIndex], num1);
	print_comp(&res);
}

/* 
	This function valiadtes a mult_comp_img command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void mult_comp_img_exec(struct complex params[], char input[]){
	int i = 0, j = 0, paramIndex = 0;
	char number[MAX_LEN];
	double num1;
	char param;
	struct complex res;

	for(; isalpha((input)[i]) || (input)[i] == '_'; i++); /* skipping the command */
	
	if(input[i] == ','){
		alertError("Illegal comma"); 
		return;	
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the parameter */
	
	if(!isValidParam(param = input[i])){
		if(input[i] == ','){ 
			alertError("Invalid comma"); 
			return;
		}
		else { 
			if(input[i + 1] == '\n' || input[i + 1] == EOF || input[i + 1] == 0) alertError("Missing parameter.");
			else alertError("Undefined complex variable.");
			return; 
		}
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the comma */
	
	if(input[i] != ',') { 
		if(input[i] == 0 || input[i] == '\n' || input[i] == EOF) alertError("Missing parameter");
		else alertError("Missing comma"); 
		return; 
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the number */
	
	while(isdigit(input[i]) || input[i] == '.' || input[i] == '-') number[j++] = input[i++]; /* getting all the digits of the number. */
	
	if(input[i] == ',' && j == 0){
		alertError("Multiple consecutive commas");
		return;
	}
	
	number[j] = '\0';
	num1 = atof(number); /* converting to a number */
	if(j == 0){ 
		alertError("Wrong parameters, second parameter should be a number."); 
		return; 
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the \n (in case it's valid) */
	
	if(input[i] != '\n' && input[i] != EOF && input[i] != '\0'){
		alertError("Extraneous text after command.");
		return;
	}
	
	paramIndex =  getIndex(param);
	res = mult_comp_img(&params[paramIndex], num1);
	print_comp(&res);
}

/* 
	This function valiadtes a mult_comp_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void mult_comp_comp_exec(struct complex params[], char input[]){
	int i = 0, paramIndex = 0, param1Index = 0;
	char param, param1;
	struct complex res;

	for(; isalpha((input)[i]) || (input)[i] == '_'; i++); /* skipping the command */
	
	if(input[i] == ','){
		alertError("Illegal comma"); 
		return;	
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the parameter */
	
	if(!isValidParam(param = input[i])){
		if(input[i] == ','){ 
			alertError("Invalid comma"); 
			return;
		}
		else { 
			if(input[i + 1] == '\n' || input[i + 1] == EOF || input[i + 1] == 0) alertError("Missing parameter.");
			else alertError("Undefined complex variable.");
			return; 
		}
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the comma */
	
	if(input[i] != ',') { 
		if(input[i] == 0 || input[i] == '\n' || input[i] == EOF) alertError("Missing parameter");
		else alertError("Missing comma"); 
		return; 
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the parameter */
	
	if(!isValidParam(param1 = input[i])){
		if(input[i] == ','){ 
			alertError("Multiple consecutive commas"); 
			return;
		}
		else { 
			if(param1 == '\n' || param1 == EOF || param1 == 0) alertError("Missing parameter.");
			else alertError("Undefined complex variable."); 
			return; 
		}
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the \n (in case it's valid) */
	
	if(input[i] != '\n' && input[i] != EOF && input[i] != '\0'){
		alertError("Extraneous text after command.");
		return;
	}
	
	paramIndex =  getIndex(param);
	param1Index = getIndex(param1);
	res = mult_comp_comp(&params[paramIndex], &params[param1Index]);
	print_comp(&res);
}

/* 
	This function valiadtes an abs_comp command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void abs_comp_exec(struct complex params[], char input[]){
	int i = 0, paramIndex = 0;
	char param;
	struct complex res;

	for(; isalpha((input)[i]) || (input)[i] == '_'; i++); /* skipping the command */
	
	if(input[i] == ','){
		alertError("Illegal comma"); 
		return;	
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the parameter */
	
	if(!isValidParam(param = input[i])){
		if(input[i] == ','){ 
			alertError("Invalid comma"); 
			return;
		}
		else { 
			if(input[i + 1] == '\n' || input[i + 1] == EOF || input[i + 1] == 0) alertError("Missing parameter.");
			else alertError("Undefined complex variable.");
			return; 
		}
	}
	i++;
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the \n (in case it's valid) */
	
	if(input[i] != '\n' && input[i] != EOF && input[i] != '\0'){
		alertError("Extraneous text after command.");
		return;
	}
	
	paramIndex = getIndex(param);
	res = abs_comp(&params[paramIndex]);
	print_comp(&res);
}

/* 
	This function valiadtes a stop command, if it is valid, it executes it. Else, it returns an error.
	parameters:
	params - the complex parameters.
	input - the user input.
	
*/
void stop_exec(struct complex params[], char input[]){
	int i = 0;
	for(; isalpha((input)[i]) || (input)[i] == '_'; i++); /* skipping the command */
	
	if(input[i] == ','){
		alertError("Illegal comma"); 
		return;	
	}
	
	while(isspace(input[i]) && input[i] != '\n') i++;  /* skipping all the spaces until the \n (in case it's valid) */
	
	if(input[i] != '\n' && input[i] != EOF && input[i] != '\0'){
		alertError("Extraneous text after command.");
		return;
	}
	stop();
}