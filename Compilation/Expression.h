#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "Token.h"
#include "Parser.h"

Types Parse_Expression();
int notInFollow_Expression(eTOKENS kind);
Types checkType(Types idType, Types exType);

#endif