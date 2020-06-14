#ifndef TYPE_H
#define TYPE_H
#include "Token.h"
#include "Parser.h"

Types Parse_Type();
int notInFollow_Type(eTOKENS kind);

#endif