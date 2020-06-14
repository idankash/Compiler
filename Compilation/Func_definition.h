#ifndef FUNC_DEFINITION_H
#define FUNC_DEFINITION_H
#include "Token.h"
#include "Parser.h"

void Parse_Func_definition();
int notInFollow_Func_definition(eTOKENS kind);
int num_of_params_f(TypesNode* paramList);

#endif