#include "input.h"

/*
this function activates the needed functions in order to parse the input, check errors and exectue it
*/
void executeCmd(mat mats[]){
    recivedLine recivedLine;
    initLine(&recivedLine);
    getInput(&recivedLine);
    parseInput(&recivedLine, mats);
    checkErrors(&recivedLine);
    if(recivedLine.errorType != NO_ERROR){
        printError(recivedLine.errorType);
        return;
    }
    executeCommand(&recivedLine, mats);
}

/*
this function initializes the valuse of the recivedLine according to it's struct
*/
void initLine(recivedLine *recivedLine){
    int i;
    recivedLine -> errorType = NO_ERROR;
    recivedLine -> cmdIDX = NOT_FOUND; 
    recivedLine -> numOfCommas = 0;
    recivedLine -> numOfOpernds = 0;
    for(i=0; i<MAX_CMD_LENGTH; i++){
        recivedLine -> operandsValues[0][i] = 0;
        recivedLine -> operandsValues[1][i] = 0;
        recivedLine -> operandsValues[2][i] = 0;
        recivedLine -> operandsValues[3][i] = 0;
    }
    for(i=0; i<MAT_SIZE * MAT_SIZE;i++){
       recivedLine->vals[i] = 0;
    }
}

/*
this function reads the input and stores it in the recivedLine variable. 
in case of EOF it addes "stop".
*/
void getInput(recivedLine *recivedLine){
    printf("\nPlease enter commands: \n");
    fgets(recivedLine -> line, MAX_INPUT_LENGTH, stdin);

    recivedLine -> line[strcspn(recivedLine -> line, "\n")] = 0; /* replace the \n with a null terminator */
    
    if(recivedLine->line[0] == EOF)
        stop();

    printf("The line you entered:\n%s\n", recivedLine -> line);
}

/*
this function activates the needed functions in order to get the command and it's params.
*/
void parseInput(recivedLine *recivedLine ,mat mats[]){
    getCmdIDX(recivedLine);
    getOperands(recivedLine, mats);
    return;
}

/*
this function checks the given cmd in the recivedLine. in case the cmd was found, it updates it's 
IDX in the recivedLine struct. otherwise, it updates the errorType to Undefined command name.
at the end, the function removes the command from the line. 
*/
void getCmdIDX(recivedLine *recivedLine){
    int i, j, isFound = false;
    skipEmpty(recivedLine);

    for(i=0; (i<CMD_AMOUNT && !isFound); i++){
        for(j=0;j < strlen(recivedLine -> line); j++){
            if((recivedLine -> line)[j] != command[i].name[j]){
                break;
            }
                
            if(j == strlen(command[i].name)-1) {/*returns true iff command was found*/
                if((recivedLine -> line)[j+1] == ',')
                    recivedLine -> errorType = ILLEGAL_COMMA;
                else if((recivedLine -> line)[j+1] == ' ' || i == STOP){
                    recivedLine -> errorType = NO_ERROR;
                    recivedLine -> cmdIDX = i;
                    memmove(recivedLine->line, recivedLine->line + 1+j , strlen(recivedLine->line)); 
                }
                isFound = true; 
            }   
        }
    }
    if(!isFound)
        recivedLine-> errorType = UND_CMD_NAME;
}

/*
this function stars by removing all the spaces. then, it activates the functions the needed in 
order to get the params of the given command.
*/
void getOperands(recivedLine *recivedLine, mat mats[]){
    int i;
    removeEmpty(recivedLine->line);
    for(i=0; i<MAX_OPERAND_TYPE; i++){
        switch (command[recivedLine->cmdIDX].operandTypes[i])
        {
        case MATRIX:
            getMatIDX(recivedLine, mats);
            break;
        case SCALAR:
            getScalar(recivedLine);
            break;
        case LIST:
            getList(recivedLine);  
            break;
        case NO_OPERAND:
            break;  
        }
    }
}

