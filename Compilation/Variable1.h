#ifndef VARIABLE1_H
#define VARIABLE1_H
#include "Token.h"
#include "Parser.h"

Types Parse_Variable1(char* idName, int flagExpression);
int notInFollow_Variable1(eTOKENS kind);

#endif