#include "Var_definitions1.h"
#include "Var_definitions.h"
#include "Parser.h"

TypesNode* Parse_Var_definitions1(){
	Token* t = next_token();
	Token* next;
	switch(t->kind){

		case TOKEN_SEMICOLON:
			next = peek();
			if(next->kind == TOKEN_REAL_KEYWORD || next->kind == TOKEN_INTEGER_KEYWORD){
				fprintf(yyout,"Rule( VAR_DEFINITIONS1 -> ; VAR_DEFINITIONS  )\n");
				return Parse_Var_definitions();		
			}
		case TOKEN_PARENTHESES_CLOSE:
			fprintf(yyout,"Rule( Variable1  ->epsilon )\n");
			back_token();
			return NULL;
		default:
			fprintf(yyout,"Expected token of type TOKEN_SEMICOLON at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Var_definitions1);
			return NULL;
	}
}

int notInFollow_Var_definitions1(eTOKENS kind){
	if (kind != TOKEN_PARENTHESES_CLOSE && kind != TOKEN_SEMICOLON)
		return 1;
	return 0;
}