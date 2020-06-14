#include "Expression.h"
#include "Expression1.h"


Types Parse_Expression(){
	SymbolTableNode* tmp;
	Types type;
	Token* t = next_token();
	switch(t->kind){
		case TOKEN_ID:
			fprintf(yyout,"Rule( EXPRESSION  -> id EXPRESSION1)\n");
			tmp = find(current_table_semantic, t->lexeme);
			if(tmp == NULL){
				fprintf(yyout2, "ERROR: undeclared identifier %s, at line: %d \n", t->lexeme, t->lineNumber);
			}
			else{
				if(tmp->infoVar->size > 0 && next_token()->lexeme != "["){
					fprintf(yyout2, "ERROR: expression can’t refer to entire array %s, at line: %d \n", tmp->idName, t->lineNumber);
					back_token();
				}
			}
			type = Parse_Expression1(t->lexeme);
			if(tmp == NULL)
				return checkType(NONE, type);
			return checkType(get_id_type(tmp), type);
		case TOKEN_INTEGER:
			fprintf(yyout,"Rule( EXPRESSION  ->int_number)\n");
			return INTEGER;
		case TOKEN_REAL:
			fprintf(yyout,"Rule( EXPRESSION  ->real_number )\n");
			return REAL;

		default:
			fprintf(yyout,"Expected token of type TOKEN_ID|TOKEN_INTEGER|TOKEN_REAL at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Expression);
			return NONE;	
	}
}

int notInFollow_Expression(eTOKENS kind){
	if (kind != TOKEN_SEMICOLON)
		return 1;
	return 0;
}

Types checkType(Types idType, Types exType){
	if(idType == INTEGER && exType == INTEGER)
		return INTEGER;
	if(exType == NONE)
		return NONE;
	return REAL;
}