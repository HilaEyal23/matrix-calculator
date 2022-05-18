#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAT_SIZE 4
#define FOREVER for(;;)
#define OK 1
#define MAX_CMD_LEN 30
#define MAT_NAME_LEN 6
#define NUM_OF_MATS 6

typedef struct mat{
    float matrix[MAT_SIZE][MAT_SIZE];
}mat;

/*
typedef double matrix[MAT_SIZE][MAT_SIZE];

typedef struct mat{
	char name[MAT_NAME_LEN];
	matrix *matrix;
} mat;*/

void welcome_massage();

void init_mat(mat *mat);

/*
This function copies the first matrix into the second.
@param mat1 - the matrix to be copied
@param mat2 - the matrix which stores the other matrix's copy.
*/
void copy_mat(mat *mat1, mat *mat2);

/*
This function filles the given matrix with the given valuses according to the order they were written. in case there are more valuse
nedded, it takes only the first values. in case there are less values then needed, it filles the left argumants with 0.
@param mat1 - the matrix that beeing filled
@param values[] - a list of values to fill the matrix with.
*/
void read_mat(mat *mat1 ,float values[]);

/*
This function prints the given matrix ordinarly
@param mat - the matrix to be printed
*/
void print_mat(mat *mat);

/*
This function calculates the addition of two given matrix and stores the result in the third givan matrix
@param mat1 - the first matrix that takes place in the addition
@param mat2 - the secont matrix that takes pace inh the addition
@param mat3 - the matrix which stores the result
*/
void add_mat(mat *mat1, mat *mat2, mat *mat3);

/*

*/
void sub_mat(mat *mat1, mat *mat2, mat *mat3);



/*
This functions calculates the multiplication of two given matrix and saves it on the third given matrix
@param mat1 - the first matrix that takes place in the multiplication
@param mat2 - the second matrix that takes place in the multiplication
@param mat3 - the matrix which stores the result
*/
void mul_mat(mat *mat1, mat *mat2, mat *mat3);

/*
This functions calculates the multiplication of given matrix and number and stores it in the seconed given matrix.
@param mat1 - the matrix that takes place in the multiplication
@param num - the number that takes place in the multiplication
@param mat2 - the matrix which stores the result
*/
void mul_scalar(mat *mat1, double num, mat *mat2);

/*
This program transpose the first matrix and saves it in the second matrix
@param mat1 - the matrix that should be transposed
@param mat2 - the matrix which stores the result
*/
void trans_mat(mat *mat1, mat *mat2);

/*
This functions stops the program from running
*/
void stop(void);

            