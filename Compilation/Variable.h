#ifndef VARIABLE_H
#define VARIABLE_H
#include "Token.h"
#include "Parser.h"

TypesNode* Parse_Variable(Types attr);
int notInFollow_Variable(eTOKENS kind);
int alreadyDefined(char* idName);
SymbolTableNode* getFunc();

#endif