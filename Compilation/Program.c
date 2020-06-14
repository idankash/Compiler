#include "Program.h"
#include "Var_definitions.h"
#include "Statements.h"
#include "Func_definitions.h"

void Parse_Program(){
		Token* tmp;
		Parse_BB();
		if(!match(TOKEN_PROGRAM_KEYWORD)){
			tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
			fprintf(yyout,"Expected token of type TOKEN_PROGRAM_KEYWORD at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
			error_handling(tmp, notInFollow_Program);
			return;
		}
		fprintf(yyout,"Rule( PPROGRAM ->program VAR_DEFINITIONS; STATEMENTS end FUNC_DEFINITIONS)\n");
		Parse_Var_definitions();
		if(!match(TOKEN_SEMICOLON)){
			tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
			fprintf(yyout,"Expected token of type TOKEN_SEMICOLON at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
			error_handling(tmp, notInFollow_Program);
			return;
		}
		Parse_Statements();
		if(!match(TOKEN_END_KEYWORD)){
			tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
			fprintf(yyout,"Expected token of type TOKEN_END_KEYWORD at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
			error_handling(tmp, notInFollow_Program);
			return;
		}
		Parse_Func_definitions();
		
		Parse_FB();
}

int notInFollow_Program(eTOKENS kind){
	if (kind != TOKEN_EOF)
		return 1;
	return 0;
}