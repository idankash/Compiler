#ifndef PARSER_H
#define PARSER_H

#include "Token.h"

int match(eTOKENS kind);
Token* peek();
char* enum_to_string(eTOKENS kind);
void error_handling(Token* t, int(*f)(eTOKENS));
void main_parser();

//semantic analysis
typedef enum Types{
	INTEGER = 0,
	REAL = 1, 
	VOID = 2,
	NONE = 3 //error-type
}Types;

typedef struct Var{
	Types type;
	int size;
}Var;

typedef struct TypesNode{
	struct TypesNode* next;
	struct TypesNode* back;
	Types type;
	char* name;

}TypesNode;

typedef struct Func{
	Types type;
	TypesNode* parmList; //types of parameters inside parameters list
	int numOfParams; //number of parameters inside parameters list
	int returnFlag; //return exist
}Func;

typedef struct SymbolTableNode{
	struct SymbolTableNode* next;
	struct SymbolTableNode* back;
	Var* infoVar;
	Func* infoFunc;
	char* idName;

}SymbolTableNode;

typedef struct SymbolTable{
	struct SymbolTable* father;
	SymbolTableNode* nodeList;
}SymbolTable;

SymbolTable* make_table(SymbolTable* table);
SymbolTable* pop_table(SymbolTable* table);
SymbolTableNode* insert(SymbolTable* table, char* id_name);
SymbolTableNode* lookup(SymbolTable* table, char* id_name);
SymbolTableNode* find(SymbolTable* table, char* id_name);
SymbolTableNode* insert_to_table(SymbolTable* table, char* id_name);
void delete_list(SymbolTableNode* head);
void set_id_type_var(SymbolTableNode* id_entry, Types type);
void set_id_type_func(SymbolTableNode* id_entry, Types type);
void set_id_returnFlag(SymbolTableNode* id_entry, int flag);
void set_id_size(SymbolTableNode* id_entry, int size);
void set_id_num_of_params(SymbolTableNode* id_entry, int numOfParams);
void set_id_params_list(SymbolTableNode* id_entry, TypesNode* ParamsList);
Types get_id_type(SymbolTableNode* id_entry);
int get_id_size(SymbolTableNode* id_entry);
int get_id_num_of_params(SymbolTableNode* id_entry);
int get_id_returnFlag(SymbolTableNode* id_entry);
TypesNode* get_id_params_list(SymbolTableNode* id_entry);

extern SymbolTable *current_table_semantic;
extern int param_flag; //variable in function parameters list
extern int func_flag; //block inside function
extern int error_flag; 
extern int overloading_flag; //checking for overloading function

#endif