#include "Variables_list1.h"
#include "Variable.h"

TypesNode* Parse_Variables_list1(Types attr){
	TypesNode* newList;
	Token* t = next_token();
	switch(t->kind){
		case TOKEN_COMMA:
			fprintf(yyout,"Rule( VARIABLES_LIST1 -> , VARIABLE  VARIABLES_LIST1)\n");
			newList = Parse_Variable(attr);
			if(newList == NULL)
				newList = (TypesNode*)malloc(sizeof(TypesNode));
			newList->next = (TypesNode*)malloc(sizeof(TypesNode));
			newList->next = Parse_Variables_list1(attr);
			return newList;

		case TOKEN_SEMICOLON:
		case TOKEN_PARENTHESES_CLOSE:
			fprintf(yyout,"Rule( VARIABLES_LIST1  ->epsilon )\n");
			back_token();
			return NULL;

		default:
			fprintf(yyout,"Expected token of type TOKEN_COMMA at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Variables_list1);
			return NULL;

	}
}

int notInFollow_Variables_list1(eTOKENS kind){
	if (kind != TOKEN_PARENTHESES_CLOSE && kind != TOKEN_SEMICOLON)
		return 1;
	return 0;
}