#include "prase_input.h"
/*
This file parse the input and handle all the errors if it's needed
*/

/* This array contains all the commands names and arguemnts types list*/
cmd command[] = {
  {"read_mat", {MATRIX, ARRAY, NO_OPERAND}},
  {"print_mat", {MATRIX, NO_OPERAND, NO_OPERAND}},
  {"add_mat", {MATRIX, MATRIX, MATRIX}},
  {"sub_mat", {MATRIX, MATRIX, MATRIX}},
  {"mul_mat", {MATRIX, MATRIX, MATRIX}},
  {"mul_scalar", {MATRIX, SCALAR, MATRIX}},
  {"trans_mat", {MATRIX, MATRIX, NO_OPERAND}},
  {"stop", {NO_OPERAND, NO_OPERAND, NO_OPERAND}}
};

recivedLine parseInput(char *allInput){
    recivedLine recivedLine;
    int i, cmdIndex, operandIndex = 0, operandCounter = 0, targetAmountOfCommas = 0, firstCommandCharIndex;
    char lastChar = '\0';
    initLine(&recivedLine);
    firstCommandCharIndex = getFirstCommandChar(allInput);
    allInput += firstCommandCharIndex;
    getCmdIndex(&recivedLine, allInput);
    cmdIndex = recivedLine.cmdIDX;

    if(recivedLine.cmdIDX == STOP)
        return recivedLine;
    
    if(recivedLine.errorType == NO_ERROR){
        targetAmountOfCommas = getCommasAmountInCommand(command[cmdIndex]); /* */
        for(i = recivedLine.cmdEndIDX + 2; i < strlen(allInput) - 1; i++){ /* Iter over all the input charcters from the end of the command*/
            if(isdigit(allInput[i]) || isalpha(allInput[i]) || allInput[i] == '.' || allInput[i] == '-'){ 
                recivedLine.operandsValues[operandIndex][operandCounter++] = allInput[i];
            }else if(allInput[i] == ','){
                recivedLine.operandsValues[operandIndex][operandCounter] = 0;
                operandIndex++;
                operandCounter = 0;
            }
        
            if(allInput[i] == ',' && lastChar == ',' ){ /* Checks if there are multiple consecutive commas */
                recivedLine.errorType = MULTIPLE_CON_COMMAS;
                break;
            }
                lastChar = (allInput[i] != ' ') ? allInput[i] : lastChar; /* asign the lastCh variable to the last non-space charcter shown */
        }    
            
        if(operandIndex < targetAmountOfCommas){ /* Checks if there are any missing commas*/
            recivedLine.errorType = MISS_COMMA;
        }
        /*printf("lastCh:(%c)\n", lastCh);*/
        if(!isdigit(lastChar) &&  !isalpha(lastChar)){ /* chckes if the last charcter is not a digit or a charcter */
            recivedLine.errorType = EXTRANEOUS_TEXT; /* Extra text after the operands */
        }
    }
    recivedLine.operandsValues[operandIndex][operandCounter] = 0;
    return recivedLine;
}

void getCmdIndex(recivedLine *recivedLine, char *allInput){
    int i, j, isFound = false;

    for(i=0; (i<CMD_AMOUNT && !isFound); i++){
        for(j=0;j < strlen(allInput); j++){
            if(allInput[j] != command[i].name[j]){
                break;
            }
                
            if(j == strlen(command[i].name)-1) {/*returns true iff command was found*/
                if(allInput[j+1] == ',')
                    recivedLine -> errorType = ILLEGAL_COMMA;
                else if(allInput[j+1] == ' ' || i == STOP){
                    recivedLine -> errorType = NO_ERROR;
                    recivedLine -> cmdIDX = i;
                    recivedLine -> cmdEndIDX = j;
                }
                isFound = true; 
            } 
               
        }
    }
    if(!isFound)
        recivedLine-> errorType = UND_CMD_NAME;
}

int getOperandType(char *operand){
    int resultOperand = NO_OPERAND;
    double dOperand;
    if(sscanf(operand, "%if", &dOperand) == 1)
        resultOperand = SCALAR;
    else if(strspn(operand,"MAT_") == 4 && (operand[4] <= 'F' && 'A' <= operand[4]) && strlen(operand) == MAT_NAME_LEN ){
            resultOperand == MATRIX;
    }
    return resultOperand;
}

