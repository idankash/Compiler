#include "Variable1.h"

Types Parse_Variable1(char* idName, int flagExpression){
	SymbolTableNode* entry;
	Token* t = next_token();
	Token* tmp, *tmp2;
	entry = find(current_table_semantic, idName);
	if(flagExpression)
		if(entry == NULL)
			if(error_flag != 1)
				fprintf(yyout2, "ERROR: undeclared identifier %s, at line: %d \n", idName, t->lineNumber);
	switch(t->kind){
		case TOKEN_BARACKETS_OPEN:
			fprintf(yyout,"Rule( VARIABLE1  ->[int_number])\n");
			if(flagExpression){
				if(entry != NULL){
					if(entry->infoFunc == NULL){
						if(entry->infoVar->size == 0)
							fprintf(yyout2, "ERROR: identifier %s is not an array, at line: %d \n", idName, t->lineNumber);
					}
					else
						fprintf(yyout2, "ERROR: identifier %s is not an array, at line: %d \n", idName, t->lineNumber);
				}
			}
			
			
			if(!match(TOKEN_INTEGER)){
				tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
				fprintf(yyout,"Expected token of type TOKEN_INTEGER at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
				fprintf(yyout2, "ERROR: size of %s has to be an integer, at line: %d \n", idName, t->lineNumber);
				error_handling(tmp, notInFollow_Variable1);
				break;
			}
			tmp2 = &((Node*)currentNode)->tokensArray[currentIndex];
			if(flagExpression){
				if(entry != NULL)
					if(get_id_size(entry) <= ((int) strtol(tmp2->lexeme, (char **)NULL, 10)))
						fprintf(yyout2, "ERROR: index of %s is out of bounds, at line: %d \n", idName, t->lineNumber);
			}
			else
				if(overloading_flag == 0)
					set_id_size(entry, (int) strtol(tmp2->lexeme, (char **)NULL, 10));

			if(!match(TOKEN_BARACKETS_CLOSE)){
				tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
				fprintf(yyout,"Expected token of type TOKEN_BARACKETS_CLOSE at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
				error_handling(tmp, notInFollow_Variable1);
				break;
			}
			if(flagExpression)
				if(entry != NULL)
					return get_id_type(entry);
			return NONE;
		case TOKEN_SEMICOLON:
		case TOKEN_PARENTHESES_CLOSE:
		case TOKEN_EQUAL:
		case TOKEN_COMMA:
			fprintf(yyout,"Rule( Variable1  ->epsilon )\n");
			if(flagExpression != 1 && entry != NULL)
				if(overloading_flag == 0)
					set_id_size(entry, 0);
			back_token();
			if(flagExpression)
				if(entry != NULL)
					return get_id_type(entry);
			return NONE;
		default:
			fprintf(yyout,"Expected token of type TOKEN_BARACKETS_OPEN at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Variable1);
			break;
	}	
	return NONE;
}

int notInFollow_Variable1(eTOKENS kind){
	if (kind != TOKEN_SEMICOLON && kind != TOKEN_PARENTHESES_CLOSE && kind != TOKEN_EQUAL && kind != TOKEN_COMMA)
		return 1;
	return 0;
}