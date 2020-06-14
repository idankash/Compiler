#include "Function_call.h"
#include "Parameters_list.h"

void Parse_Function_call(){
	Token* t = next_token();
	Token* tmp;
	switch(t->kind){
		case TOKEN_ID:
			fprintf(yyout,"Rule( FUNCTION_CALL  -> id (PARAMETERS_LIST))\n");
			if(!match(TOKEN_PARENTHESES_OPEN)){
				tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
				fprintf(yyout,"Expected token of type TOKEN_PARENTHESES_OPEN at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
				error_handling(tmp, notInFollow_Function_call);
				break;
			}
			Parse_Parameters_list();
			if(!match(TOKEN_PARENTHESES_CLOSE)){
				tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
				fprintf(yyout,"Expected token of type TOKEN_PARENTHESES_CLOSE at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
				error_handling(tmp, notInFollow_Function_call);
				break;
			}
			break;

		default:
			fprintf(yyout,"Expected token of type TOKEN_ID at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Function_call);
			break;

	}
}

int notInFollow_Function_call(eTOKENS kind){
	if (kind != TOKEN_SEMICOLON)
		return 1;
	return 0;
}