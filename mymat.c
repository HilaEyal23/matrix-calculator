#include "input.h"

int main(){
    mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;
    mat mats[NUM_OF_MATS];
    mats[0]=MAT_A;
    mats[1]=MAT_B;
    mats[2]=MAT_C;
    mats[3]=MAT_D;
    mats[4]=MAT_E;
    mats[5]=MAT_F;

    welcome_massage();
    init_mats(mats);
    FOREVER
        executeCmd(mats);
    return 0;
}