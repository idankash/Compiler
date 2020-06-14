#ifndef STATEMENT_H
#define STATEMENT_H
#include "Token.h"
#include "Parser.h"

void Parse_Statement();
int notInFollow_Statement(eTOKENS kind);
Types getBlockType();

#endif