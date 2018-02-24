/*
   Jorge Felix
   Dr Vail
   Olivet Nazarene University
   Lab_5
   Assignment:
   Write a C cross reference xref that prints a list of indentofiers in a source code file.[Done]
  	- Sort the list of identifiers into asc order. [Done]
        - For each identidentifier, list the line #'s on which it occurs. [Done]
        - Do not print C reserved words, only user defined words. [Done]	

   How to run:
   	./xref < [filename].c
	or 
	xref < [filename].c
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXWORD 100000
#define BUFSIZE 100000
#define FALSE   0
#define TRUE    1

int cLine    = 1;
int bufferp  = 0;
char buffer[BUFSIZE];
/* Tree Node */
struct tnode {	
	char *word;  	
	int line; 
	struct tnode *left; 
	struct tnode *right;
};
/* Detects when there's: 'space', '\f', '\r', '\t', '\v' */
char isspaceL(char c) {
	if ( c == ' ' || c == '\f' || c == '\r' || c == '\t' || c == '\v'){ 
		return 1;
	}else{  return 0; }
}
/* Gets next/word */
int getWord(char *word, int lim) {
	int c;
	int getch(void);
	void ungetch(int);
	char *wrd = word;
	while (isspaceL(c = getch()))
        ;
		if(c != EOF){ *wrd++ = c;}
		if(c == '\n'){ ++cLine;}
		if(!isalpha(c)){ *wrd = '\0'; return c; }
	for(; --lim > 0; wrd++) {
		if(!isalnum(*wrd = getch())){ ungetch(*wrd); break; }
	} *wrd = '\0';
	return word[0];
}
/* Gets data from buffer */
int getch(void){ return (bufferp > 0) ? buffer[--bufferp] : getchar(); }
/* Puts data into buffer */
void ungetch( int c ){
	if(bufferp >= BUFSIZE){ 
		printf("ERROR: cant get, size to big \n");
	}else{	buffer[bufferp++] = c; }
}
/* Verifies we have have a datatype */
int dataType( char *wrd ) {
	char *dTypes[] = { "char", "double", "float", "int", "long", "short", };
	int loc    = TRUE;
	int stop   = 0;
	int low    = 0;
	int diff   = 0;
	int high   = sizeof dTypes / sizeof dTypes[0] - 1;
	int where  = ( high / 2 );	
	if(wrd != NULL) {
		while(loc && !stop) {
			diff = strcmp(dTypes[where], wrd);
			if( 0 == diff) { loc = FALSE;} 
			if( 0 < diff ) {
				high   = where - 1;
			}else{
				low    = where + 1;
			}
			if( high <= ( low - 1 )) {
				stop   = 1;
			}else{
				where  = (( high + low ) / 2);
			}
		}
	}
	return loc;
}
/* Makes sure that there is a valid Identifier */
int validIdentifier(char *str) {
    	if(isdigit(str[0])){    return TRUE; }
	if(!(isdigit(str[0]))){ return FALSE;}
}
/* Manages/Makes memory for tree node */
struct tnode *talloc(void){ return(struct tnode *)malloc(sizeof(struct tnode)); }
/* Adds a tree node */   
struct tnode *addtree(struct tnode *rt, char *wrd) {
	int cdt;
	if( rt == NULL ){
		rt = talloc();                        
		rt -> word = strdup(wrd);
		rt -> line = cLine;
		rt -> left = rt -> right = NULL;
	}else if(( cdt = strcmp(wrd,  rt -> word )) < 0 ){
		rt -> left  = addtree(rt -> left, wrd);
	}else{  rt -> right = addtree(rt -> right, wrd); }
	return rt;
}
/* Prints tree in order */
void printTree(struct tnode *rt) {
	if(rt != NULL){
		printTree( rt -> left  );
		printf("  %4d     %s\n", rt -> line, rt -> word);
		printTree( rt -> right );
	}
}
int main(void) {                      
	struct tnode *root;
	char word[MAXWORD];
	root = NULL;	
	while(getWord(word, MAXWORD) != EOF) {
		if (dataType(word) == FALSE) {
			if (getWord(word, MAXWORD) != EOF) {
				if(isalpha(word[0])){ root = addtree(root, word); }
			}
		}
	}
	printf("    XREF Utility\n");
	printf("-- Ascending Order --\n");
	printf("   Line | Identifier\n");
	printTree(root);
	exit(0);
}
