#include "Token.h"

/* This package describes the storage of tokens identified in the input text.
* The storage is a bi-directional list of nodes.
* Each node is an array of tokens; the size of this array is defined as TOKEN_ARRAY_SIZE.
* Such data structure supports an efficient way to manipulate tokens.

There are three functions providing an external access to the storage:
- function create_and_store_tokens ; it is called by the lexical analyzer when it identifies a legal token in the input text.
- functions next_token and back_token; they are called by parser during the syntax analysis (the second stage of compilation)
*/

int currentIndex = 0;
Node* currentNode = NULL;

int backT_flag = 0;

#define TOKEN_ARRAY_SIZE 100

/*
* This function creates a token and stores it in the storage.
*/
void create_and_store_token(eTOKENS kind, char* lexeme, int numOfLine)
{ 
	int length = strlen(lexeme)+1;
	
	// case 1: there is still no tokens in the storage.
	if (currentNode == NULL)
	{
		currentNode = (Node*)malloc(sizeof(Node));

		if(currentNode == NULL)
		{
			fprintf(yyout,"\nUnable to allocate memory! \n"); 
			exit(0);
		}
		currentNode->tokensArray = (Token*)calloc(sizeof(Token),TOKEN_ARRAY_SIZE);
		if(currentNode->tokensArray == NULL)
		{
			fprintf(yyout,"\nUnable to allocate memory! \n"); 
			exit(0);
		}
		currentNode->prev = NULL;
		currentNode->next = NULL;
	}

	// case 2: at least one token exsits in the storage.
	else
	{
		// the array (the current node) is full, need to allocate a new node
		if (currentIndex == TOKEN_ARRAY_SIZE - 1)
		{
			currentIndex = 0;
			currentNode->next = (Node*)malloc(sizeof(Node));

			if(currentNode == NULL)
			{
				fprintf(yyout,"\nUnable to allocate memory! \n"); 
				exit(0);
			}
			currentNode->next->prev = currentNode;
			currentNode = currentNode->next;
			currentNode->tokensArray = (Token*)calloc(sizeof(Token),TOKEN_ARRAY_SIZE);

			if(currentNode->tokensArray == NULL)
			{
				fprintf(yyout,"\nUnable to allocate memory! \n"); 
				exit(0);
			}
			currentNode->next = NULL;
		}

		// the array (the current node) is not full
		else
		{
			currentIndex++;
		}
	}

	currentNode->tokensArray[currentIndex].kind = kind;	
	currentNode->tokensArray[currentIndex].lineNumber = numOfLine;

	currentNode->tokensArray[currentIndex].lexeme = (char*)malloc(sizeof(char)*length);
	#ifdef _WIN32
		strcpy_s(currentNode->tokensArray[currentIndex].lexeme, length, lexeme);
	#else
		strcpy(currentNode->tokensArray[currentIndex].lexeme, lexeme);
	#endif		
}

/*
* This function returns the token in the storage that is stored immediately before the current token (if exsits).
*/
Token *back_token() { 
	if(currentIndex != 0){ //atleast two tokens
		backT_flag++;
		currentIndex--;
		return &currentNode->tokensArray[currentIndex];
	}
	else{
		if(currentNode->prev != NULL){
			backT_flag++;
			currentIndex = 99;
			currentNode = currentNode->prev;
			return  &currentNode->tokensArray[currentIndex];//last token in the prev array
		}
	}
	return NULL;//no token to return
}

/*
* If the next token already exists in the storage (this happens when back_token was called before this call to next_token): 
*  this function returns the next stored token.
* Else: continues to read the input file in order to identify, create and store a new token (using yylex function);
*  returns the token that was created.
*/
Token *next_token() {

	if(backT_flag){//back_token was called before this call
		backT_flag--;
		if(currentIndex == 99){
			currentIndex = 0;
			currentNode = currentNode->next;
			//fprintf(yyout, "\n lex:%s \n", currentNode->tokensArray[currentIndex].lexeme);
			return &currentNode->tokensArray[currentIndex];
		}
		currentIndex++;
		//fprintf(yyout, "\n lex:%s \n", currentNode->tokensArray[currentIndex].lexeme);
		return &currentNode->tokensArray[currentIndex];
	}

	yylex();
	//fprintf(yyout, "\n lex:%s \n", currentNode->tokensArray[currentIndex].lexeme);
	return &currentNode->tokensArray[currentIndex];
}

eTOKENS handle_token(eTOKENS kind, char* lexeme, int numOfLine){
	
	create_and_store_token(kind, lexeme, numOfLine);

	return kind;
}

void free_tokens(){
	Node* head = currentNode;
	Node* next;
	int i = 0;

	currentNode = NULL;
	currentIndex = 0;
	while (head -> prev){
		head = head -> prev;
	}

	while(head){
		next = head -> next;

		while(head ->tokensArray[i].lexeme && i < TOKEN_ARRAY_SIZE){
			//free(head ->tokensArray[i].lexeme);
			i++;
		}
		free(head ->tokensArray);
		free(head);
		head = next;
	}

	return;
}