/*
this function checks the given matrix name in the recivedLine. in case the mat was found, it 
updates it's IDX in the recivedLine struct. otherwise, it updates the errorType to Undefined 
matrix name. at the end, the function removes the matrix from the line. 
*/
void getMatIDX(recivedLine *recivedLine, mat mats[]){
    int i, isFound = false;
    const char s[2] = ",";
    char *token;
    char str[MAX_INPUT_LENGTH] = {0};

    strcpy(str,recivedLine->line);
    if(str == NULL){
        recivedLine->errorType = MISS_PAR;
        return;
    }
    token = strtok(str, s);
    if(recivedLine->line[strlen(token)] == ','){
        recivedLine->numOfCommas++;
    }
    memmove(recivedLine->line, recivedLine->line + strlen(token)+1, strlen(recivedLine->line)); 

    for(i=0; i<NUM_OF_MATS && !isFound && token != NULL; i++){
        if(!strcmp(token, mats[i].name)){
            recivedLine->operandsValues[0][recivedLine->numOfOpernds] = i;
            recivedLine->numOfOpernds++;
            isFound = true;
            break;
        }
    }
    if(!isFound)
        recivedLine -> errorType = UND_MAT_NAME;
}

/*
this function checks the given scalar in the recivedLine. in case the scalar is valid, it 
updates it's value in the recivedLine struct. otherwise, it updates the errorType to non scalar.
at the end, the function removes the scalar from the line. 
*/
void getScalar(recivedLine *recivedLine){
    int isFound = false;
    const char s[2] = ",";
    char *token ,*p; 
    char str[MAX_INPUT_LENGTH] = {0};

    strcpy(str,recivedLine->line);
    token = strtok(str, s);
    if(recivedLine->line[strlen(token)] == ','){
        recivedLine->numOfCommas++;
    }
    memmove(recivedLine->line, recivedLine->line + 2, strlen(recivedLine->line));
    if(isNumber(token)){
        recivedLine->operandsValues[1][1] = strtod(token,&p);
        recivedLine->numOfOpernds++;
        isFound = true;
    }
    if(!isFound)
        recivedLine->errorType = NOT_SCALAR;
}

/*
this function checks the given values (which supposed to fill the given matrix) recivedLine. 
in case they're valid, it updates their value in the recivedLine struct. otherwise, it updates 
the errorType to not list. at the end, the function removes the values from the line. 
*/ 
void getList(recivedLine *recivedLine){
    int i = 0, updatedNumOfOperands = false;
    char *token, *p;
    char s[2] = ",";
    char str[MAX_INPUT_LENGTH];

    strcpy(str,recivedLine->line);
    token = strtok(str, s);
    recivedLine->numOfOpernds++;
    while(token != NULL && i<MAT_SIZE*MAT_SIZE) {
        if(!isNumber(token)){
            recivedLine -> errorType = NOT_LIST;
		break;
        }
            
        recivedLine -> vals[i] = strtod(token, &p);
        i++;
        token = strtok(NULL, s);
    }
}

/*
this function checks the error status of the recivedLine and updates it in case its needed. 
*/
void checkErrors(recivedLine *recivedLine){
    if(recivedLine -> errorType == UND_CMD_NAME)
        return;

    if(recivedLine -> errorType == NOT_SCALAR)
        return;

    if(recivedLine -> errorType == UND_MAT_NAME)
        return; 
    
    if(recivedLine->numOfOpernds < getExpectedOperandsAmount(command[recivedLine->cmdIDX])){
        recivedLine -> errorType = MISS_PAR;
        return;
    }

    if(recivedLine->numOfCommas < getExpectedCommasAmount(command[recivedLine->cmdIDX])){
        recivedLine -> errorType = MISS_COMMA;
        return;
    }

    if(recivedLine->numOfCommas > getExpectedCommasAmount(command[recivedLine->cmdIDX])){
        recivedLine -> errorType = ILLEGAL_COMMA;
        return;
    }
    
    if(recivedLine->numOfOpernds > getExpectedOperandsAmount(command[recivedLine->cmdIDX])){
        recivedLine -> errorType = EXTRANEOUS_TEXT;
        return;
    }

}

/*
this function prints the error massage according to the errorType of the recivedLine.
*/
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
    case NOT_LIST:
        printf("Argument is not a list of valid values\n");
        break;
    case NOT_SCALAR:
        printf("Argument is not a scalar");
        break;
    case UND_MAT_NAME:
        printf("Undefined marix name\n");
        break;
  }
}

