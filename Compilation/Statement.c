#include "Statement.h"
#include "Statement1.h"
#include "Statement2.h"
#include "Variable.h"
#include "Expression.h"
#include "Block.h"
#include "Function_call.h"

void Parse_Statement(){
	Types type;
	Token* t = next_token();
	switch(t->kind){
		case TOKEN_ID:
			fprintf(yyout,"Rule( STATEMENT  ->  idSTATEMENT2)\n");
			if(find(current_table_semantic, t->lexeme) == NULL){
				fprintf(yyout2, "ERROR: undeclared identifier %s, at line: %d \n", t->lexeme, t->lineNumber);
				error_flag = 1;
			}
			Parse_Statement2(t->lexeme);
			break;
		case TOKEN_BRACES_OPEN:
			fprintf(yyout,"Rule( STATEMENT  ->  BLOCK)\n");
			back_token();
			Parse_Block();
			break;
		case TOKEN_RETURN_KEYWORD:
			fprintf(yyout,"Rule( STATEMENT  -> return STATEMENT*)\n");
			type = Parse_Statement1();
			if(current_table_semantic->father == NULL){ // if we are inside main block
				if(type != VOID)
					fprintf(yyout2, "ERROR: main block can not return value, at line: %d \n", t->lineNumber);
			}
			else{
				if(overloading_flag == 0 && type != getBlockType() && getBlockType() != NONE) //return type matches function type
					fprintf(yyout2, "ERROR: return type does not match function %s type, at line: %d \n", t->lexeme, t->lineNumber);
				else if(overloading_flag == 0 && getBlockType() != NONE)
					set_id_returnFlag(getFunc(), 1);
			}
			break;
		default:
			fprintf(yyout,"Expected token of type TOKEN_ID|TOKEN_BRACES_OPEN|TOKEN_RETURN_KEYWORD at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Statement);
			break;	
	}
}

int notInFollow_Statement(eTOKENS kind){
	if (kind != TOKEN_SEMICOLON)
		return 1;
	return 0;
}

Types getBlockType(){ //return function return type
	SymbolTableNode* tmp = current_table_semantic->father->nodeList;

	if(tmp != NULL){
		while(tmp->next != NULL)
			tmp = tmp->next;

		if(tmp->infoFunc != NULL)
			return tmp->infoFunc->type;
	}
	return NONE;
}