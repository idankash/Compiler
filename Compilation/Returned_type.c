#include "Returned_type.h"
#include "Type.h"

Types Parse_Returned_type(){
	Token* t = next_token();
	switch(t->kind){
		case TOKEN_VOID_KEYWORD:
			fprintf(yyout,"Rule( RETURNED_TYPE  -> void)\n");
			return VOID;

		default:
			back_token();
			return Parse_Type();		

	}
}