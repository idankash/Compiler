#include "Parameters_list.h"
#include "Variables_list.h"

TypesNode* Parse_Parameters_list(){
	
	Token* t = next_token();
	switch(t->kind){
		case TOKEN_ID:
				fprintf(yyout,"Rule( PARAMETERS_LIST  -> | VARIABLES_LIST))\n");
				back_token();
				return Parse_Variables_list(NONE);
		case TOKEN_PARENTHESES_CLOSE:
			fprintf(yyout,"Rule( PARAMETERS_LIST  -> epsilon))\n");
			back_token();
			return NULL;

		default:
			fprintf(yyout,"Expected token of type TOKEN_ID|TOKEN_PARENTHESES_CLOSE(epsilon) at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Parameters_list);
			return NULL;

	}
}

int notInFollow_Parameters_list(eTOKENS kind){
	if (kind != TOKEN_PARENTHESES_CLOSE)
		return 1;
	return 0;
}