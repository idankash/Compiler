#include "Func_definitions1.h"
#include "Func_definition.h"

void Parse_Func_definitions1(){
	Token* t = next_token();
	switch(t->kind){
		case TOKEN_INTEGER_KEYWORD:
		case TOKEN_VOID_KEYWORD:
		case TOKEN_REAL_KEYWORD:
				fprintf(yyout,"Rule( FUNC_DEFINITIONS1  -> FUNC_DEFINITION FUNC_DEFINITIONS1 ))\n");
				back_token();
				Parse_Func_definition();
				Parse_Func_definitions1();
				break;
		case TOKEN_EOF:
			fprintf(yyout,"Rule( FUNC_DEFINITIONS1  -> epsilon))\n");
			back_token();
			break;

		default:
			fprintf(yyout,"Expected token of type TOKEN_INTEGER_KEYWORD|TOKEN_VOID_KEYWORD|TOKEN_REAL_KEYWORD|TOKEN_EOF(epsilon) at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Func_definitions1);
			break;

	}
}

int notInFollow_Func_definitions1(eTOKENS kind){
	if (kind != TOKEN_EOF)
		return 1;
	return 0;
}