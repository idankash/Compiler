#include "BB.h"

void Parse_BB(){
	if(func_flag != 1)
		current_table_semantic = make_table(current_table_semantic);
	else
		func_flag = 0;
}