#include "Func_definitions.h"
#include "Func_definitions1.h"
#include "Func_definition.h"

void Parse_Func_definitions(){
	fprintf(yyout,"Rule( FUNC_DEFINITIONS  -> FUNC_DEFINITION FUNC_DEFINITIONS1 )\n");
	Parse_Func_definition();
	Parse_Func_definitions1();
}
