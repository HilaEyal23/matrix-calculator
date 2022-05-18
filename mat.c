#include "mat.h"

void welcome_massage(){
    printf("Welcome to the matrix calculator!\n"
        "Enter your desired command from the following list:\n"
        "read_mat mat, list of values\n"
        "print_mat mat\n"
        "add_mat mat, mat, mat\n"
        "sub_mat mat, mat, mat\n"
        "mul_mat mat, mat, mat\n"
        "mul_scalar mat, scalar, mat\n"
        "trans_mat mat, mat \n"
        "stop\n");
}

void init_mat(mat *mat){
    int i,j;
    for(i=0; i<MAT_SIZE; i++){
        for(j=0; j<MAT_SIZE; j++){
            mat -> matrix[i][j] = 0;
        }
    }
}

void copy_mat(mat *mat1, mat *mat2){
    int i,j;
    for(i=0; i<MAT_SIZE; i++){
        for(j=0; j<MAT_SIZE; j++){
            mat2 -> matrix[i][j] = mat1 -> matrix[i][j];
        }
    }
}








void read_mat(mat *mat1 ,float values[])
{
	int i,j,k=0;
    for(i=0; i<MAT_SIZE; i++){
        for(j=0; j<MAT_SIZE; j++){
            mat1 -> matrix[i][j] = values[k];
            k++;
        }
    }	
}

void print_mat(mat *mat)
{
	int i,j;
    printf("MAT:\n");
    for(i=0; i<MAT_SIZE; i++){
        for(j=0; j<MAT_SIZE; j++){
            printf("%9.2f", mat -> matrix[i][j]);
        }
        printf("\n");
    }
}

void add_mat(mat *mat1, mat *mat2, mat *mat3)
{
	int i, j;
    mat tmp;
        for(i=0; i<MAT_SIZE; i++){
            for(j=0; j<MAT_SIZE; j++){
            tmp.matrix[i][j] = mat1 -> matrix[i][j] + mat2 -> matrix[i][j];
        }
    }
    copy_mat(&tmp,mat3);
    print_mat(mat3);
}

void sub_mat(mat *mat1, mat *mat2, mat *mat3)
{
	int i, j;
    mat tmp;
    for(i=0; i<MAT_SIZE; i++){
        for(j=0; j<MAT_SIZE; j++){
            tmp.matrix[i][j] = mat1 -> matrix[i][j] - mat2 -> matrix[i][j];
        }
    }
    copy_mat(&tmp,mat3);
    print_mat(mat3);
}

void mul_mat(mat *mat1, mat *mat2, mat *mat3)
{
	int i, j, sum = 0;
    mat tmp;
    for(i=0; i<MAT_SIZE; i++){
        for(j=0; j<MAT_SIZE; j++){
            tmp.matrix[i][j] = mat1 -> matrix[i][j] * mat2 -> matrix[i][j];
        }
    }
    copy_mat(&tmp,mat3);
    print_mat(mat3);
}

void mul_scalar(mat *mat1, double num, mat *mat2)
{
	int i, j;
    mat tmp;
    for(i=0; i<MAT_SIZE; i++){
        for(j=0; j<MAT_SIZE; j++){
            tmp.matrix[i][j] = mat1 -> matrix[i][j]*num;
        }
    }
    copy_mat(&tmp,mat2);
    print_mat(mat2);
}


void trans_mat(mat *mat1, mat *mat2)
{
	int i, j;
    mat tmp;
    for(i=0; i<MAT_SIZE; i++){
        for(j=0; j<MAT_SIZE; j++){
            tmp.matrix[i][j] = mat1 -> matrix[j][i];
        }
    }
    copy_mat(&tmp,mat2);
    print_mat(mat2);
}

void stop(void)
{
    printf("program stops");
	exit(0);
}