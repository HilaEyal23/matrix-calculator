#include "mat.h"

int main(){
    int i;
    mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;
    mat mats[NUM_OF_MATS];
    mats[0]=MAT_A;
    mats[1]=MAT_B;
    mats[2]=MAT_C;
    mats[3]=MAT_D;
    mats[4]=MAT_E;
    mats[5]=MAT_F;

    welcome_massage();
    for(i=0; i<NUM_OF_MATS; i++){
        init_mat(&mats[i]);
    }
    for(i=0; i<NUM_OF_MATS; i++){
        print_mat(&mats[i]);
    }
float val[16] = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6};
read_mat(&mats[1],val);
print_mat(&mats[1]);

float val2[16] = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
read_mat(&mats[2],val2);
print_mat(&mats[2]);

add_mat(&mats[1], &mats[2], &mats[3]);
sub_mat(&mats[1], &mats[2], &mats[3]);
mul_scalar(&mats[2], 2, &mats[3]);

    /* FOREVER */
    /*     executeCommand(); */
    return 0;

}