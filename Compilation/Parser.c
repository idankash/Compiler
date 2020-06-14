#include "Parser.h"
#include "Token.h"
#include "Program.h"

SymbolTable *current_table_semantic = NULL;
int param_flag = 0;
int func_flag = 0;
int error_flag = 0;
int overloading_flag = 0;

int match(eTOKENS kind){
	Token* nt = next_token();
	if(nt->kind == kind)
		return 1;
	return 0;
}

Token* peek(){
	Token* t = next_token();
	back_token();
	return t;
}

void main_parser(){
	Parse_Program();
	if (match(TOKEN_EOF)){
		fprintf(yyout,"Reached TOKEN_EOF!\n");
		fprintf(yyout2,"Reached EOF!\n");
	}
	
}

void error_handling(Token* t, int(*f)(eTOKENS)){
	while((*f)(t->kind) && t->kind != TOKEN_EOF)
				t = next_token();
			back_token();
}
char* enum_to_string(eTOKENS kind){

	switch(kind){
		case TOKEN_INTEGER:
			return "TOKEN_INTEGER";
			break;
		case TOKEN_REAL:
			return "TOKEN_REAL";
			break;
		case TOKEN_DIV:
			return "TOKEN_DIV";
			break;
		case TOKEN_MUL:
			return "TOKEN_MUL";
			break;
		case TOKEN_EQUAL:
			return "TOKEN_EQUAL";
			break;
		case TOKEN_PROGRAM_KEYWORD:
			return "TOKEN_PROGRAM_KEYWORD";
			break;
		case TOKEN_END_KEYWORD:
			return "TOKEN_END_KEYWORD";
			break;
		case TOKEN_REAL_KEYWORD:
			return "TOKEN_REAL_KEYWORD";
			break;
		case TOKEN_INTEGER_KEYWORD:
			return "TOKEN_INTEGER_KEYWORD";
			break;
		case TOKEN_VOID_KEYWORD:
			return "TOKEN_VOID_KEYWORD";
			break;
		case TOKEN_RETURN_KEYWORD:
			return "TOKEN_RETURN_KEYWORD";
			break;
			case TOKEN_COMMA:
			return "TOKEN_COMMA";
			break;
		case TOKEN_SEMICOLON:
			return "TOKEN_SEMICOLON";
			break;
		case TOKEN_BARACKETS_OPEN:
			return "TOKEN_BARACKETS_OPEN";
			break;
		case TOKEN_BARACKETS_CLOSE:
			return "TOKEN_BARACKETS_CLOSE";
			break;
		case TOKEN_BRACES_OPEN:
			return "TOKEN_BRACES_OPEN";
			break;
		case TOKEN_BRACES_CLOSE:
			return "TOKEN_BRACES_CLOSE";
			break;
		case TOKEN_PARENTHESES_OPEN:
			return "TOKEN_PARENTHESES_OPEN";
			break;
		case TOKEN_PARENTHESES_CLOSE:
			return "TOKEN_PARENTHESES_CLOSE";
			break;
		case TOKEN_ID:
			return "TOKEN_ID";
			break;
		case TOKEN_EOF:
			return "TOKEN_EOF";
			break;
		default:
			return "Invalid token kind";
			break;

	}
}

//semantic analysis
SymbolTable* make_table(SymbolTable* table){
	SymbolTable* new_table = (SymbolTable*)malloc(sizeof(SymbolTable));
	if(new_table != NULL){
		new_table->father = table;
		new_table->nodeList = NULL;
	}
	current_table_semantic = new_table;
	return new_table;
}

SymbolTable* pop_table(SymbolTable* table){
	current_table_semantic = table->father;
	delete_list(table->nodeList);
	if(table != NULL)
		free(table);
	return current_table_semantic;
}

SymbolTableNode* insert(SymbolTable* table, char* id_name){
	SymbolTableNode* entry = lookup(table, id_name);
	if(entry != NULL){
		return NULL;
	}
	return insert_to_table(table, id_name);

}

SymbolTableNode* lookup(SymbolTable* table, char* id_name){
	SymbolTableNode* list = table->nodeList;
	while(list != NULL){
		if(!strcmp(list->idName, id_name))
			return list;
		list = list->next;
	}
	return NULL;
}

