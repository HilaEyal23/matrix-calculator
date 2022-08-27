#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mat.h"

#define MAX_OPERAND_TYPE 3
#define MAX_CMD_LENGTH 30
#define MAX_INPUT_LENGTH 100
#define CMD_AMOUNT 9
#define MAT_NAME_LENTH 5
#define MAT_NAME_LEN 6
#define MAX_NUM_OF_OPERANDS 3
#define TAB '\t'

#define true 1
#define false 0
#define NOT_FOUND -1
#define LAST_CHAR '\0'
#define DEFAULT_VAL '0'

typedef enum operandType{NO_OPERAND = -1, MATRIX, SCALAR, LIST} operandType;
enum error{NO_ERROR, UND_CMD_NAME, EXTRANEOUS_TEXT, MULTIPLE_CON_COMMAS,ILLEGAL_COMMA, MISS_COMMA, MISS_PAR, UND_MAT_NAME, NOT_SCALAR, NOT_LIST};
enum commandIdx{READ_MAT, PRINT_MAT, ADD_MAT, SUB_MAT, MUL_MAT, MUL_SCALAR, TRANS_MAT, STOP};

typedef struct cmd{
  char name[MAX_CMD_LENGTH];
  int operandTypes[MAX_OPERAND_TYPE];
} cmd;

typedef struct recivedLine{
  int errorType;
  int cmdIDX;
  char operandsValues[MAX_OPERAND_TYPE][MAX_NUM_OF_OPERANDS];
  char line[MAX_INPUT_LENGTH];
  int numOfCommas;
  int numOfOpernds;
  double vals[MAT_SIZE * MAT_SIZE];

} recivedLine;

void executeCmd(mat mats[]);
void getInput(recivedLine *recivedLine);
void parseInput(recivedLine *recivedLine, mat mats[]);
void initLine(recivedLine *recivedLine);
void printCurrState(recivedLine *recivedLine);
void getCmdIDX(recivedLine *recivedLine);
void printError(int errorType);
int isNumber(char s[]);
int getExpectedCommasAmount(cmd command);
int getExpectedOperandsAmount(cmd command);
void skipEmpty(recivedLine *recivedLine);
void executeCommand(recivedLine *recivedLine, mat mats[]);
void getMatIDX(recivedLine *recivedLine, mat mat[]);
void getScalar(recivedLine *recivedLine);
void getList(recivedLine *recivedLine);
void removeEmpty(char s[]);
void getOperands(recivedLine *recivedLine, mat mats[]);

static cmd command[] = {
  {"read_mat", {MATRIX, LIST, NO_OPERAND}},
  {"print_mat", {MATRIX, NO_OPERAND, NO_OPERAND}},
  {"add_mat", {MATRIX, MATRIX, MATRIX}},
  {"sub_mat", {MATRIX, MATRIX, MATRIX}},
  {"mul_mat", {MATRIX, MATRIX, MATRIX}},
  {"mul_scalar", {MATRIX, SCALAR, MATRIX}},
  {"trans_mat", {MATRIX, MATRIX, NO_OPERAND}},
  {"stop", {NO_OPERAND, NO_OPERAND, NO_OPERAND}}
};


#endif
