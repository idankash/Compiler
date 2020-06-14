#ifndef PROGRAM_H
#define PROGRAM_H
#include "Token.h"
#include "Parser.h"
#include "BB.h"
#include "FB.h"

void Parse_Program();
int notInFollow_Program(eTOKENS kind);

#endif