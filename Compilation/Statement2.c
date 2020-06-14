#include "Variable1.h"
#include "Expression.h"
#include "Statement2.h"
#include "Parameters_list.h"

void Parse_Statement2(char* idName){
	SymbolTableNode * node, *tempNode;
	TypesNode* paramList;
	Types right, left;
	Token *t = next_token();
	Token* tmp;

	switch(t->kind){
	case TOKEN_PARENTHESES_OPEN:
		fprintf(yyout,"Rule( STATEMENT2  -> (PARAMETERS_LIST))\n");
		tempNode = find(current_table_semantic, idName);
		if(tempNode == NULL)
			fprintf(yyout2, "ERROR: function %s must be defined, at line: %d \n", idName, t->lineNumber);
		else if(tempNode->infoFunc == NULL)
				fprintf(yyout2, "ERROR: identifier %s must be a function, at line: %d \n", idName, t->lineNumber);

		paramList = Parse_Parameters_list();
		if(tempNode != NULL && num_of_params(paramList) != tempNode->infoFunc->numOfParams){
			fprintf(yyout2, "ERROR: number of parameters do not match definition of function %s , at line: %d \n", idName, t->lineNumber);
		}
		else{
			if(tempNode != NULL && compareList(paramList, tempNode->infoFunc->parmList) == 0)
				fprintf(yyout2, "ERROR: types of parameters do not match definition of function %s , at line: %d \n", idName, t->lineNumber);
		}
		if(!match(TOKEN_PARENTHESES_CLOSE)){
			tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
			fprintf(yyout,"Expected token of type TOKEN_PARENTHESES_OPEN at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
			error_handling(tmp, notInFollow_Statement2);
			break;
		}
		break;
	default:
		fprintf(yyout,"Rule( STATEMENT2  -> VARIABLE1 = EXPRESSION)\n");
		back_token();
		left = Parse_Variable1(idName, 1);
		if(!match(TOKEN_EQUAL)){
			tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
			fprintf(yyout,"Expected token of type TOKEN_EQUAL at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
			error_handling(tmp, notInFollow_Statement2);
			break;
		}

		node = find(current_table_semantic,idName);
		if(node == NULL)
			if(error_flag != 1)
				fprintf(yyout2, "ERROR: undeclared identifier %s, at line: %d \n", idName, t->lineNumber);
			else
				error_flag = 0;
		else{
			if(node->infoFunc != NULL)
				fprintf(yyout2, "ERROR: assignment to %s is forbidden, %s is declared as function, at line: %d \n", idName,idName, t->lineNumber);
			else{
				if(node->infoVar->size > 0){
					if(strcmp(back_token()->lexeme, "]"))
						fprintf(yyout2, "ERROR: assignment to array %s without index is forbidden, at line: %d \n", idName, t->lineNumber);
					next_token();
				}
			}
		}
		right = Parse_Expression();

		if(left == INTEGER && right == REAL)
			fprintf(yyout2, "ERROR: illegal assignment, at line: %d \n", t->lineNumber);
		break;

	}
}

int notInFollow_Statement2(eTOKENS kind){
	if (kind != TOKEN_SEMICOLON)
		return 1;
	return 0;
}

int num_of_params(TypesNode* paramList){
	int size = 0;
	TypesNode* tmp = paramList;
	while(tmp != NULL){
		size++;
		tmp = tmp->next;
	}

	return size;
}

int compareList(TypesNode* l1, TypesNode* l2){
	TypesNode* tmp1 = l1, *tmp2 = l2;
	
	if(num_of_params(l1) != num_of_params(l2))
		return 0;

	while(tmp1 != NULL && tmp2 != NULL){
		if(tmp1->type != tmp2->type)
			return 0;
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}

	return 1;
}