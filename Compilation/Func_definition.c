#include "Func_definition.h"
#include "Returned_type.h"
#include "Param_definitions.h"
#include "BB.h"
#include "Block.h"

void Parse_Func_definition(){
	Types type;
	TypesNode* paramList;
	char* idName;
	SymbolTableNode* newEntry;
	Token* t = next_token();
	Token* tmp, *tmp2;
	switch(t->kind){
		case TOKEN_VOID_KEYWORD:
		case TOKEN_REAL_KEYWORD:
		case TOKEN_INTEGER_KEYWORD:
			fprintf(yyout,"Rule( FUNC_DEFINITION -> RETURNED_TYPE id (PARAM_DEFINITIONS)BLOCK )\n");
			back_token();
			type = Parse_Returned_type();
			if(!match(TOKEN_ID)){
				tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
				fprintf(yyout,"Expected token of type TOKEN_ID at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
				error_handling(tmp, notInFollow_Func_definition);
				break;
			}
			tmp2 = &((Node*)currentNode)->tokensArray[currentIndex];
			idName = tmp2->lexeme;
			newEntry = insert(current_table_semantic, idName);
			
			if(newEntry != NULL){
				set_id_type_func(newEntry, type);
				set_id_returnFlag(newEntry, 0);
			}
			else{
				fprintf(yyout2, "ERROR: function already declared %s, at line: %d \n", idName, tmp2->lineNumber); 
				overloading_flag = 1;
			}

			if(overloading_flag == 0){
				Parse_BB();
				func_flag = 1;
			}
			

			if(!match(TOKEN_PARENTHESES_OPEN)){
				tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
				fprintf(yyout,"Expected token of type TOKEN_PARENTHESES_OPEN at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
				error_handling(tmp, notInFollow_Func_definition);
				break;
			}
			param_flag = 1;
			paramList = Parse_Param_definitions();
			param_flag = 0;
			if(!match(TOKEN_PARENTHESES_CLOSE)){
				tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
				fprintf(yyout,"Expected token of type TOKEN_PARENTHESES_CLOSE at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
				error_handling(tmp, notInFollow_Func_definition);
				break;
			}

			if(overloading_flag == 0){
				set_id_params_list(newEntry, paramList);
				set_id_num_of_params(newEntry, num_of_params_f(paramList));
			}

			Parse_Block();

			if(overloading_flag == 1){
				overloading_flag = 0;
			}
			break;

		default:
			fprintf(yyout,"Expected token of type TOKEN_INTEGER_KEYWORD|TOKEN_VOID_KEYWORD|TOKEN_REAL_KEYWORD at line: %d,\nActual token of type %s, lexeme: %s.\n", t->lineNumber, enum_to_string(t->kind), t->lexeme);
			error_handling(t, notInFollow_Func_definition);
			break;
	}
}

int notInFollow_Func_definition(eTOKENS kind){
	if (kind != TOKEN_EOF && kind != TOKEN_VOID_KEYWORD && kind != TOKEN_REAL_KEYWORD && kind != TOKEN_INTEGER_KEYWORD)
		return 1;
	return 0;
}

int num_of_params_f(TypesNode* paramList){
	int size = 0;
	TypesNode* tmp = paramList;
	while(tmp != NULL){
		size++;
		tmp = tmp->next;
	}

	return size;
}