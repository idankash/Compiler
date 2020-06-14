#include "Var_definition.h"
#include "Type.h"
#include "Variables_list.h"

TypesNode* Parse_Var_definition(){
	Types attr_type;
	fprintf(yyout,"Rule( VAR_DEFINITION  -> TYPE VARIABLES_LIST )\n");
	attr_type = Parse_Type();
	return Parse_Variables_list(attr_type);

}
