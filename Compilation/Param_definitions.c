#include "Param_definitions.h"
#include "Var_definitions.h"

TypesNode* Parse_Param_definitions(){
	Token* t = next_token();
	switch(t->kind){
		case TOKEN_INTEGER_KEYWORD:
		case TOKEN_REAL_KEYWORD:
				fprintf(yyout,"Rule( PARAM_DEFINITIONS  -> VAR_DEFINITIONS))\n");
				back_token();
				return Parse_Var_definitions();

		case TOKEN_PARENTHESES_CLOSE:
			fprintf(yyout,"Rule( PARAM_DEFINITIONS  -> epsilon))\n");
			back_token();
			return NULL;

		default:
			fprintf(yyout,"Expected token of type TOKEN_INTEGER_KEYWORD|TOKEN_REAL_KEYWORD|TOKEN_PARENTHESES_CLOSE(epsilon) at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Param_definitions);
			return NULL;

	}
}

int notInFollow_Param_definitions(eTOKENS kind){
	if (kind != TOKEN_PARENTHESES_CLOSE)
		return 1;
	return 0;
}