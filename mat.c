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

void init_mats(mat mats[]){
    int i, j;
    strcpy(mats[0].name, "MAT_A");
    strcpy(mats[1].name, "MAT_B");
    strcpy(mats[2].name, "MAT_C");
    strcpy(mats[3].name, "MAT_D");
    strcpy(mats[4].name, "MAT_E");
    strcpy(mats[5].name, "MAT_F");
	 for(i=0; i<MAT_SIZE; i++){
        for(j=0; j<MAT_SIZE; j++){
            mats[0].matrix[i][j] = 0;
            mats[1].matrix[i][j] = 0;
            mats[2].matrix[i][j] = 0;
            mats[3].matrix[i][j] = 0;
            mats[4].matrix[i][j] = 0;
            mats[5].matrix[i][j] = 0;
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

void read_mat(mat *mat1 ,double values[])
{
	int i,j,k=0;
    mat tmp;
    for(i=0; i<MAT_SIZE; i++){
        for(j=0; j<MAT_SIZE; j++){
            tmp.matrix[i][j] = values[k];
            k++;
        }
    }
    copy_mat(&tmp, mat1);
    print_mat(mat1);	
}

void print_mat(mat *mat)
{
	int i,j;
    printf("%s:\n", mat -> name);
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
    copy_mat(&tmp, mat3);
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
    copy_mat(&tmp, mat3);
    print_mat(mat3);
}

void mul_mat(mat *mat1, mat *mat2, mat *mat3)
{
	int i, j, k;
    double sum;
    mat tmp;
    for(i=0; i<MAT_SIZE; i++){
        for(j=0; j<MAT_SIZE; j++){
            sum = 0;
            for(k=0; k<MAT_SIZE; k++){
                sum += mat1 -> matrix[i][k] * mat2 -> matrix[k][j];
            }
            tmp.matrix[i][j] = sum;
        }
    }
    copy_mat(&tmp, mat3);
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
    copy_mat(&tmp, mat2);
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
    copy_mat(&tmp, mat2);
    print_mat(mat2);
}

void stop(void)
{
    printf("program stops\n");
	exit(0);
}