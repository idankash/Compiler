#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin, *yyout, *yyout2;
extern int yylex();
extern int currentIndex;


typedef enum eTOKENS
{
	TOKEN_INTEGER,
	TOKEN_REAL,
	TOKEN_DIV,
	TOKEN_MUL,
	TOKEN_EQUAL,
	TOKEN_PROGRAM_KEYWORD,
	TOKEN_END_KEYWORD,
	TOKEN_REAL_KEYWORD,
	TOKEN_INTEGER_KEYWORD,
	TOKEN_VOID_KEYWORD,
	TOKEN_RETURN_KEYWORD,
	TOKEN_COMMA,
	TOKEN_SEMICOLON,
	TOKEN_BARACKETS_OPEN,
	TOKEN_BARACKETS_CLOSE,
	TOKEN_BRACES_OPEN,
	TOKEN_BRACES_CLOSE,
	TOKEN_PARENTHESES_OPEN,
	TOKEN_PARENTHESES_CLOSE,
	TOKEN_ID,
	TOKEN_EOF
	/*
		Examples of tokens, add/change according to your needs.
		
		Alternative way to define tokens:
		#define TOKEN_INTEGER 1
		#define TOKEN_IF 2
		...........
	*/
}eTOKENS;

typedef struct Token
{
	eTOKENS kind;
	char *lexeme;
	int lineNumber;
}Token;

typedef struct Node
{
	Token *tokensArray;
	struct Node *prev;
	struct Node *next;
} Node;

extern Node* currentNode;
void create_and_store_token(eTOKENS kind, char* lexeme, int numOfLine);
Token *next_token();
Token *back_token();
eTOKENS handle_token(eTOKENS kind, char* lexeme, int numOfLine);
void free_tokens();

#endif