#ifndef STATEMENT2_H
#define STATEMENT2_H
#include "Token.h"
#include "Parser.h"

void Parse_Statement2(char* idName);
int notInFollow_Statement2(eTOKENS kind);
int num_of_params(TypesNode* paramList);
int compareList(TypesNode* l1, TypesNode* l2);

#endif