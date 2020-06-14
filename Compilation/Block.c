#include "Block.h"
#include "Var_definitions.h"
#include "Statements.h"

void Parse_Block(){
	Token* t = next_token();
	Token* tmp;
	switch(t->kind){
		case TOKEN_BRACES_OPEN:
			fprintf(yyout,"Rule( BLOCK  -> { VAR_DEFINITIONS; STATEMENTS })\n");
			Parse_BB();
			Parse_Var_definitions();
			if(!match(TOKEN_SEMICOLON)){
				tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
				fprintf(yyout,"Expected token of type TOKEN_BRACES_OPEN at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
				error_handling(tmp, notInFollow_Block);
				break;
			}
			Parse_Statements();
			if(!match(TOKEN_BRACES_CLOSE)){
				tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
				fprintf(yyout,"Expected token of type TOKEN_BRACES_OPEN at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
				error_handling(tmp, notInFollow_Block);
				break;
			}
			if(overloading_flag == 0 && getFunc_b() != NULL && get_id_returnFlag(getFunc_b()) == 0 && getFunc_b()->infoFunc->type != VOID)
				fprintf(yyout2, "ERROR: function must return value, at line: %d \n", t->lineNumber);
			Parse_FB();
			break;

		default:
			fprintf(yyout,"Expected token of type TOKEN_BRACES_OPEN at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Block);
			break;

	}
}

int notInFollow_Block(eTOKENS kind){
	if (kind != TOKEN_EOF && kind != TOKEN_SEMICOLON && kind != TOKEN_VOID_KEYWORD && kind != TOKEN_REAL_KEYWORD && kind != TOKEN_INTEGER_KEYWORD)
		return 1;
	return 0;
}

SymbolTableNode* getFunc_b(){
	SymbolTable* tmpFather = current_table_semantic->father;
	SymbolTableNode* tmpNode;

	if(tmpFather == NULL)
		return NULL;

	tmpNode = tmpFather->nodeList;
	while(tmpNode->next != NULL)
		tmpNode = tmpNode->next;
	if(tmpNode->infoFunc != NULL)
		return tmpNode;
	return NULL;
}