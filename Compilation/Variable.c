#include "Variable.h"
#include "Variable1.h"
#include "Token.h"

TypesNode* Parse_Variable(Types attr){
	Token* tmp, *tmp2;
	TypesNode* typeNode = (TypesNode*)malloc(sizeof(TypesNode));
	char* idName;
	SymbolTableNode* newEntry;
	fprintf(yyout,"Rule( VARIABLE  -> id VARIABLE1  )\n");	
	if(!match(TOKEN_ID)){
		tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
		fprintf(yyout,"Expected token of type TOKEN_ID at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
		error_handling(tmp, notInFollow_Variable);
		return NULL;
	}
	tmp2 = &((Node*)currentNode)->tokensArray[currentIndex];
	idName = tmp2->lexeme;
	if(param_flag == 0 && attr != NONE){ //checking if we are not in param list of function 
		if(overloading_flag == 0){
			if(getFunc() != NULL && alreadyDefined(idName) == 1)
				fprintf(yyout2, "ERROR: identifier %s already declared in parameters list, at line %d \n", idName, tmp2->lineNumber); 
			else{
					newEntry = insert(current_table_semantic, idName);
					if(newEntry == NULL)
						fprintf(yyout2, "ERROR: identifier already declared %s, at line %d \n", idName, tmp2->lineNumber); 
					else
						set_id_type_var(newEntry, attr);
			}
		}
	
			

		Parse_Variable1(idName, 0);

		if(overloading_flag == 0){
			typeNode->back = NULL;
			typeNode->next = NULL;
			typeNode->type = attr;
			typeNode->name = idName;
		}
	}
	else if(param_flag == 0){
		if(overloading_flag == 0){
		newEntry = find(current_table_semantic, idName);
		typeNode->back = NULL;
		typeNode->next = NULL;
		if(newEntry != NULL && newEntry->infoVar != NULL)
		typeNode->type = newEntry->infoVar->type;
		typeNode->name = idName;
		}
	}
	else{
		if(overloading_flag == 0){
		newEntry = insert(current_table_semantic, idName);
		if(newEntry != NULL)
			set_id_type_var(newEntry, attr);
		typeNode->back = NULL;
		typeNode->next = NULL;
		typeNode->type = attr;
		typeNode->name = idName;
		}
	}
	return typeNode;
}

int notInFollow_Variable(eTOKENS kind){
	if (kind != TOKEN_SEMICOLON && kind != TOKEN_PARENTHESES_CLOSE && kind != TOKEN_EQUAL && kind != TOKEN_COMMA)
		return 1;
	return 0;
}

int alreadyDefined(char* idName){ // check if idName already defined
	SymbolTableNode* tmp = getFunc();
	TypesNode* node = tmp->infoFunc->parmList;
	while(node != NULL){
		if(!strcmp(node->name, idName))
			return 1;
		node = node->next;
	}
	return 0;
}

SymbolTableNode* getFunc(){ //return the entry of the current function
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