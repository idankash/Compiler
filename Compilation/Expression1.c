#include "Variable1.h"
#include "Expression.h"
#include "Expression1.h"

Types Parse_Expression1(char* idName){
	Token* t = next_token();
	switch(t->kind){
		case TOKEN_MUL:
		case TOKEN_DIV:
			fprintf(yyout,"Rule( EXPRESSION1  ->ar_op EXPRESSION)\n");
			return Parse_Expression();
		default:
			fprintf(yyout,"Rule( EXPRESSION1  -> Variable1)\n");
			back_token();
			return Parse_Variable1(idName, 1);
	}
}

int notInFollow_Expression1(eTOKENS kind){
	if (kind != TOKEN_SEMICOLON)
		return 1;
	return 0;
}