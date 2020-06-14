#ifndef STATEMENTS_H
#define STATEMENTS_H
#include "Token.h"
#include "Parser.h"

void Parse_Statements();
int notInFollow_Statements(eTOKENS kind);

#endif