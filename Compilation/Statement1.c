#include "Statement1.h"
#include "Expression.h"

Types Parse_Statement1(){

	Token* t = next_token();
	switch(t->kind){
		case TOKEN_ID:
		case TOKEN_INTEGER:
		case TOKEN_REAL:
				fprintf(yyout,"Rule( STATEMENT1  -> EXPRESSION )\n");
				back_token();
				return Parse_Expression();
		case TOKEN_SEMICOLON:
			fprintf(yyout,"Rule( STATEMENT1  -> epsilon )\n");
			back_token();
			return VOID;

		default:
			fprintf(yyout,"Expected token of type TOKEN_REAL_KEYWORD|TOKEN_INTEGER_KEYWORD|TOKEN_ID|TOKEN_SEMICOLON(epsilon) at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Statement1);
			return NONE;

	}
}

int notInFollow_Statement1(eTOKENS kind){
	if (kind != TOKEN_SEMICOLON)
		return 1;
	return 0;
}