/*
this function transfers the params to the cmd that was found so it will be executed.
*/
void executeCommand(recivedLine *recivedLine, mat mats[]){
  double scalar;
  mat *mat1, *mat2, *mat3;
  
    mat1 = &mats[recivedLine -> operandsValues[0][0]];
    switch (recivedLine -> cmdIDX){
        case READ_MAT:
            read_mat(mat1, recivedLine->vals);
            break;
        case PRINT_MAT:
            print_mat(mat1);
            break;
        case ADD_MAT:
            mat2 = &mats[recivedLine -> operandsValues[0][1]];
            mat3 = &mats[recivedLine -> operandsValues[0][2]];
            add_mat(mat1, mat2, mat3);
            break;
        case SUB_MAT:
            mat2 = &mats[recivedLine -> operandsValues[0][1]];
            mat3 = &mats[recivedLine -> operandsValues[0][2]];
            sub_mat(mat1, mat2, mat3);
            break;
        case MUL_MAT:
            mat2 = &mats[recivedLine -> operandsValues[0][1]];
            mat3 = &mats[recivedLine -> operandsValues[0][2]];
            mul_mat(mat1, mat2, mat3);
            break;
        case MUL_SCALAR:
            scalar = recivedLine -> operandsValues[1][1];
            mat2 = &mats[recivedLine -> operandsValues[0][2]];
            mul_scalar(mat1, scalar, mat2);
            break;
        case TRANS_MAT:
            mat2 = &mats[recivedLine -> operandsValues[0][1]];
            trans_mat(mat1, mat2);
            break;
        case STOP:
            stop();
            break;    
  }
}


/*Auxiliary functions*/

/*
this function check if the given number is number.
*/
int isNumber(char s[]){
    #define isDig(c) ()
    int i, period =0;
    for(i=0; s[i]; i++){
        if(s[i] == '.'){
            if(period)
                return false;
            period = 1;    
        }
        else if(s[i]<'0' && s[i]>'9'){
                if( i!=0 || s[i] != '-')
                    return false;
        }
    }
    return true;
}

/*
this function updates the recivedLine to non-spaced line
*/
void removeEmpty(char s[]){
    char s2[MAX_INPUT_LENGTH] = {0};
    int i, j;
    char empty = ' ';
    for(i=0, j=0; j<strlen(s); j++){
        if(s[j] != empty){
            s2[i] = s[j];
		i++;
        }
    }
    strcpy(s,s2);
}

/*
this function removes the spaces in the begining of a given line
*/
void skipEmpty(recivedLine *recivedLine){
    int cnt = 0, i = 0;
    int strLen = strlen(recivedLine -> line);
    while(i<strLen){
        if(recivedLine -> line[i] != ' ' && recivedLine -> line[i] != TAB)
            break;
        i++;
        cnt++;    
    }
    memmove(recivedLine->line, recivedLine->line + cnt, strlen(recivedLine->line)); 
}

/*
this function removes the comma in the begining of a line
*/
void skipComma(recivedLine *recivedLine){
    int cnt = 0, i = 0;
    int strLen = strlen(recivedLine -> line);
    while(i<strLen){
        if(recivedLine -> line[i] != ' ' && recivedLine -> line[i] != TAB)
            break;
        i++;
        cnt++;    
    }
    strcpy((recivedLine -> line), (recivedLine -> line[cnt]));
    (recivedLine -> numOfCommas)++;
}

/*
this function prints the recivedLine current status according to its struct.
*/
void printCurrState(recivedLine *recivedLine){
    printf("Current state is:\n");
    printf("line: %s\n",recivedLine -> line);
    printf("errorType: %d\n",recivedLine -> errorType);
    printf("cmdIDX: %d\n",recivedLine -> cmdIDX);
    printf("commas: %d\n",recivedLine -> numOfCommas);    
}

/*
this function countes the expected amount of commat in the recivedLine (based on the operand
only, doesn't include the commas in the value's list in read_mat function).
*/
int getExpectedCommasAmount(cmd command){
  int i, counter = 0;
  if (!strcmp(command.name,"stop"))
    return 0;
  for(i = 0; i < MAX_OPERAND_TYPE; i++){
    if(command.operandTypes[i] != NO_OPERAND)
      counter++;
  }
  
  return counter - 1;
}

/*
this function countes the expected amount of operands in the recivedLine according to the given 
command.
*/
int getExpectedOperandsAmount(cmd command){
  int i, counter = 0;
  for(i = 0; i < MAX_OPERAND_TYPE; i++){
    if(command.operandTypes[i] != NO_OPERAND)
      counter++;
  }
  return counter;
}