int isOperandsValid(recivedLine *recivedLine){
    int result = true, i;
    for(i=0; i<MAX_OPERAND_TYPE; i++){
        if(getOperandType(recivedLine -> operandsValues[i] != command[recivedLine->cmdIDX].operandTypes[i])){
            recivedLine->errorType = 7 + command[recivedLine->cmdIDX].operandTypes[i]; /* The error is 7 + the target operand in the enum we created */
            result = false;
            break;
        }
    }
    return result;
}

void printError(int errorType){
  switch(errorType){
    case UND_CMD_NAME:
        printf("Undefined command name\n");
        break;
    case EXTRANEOUS_TEXT:
        printf("Extraneous text after end of command\n");
        break;
    case MULTIPLE_CON_COMMAS:
        printf("Multiple consecutive commas\n");
        break;
    case ILLEGAL_COMMA:
        printf("Illegal comma\n");
        break;
    case MISS_COMMA:
        printf("Missing comma\n");
        break;
    case MISS_PAR:
        printf("Missing argumant\n");
        break;
    case NOT_REAL:
        printf("Argument is not a real number\n");
        break;
    case NOT_SCALAR:
        printf("Argument is not a scalar");
        break;
    case UND_MAT_NAME:
        printf("Undefined marix name\n");
        break;
  }
}

/*to be fixed*/
void executeCommand(recivedLine *recivedLine, mat **arr){
  float vals[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  float scalar;
  mat *mat1, *mat2, *mat3;
  
  if(isOperandsValid(recivedLine)){
    mat1 = arr[recivedLine->operandsValues[0][0] - 'A'];
    switch (recivedLine->cmdIDX){
        case READ_MAT:
            vals[16] = atof(recivedLine->operandsValues[1]); 
            read_mat(&mat1, vals);
            break;
        case PRINT_MAT:
            print_mat(&mat1);
            break;
        case ADD_MAT:
            mat2 = arr[recivedLine->operandsValues[1][0] - 'A'];
            mat3 = arr[recivedLine->operandsValues[2][0] - 'A']; 
            add_mat(&mat1, &mat2, &mat3);
            break;
        case SUB_MAT:
            mat2 = arr[recivedLine->operandsValues[1][0] - 'A'];
            mat3 = arr[recivedLine->operandsValues[2][0] - 'A'];            
            sub_mat(&mat1, &mat2, &mat3);
            break;
        case MUL_MAT:
            mat2 = arr[recivedLine->operandsValues[1][0] - 'A'];
            mat3 = arr[recivedLine->operandsValues[2][0] - 'A'];             
            mul_mat(&mat1, &mat2, &mat3);
            break;
        case MUL_SCALAR:
            scalar = atof(recivedLine->operandsValues[2]);
            mat2 = arr[recivedLine->operandsValues[1][0] - 'A']; 
            mul_scalar(&mat1, scalar, &mat2);
            break;
        case TRANS_MAT:
            mat2 = arr[recivedLine->operandsValues[1][0] - 'A'];
            mat3 = arr[recivedLine->operandsValues[2][0] - 'A']; 
            trans_mat(&mat1, &mat2);
            break;
        case STOP:
            break;
        
    }

  }
}

int getCommasAmountInCommand(cmd command){
    int i, cnt = 0;
    for(i=0; i<MAX_OPERAND_TYPE; i++){
        if(command.operandTypes[i] != NO_OPERAND)
            cnt++;
    }
    return cnt-1;
}

void initLine(recivedLine *recivedLine){
    int i;
    recivedLine -> errorType = NO_ERROR;
    for(i=0; i<MAX_CMD_LENGTH; i++){
        recivedLine -> operandsValues[0][i] = 0;
        recivedLine -> operandsValues[1][i] = 0;
        recivedLine -> operandsValues[2][i] = 0;
        recivedLine -> operandsValues[3][i] = 0;

    }
}

int getFirstCommandChar(char *input){
    int cnt = 0, i = 0;
    int strLen = strlen(input);
    while(i<strLen){
        if(input[i] != ' ' && input[i] != '/t')
            break;
        i++;
        cnt++;    
    }
    return cnt;
}

void executeCommand(){
 //to be fixed
}
