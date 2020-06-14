#include "Statements1.h"
#include "Statements.h"

void Parse_Statements1(){
	
	Token* t = next_token();
	switch(t->kind){
		case TOKEN_ID:
		case TOKEN_RETURN_KEYWORD:
		case TOKEN_BRACES_OPEN:
				fprintf(yyout,"Rule( STATEMENTS1  -> STATEMENTS )\n");
				back_token();
				Parse_Statements();
				break;
		case TOKEN_BRACES_CLOSE:
		case TOKEN_END_KEYWORD:
			fprintf(yyout,"Rule( STATEMENTS1  ->epsilon )\n");
			back_token();
			break;

		default:
			fprintf(yyout,"Expected token of type TOKEN_ID|TOKEN_RETURN_KEYWORD|TOKEN_BRACES_OPEN|TOKEN_BRACES_CLOSE(epsilon)|TOKEN_END_KEYWORD(epsilon) at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Statements1);
			break;

	}
}

int notInFollow_Statements1(eTOKENS kind){
	if (kind != TOKEN_BRACES_CLOSE && kind != TOKEN_END_KEYWORD)
		return 1;
	return 0;
}