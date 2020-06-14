#ifndef BLOCK_H
#define BLOCK_H
#include "Token.h"
#include "Parser.h"
#include "BB.h"
#include "FB.h"

void Parse_Block();
int notInFollow_Block(eTOKENS kind);
SymbolTableNode* getFunc_b();

#endif