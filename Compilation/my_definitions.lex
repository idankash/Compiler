%{ 
#include<stdio.h> 
#include<string.h> 
#include "Token.h"
#include "Parser.h"
int line = 1;
int task1 = 1;
int yywrap() {return 1;}
FILE * yyout2;
%}
DIGIT [0-9]
INTEGER 0|[1-9]{DIGIT}*
REAL 0"."{DIGIT}+|[1-9]{DIGIT}*"."{DIGIT}+
WORD [a-zA-Z][a-zA-Z0-9]*
UNDWITHWRD "_"[a-zA-Z0-9]+
COMMENT "--".*
TABORSPACES "	"|" "
%%
{INTEGER}					{handle_token(TOKEN_INTEGER, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_INTEGER was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
{REAL}   					{handle_token(TOKEN_REAL, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_REAL was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"/"	                        {handle_token(TOKEN_DIV, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_DIV operator was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"*" 						{handle_token(TOKEN_MUL, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_MUL operator was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"="                         {handle_token(TOKEN_EQUAL, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_EQUAL was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"program"					{handle_token(TOKEN_PROGRAM_KEYWORD, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_PROGRAM_KEYWORD was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"end"						{handle_token(TOKEN_END_KEYWORD, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_END_KEYWORD was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"real"						{handle_token(TOKEN_REAL_KEYWORD, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_REAL_KEYWORD was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"integer"					{handle_token(TOKEN_INTEGER_KEYWORD, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_INTEGER_KEYWORD was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"void"						{handle_token(TOKEN_VOID_KEYWORD, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_VOID_KEYWORD was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"return"					{handle_token(TOKEN_RETURN_KEYWORD, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_RETURN_KEYWORD was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
","							{handle_token(TOKEN_COMMA, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_COMMA was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
";"							{handle_token(TOKEN_SEMICOLON, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_SEMICOLON was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"["							{handle_token(TOKEN_BARACKETS_OPEN, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_BARACKETS_OPEN was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"]"							{handle_token(TOKEN_BARACKETS_CLOSE, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_BARACKETS_CLOSE was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"{"							{handle_token(TOKEN_BRACES_OPEN, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_BRACES_OPEN was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"}"							{handle_token(TOKEN_BRACES_CLOSE, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_BRACES_CLOSE was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
"("							{handle_token(TOKEN_PARENTHESES_OPEN, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_PARENTHESES_OPEN was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
")"							{handle_token(TOKEN_PARENTHESES_CLOSE, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_PARENTHESES_CLOSE was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}
{WORD}{UNDWITHWRD}*|{WORD}	{handle_token(TOKEN_ID, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_ID was found at line: %d, lexeme: %s.\n", line, yytext);return 1;}					
{COMMENT}					{}
{TABORSPACES}				{}
\n    						{line++;}
<<EOF>>						{handle_token(TOKEN_EOF, yytext, line); if(task1)fprintf(yyout,"Token of kind TOKEN_EOF was found at line: %d, lexeme: <<EOF>>.\n", line); return 0;}
.							{if(task1)fprintf(yyout,"The character %s at line: %d does not begin any legal token in the language.\n", yytext, line);return 1;}
%%  
  
int main() 
{   
	/*Part 1 - test 1*/
    yyin=fopen("C:\\temp\\test1.txt ","r");
    yyout=fopen("c:\\temp\\test1_315877902_328724588_lex.txt","w");  
    while(yylex());
	fclose(yyin);
	fclose(yyout);
	free_tokens();

	/*Part 1 - test 2*/
	line = 1;
	yyin=fopen("C:\\temp\\test2.txt ","r");
    yyout=fopen("c:\\temp\\test2_315877902_328724588_lex.txt","w");  
    while(yylex());
	fclose(yyin);
	fclose(yyout);
	free_tokens();
	
	//Disable irelevant printing
	task1 = 0;
	
	/*Part 2 - test 1*/
	line = 1;
	yyin=fopen("C:\\temp\\test1.txt ","r");
    yyout=fopen("c:\\temp\\test1_315877902_328724588_syntactic.txt","w"); 
	yyout2=fopen("c:\\temp\\test1_315877902_328724588_semantic.txt","w"); 
	main_parser();
	fclose(yyin);
	fclose(yyout);
	free_tokens();
	
	/*Part 2 - test 2*/
	line = 1;
	yyin=fopen("C:\\temp\\test2.txt ","r");
    yyout=fopen("c:\\temp\\test2_315877902_328724588_syntactic.txt","w"); 
	yyout2=fopen("c:\\temp\\test2_315877902_328724588_semantic.txt","w");
	main_parser();
	fclose(yyin);
	fclose(yyout);
	free_tokens();
	
    
    return 0; 
}
