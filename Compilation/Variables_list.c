#include "Variables_list.h"
#include "Variable.h"
#include "Variables_list1.h"

TypesNode* Parse_Variables_list(Types attr){
	TypesNode* newList;
	fprintf(yyout,"Rule( VARIABLES_LIST  -> VARIABLE  VARIABLES_LIST1 )\n");
	newList = Parse_Variable(attr);
	newList->next = Parse_Variables_list1(attr);
	return newList;
}