SymbolTableNode* find(SymbolTable* table, char* id_name){
	SymbolTableNode* entry;
	SymbolTable* tab = table;
	while(tab != NULL){
		entry = lookup(tab, id_name);
		if(entry != NULL)
			return entry;
		else
			tab = tab->father;
	} 
	return NULL;
}

SymbolTableNode* insert_to_table(SymbolTable* table, char* id_name){
	SymbolTableNode* node;
	SymbolTableNode* newnode = (SymbolTableNode*)malloc(sizeof(SymbolTableNode));
	if(table != NULL){
		node = table->nodeList;
		if(node == NULL){
			table->nodeList = newnode;
			newnode->back = node;
			newnode->next = NULL;
			newnode->idName = id_name;
			newnode->infoFunc = NULL;
			newnode->infoVar = NULL;
		}
		else{
			while(node->next != NULL)
				node = node->next;

			node->next = newnode;
			newnode->back = node;
			newnode->next = NULL;
			newnode->idName = id_name;
			newnode->infoFunc = NULL;
			newnode->infoVar = NULL;
		}
		return newnode;
	}
	return NULL;
}

void delete_list(SymbolTableNode* head){
	SymbolTableNode* temp;

	while(head != NULL){
		temp = head->next;
		free(head->idName);
		if(head->infoFunc != NULL){
			if(head->infoFunc->parmList != NULL)
				free(head->infoFunc);
		}
		if(head != NULL)
			free(head);
		head = temp;
	}
	head = NULL;
}

void set_id_type_var(SymbolTableNode* id_entry, Types type){
	if(id_entry!=NULL){
		if(id_entry->infoVar == NULL)
			id_entry->infoVar = (Var*)malloc(sizeof(Var));
		id_entry->infoVar->type = type;
	}
}

void set_id_type_func(SymbolTableNode* id_entry, Types type){
	if(id_entry!=NULL){
		if(id_entry->infoFunc == NULL)
			id_entry->infoFunc = (Func*)malloc(sizeof(Func));
		id_entry->infoFunc->type = type;
	}
}

void set_id_returnFlag(SymbolTableNode* id_entry, int flag){
	if(id_entry!=NULL){
		if(id_entry->infoFunc == NULL)
			id_entry->infoFunc = (Func*)malloc(sizeof(Func));
		id_entry->infoFunc->returnFlag = flag;
	}
}

void set_id_size(SymbolTableNode* id_entry, int size){
	if(id_entry!=NULL){
		if(id_entry->infoVar == NULL)
			id_entry->infoVar = (Var*)malloc(sizeof(Var));
		id_entry->infoVar->size = size;
	}
}

void set_id_num_of_params(SymbolTableNode* id_entry, int numOfParams){
	if(id_entry!=NULL){
		if(id_entry->infoFunc == NULL)
			id_entry->infoFunc = (Func*)malloc(sizeof(Func));
		id_entry->infoFunc->numOfParams = numOfParams;
	}
}

void set_id_params_list(SymbolTableNode* id_entry, TypesNode* ParamsList){
	if(id_entry!=NULL){
		if(id_entry->infoFunc == NULL)
			id_entry->infoFunc = (Func*)malloc(sizeof(Func));
		id_entry->infoFunc->parmList = ParamsList;
	}
}

Types get_id_type(SymbolTableNode* id_entry){
	if(id_entry!=NULL){
		if(id_entry->infoFunc != NULL)
			return id_entry->infoFunc->type;
		else
			return id_entry->infoVar->type;
	}
	return NONE;
}

int get_id_size(SymbolTableNode* id_entry){
	if(id_entry != NULL && id_entry->infoVar != NULL)
		return id_entry->infoVar->size;
	return 0;
}

int get_id_num_of_params(SymbolTableNode* id_entry){
	if(id_entry != NULL && id_entry->infoFunc != NULL)
		return id_entry->infoFunc->numOfParams;
	return 0;
}

int get_id_returnFlag(SymbolTableNode* id_entry){
	if(id_entry != NULL && id_entry->infoFunc != NULL)
		return id_entry->infoFunc->returnFlag;
	return 0;
}

TypesNode* get_id_params_list(SymbolTableNode* id_entry){
	if(id_entry != NULL && id_entry->infoFunc != NULL)
		return id_entry->infoFunc->parmList;
	return NULL;
}