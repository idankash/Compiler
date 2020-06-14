#include "Type.h"

Types Parse_Type(){
	Token* t = next_token();
	switch(t->kind){
		case TOKEN_REAL_KEYWORD:
			fprintf(yyout,"Rule( TYPE  -> real)\n");
			return REAL;

		case TOKEN_INTEGER_KEYWORD:
			fprintf(yyout,"Rule( TYPE  -> integer)\n");
			return INTEGER;

		default:
			fprintf(yyout,"Expected token of type TOKEN_REAL_KEYWORD|TOKEN_INTEGER_KEYWORD at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Type);
			break;

	}
}

int notInFollow_Type(eTOKENS kind){
	if (kind != TOKEN_PARENTHESES_CLOSE && kind != TOKEN_SEMICOLON && kind != TOKEN_ID)
		return 1;
	return 0;
}