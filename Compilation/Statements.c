#include "Statements.h"
#include "Statements1.h"
#include "Statement.h"

void Parse_Statements(){
	Token* tmp;
	fprintf(yyout,"Rule( STATEMENTS  -> STATEMENT; STATEMENTS1 )\n");
	Parse_Statement();
	if(!match(TOKEN_SEMICOLON)){
		tmp = &((Node*)currentNode)->tokensArray[currentIndex];//for the message error
		fprintf(yyout,"Expected token of type TOKEN_SEMICOLON at line: %d,\nActual token of type %s, lexeme: %s.\n", tmp->lineNumber, enum_to_string(tmp->kind), tmp->lexeme);
		error_handling(tmp, notInFollow_Statements);
		return;
	}
	Parse_Statements1();
}

int notInFollow_Statements(eTOKENS kind){
	if (kind != TOKEN_END_KEYWORD && kind != TOKEN_BRACES_CLOSE)
		return 1;
	return 0;
}
