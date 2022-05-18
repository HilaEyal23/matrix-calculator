#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mat.h"

#define MAX_OPERAND_TYPE 4
#define MAX_CMD_LENGTH 30
#define MAX_INPUT_LENGTH 100
#define CMD_AMOUNT 9
#define MAT_NAME_LENTH 5

#define true 1
#define false 0
#define MAT_NAME_LEN 6

typedef enum operandType{NO_OPERAND = -1, MATRIX, SCALAR, ARRAY} operandType;
enum error{NO_ERROR, UND_CMD_NAME, EXTRANEOUS_TEXT, MULTIPLE_CON_COMMAS,ILLEGAL_COMMA, MISS_COMMA, MISS_PAR, NOT_REAL, NOT_SCALAR, UND_MAT_NAME};
enum commandIdx{READ_MAT, PRINT_MAT, ADD_MAT, SUB_MAT, MUL_MAT, MUL_SCALAR, TRANS_MAT, STOP};

typedef struct cmd{
  char name[MAX_CMD_LENGTH];
  int operandTypes[MAX_OPERAND_TYPE];
}cmd;

typedef struct recivedLine{
  int errorType;
  int cmdIDX;
  int cmdEndIDX;
  char operandsValues[MAX_OPERAND_TYPE][MAX_CMD_LENGTH];

} recivedLine;

recivedLine parseInput(char *allInput);
void printInput(char *allInput);
void initLine(recivedLine *recivedLine);
void getCmdIndex(recivedLine *recivedLine, char *allInput);
operandType getOperandType(char *operand);
int isOperandsValid(recivedLine *recivedLine);
void printError(int errorType);
void executeCommand(recivedLine *recivedLine, mat **arr);
int getFirstCommandChar(char *input);
int getCommasAmountInCommand(cmd);
void executeCommand();

#endif
