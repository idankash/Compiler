#ifndef EXPRESSION1_H
#define EXPRESSION1_H
#include "Token.h"
#include "Parser.h"

Types Parse_Expression1(char* idName);
int notInFollow_Expression1(eTOKENS kind);
#endif