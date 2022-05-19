#include "executeCmd.h"

int isValidParam(char mat_name[]){
    return ((strspn(mat_name,"MAT_") == 4 &&
     (mat_name[4] <= 'F' && 'A' <= mat_name[4]) && 
     strlen(mat_name) == MAT_NAME_LENGTH));   
}

void alartErrors(){
    fprintf(stderr,"%s\n",errorMassage);
}

void read_comp_exec(mat params[], char input[]){
    int i=0, j=0, paramIdx = 0;
    
}