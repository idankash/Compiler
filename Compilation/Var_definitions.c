#include "Var_definitions.h"
#include "Var_definitions1.h"
#include "Var_definition.h"


TypesNode* Parse_Var_definitions(){
	TypesNode* newList, *tmp;
	fprintf(yyout,"Rule( VAR_DEFINITIONS -> VAR_DEFINITION VAR_DEFINITIONS1 )\n");
	newList = Parse_Var_definition();
	tmp = newList;
	while(tmp->next != NULL) //end of the list
		tmp = tmp->next;
	tmp->next = Parse_Var_definitions1();
	return newList;
}
