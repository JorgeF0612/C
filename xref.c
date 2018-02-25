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
#define F       0
#define T       1
#define N       NULL
#define Z       0
#define O       1
#define MXWORD  100000
#define BUFSIZE 100000

int cLine    = O;
int bufferp  = Z;
char buffer[BUFSIZE];
/* Tree Node */
struct tnode{	
	char *word;  	
	int line; 
	struct tnode *left; 
	struct tnode *right;
};
/* Detects when there's: 'space', '\f', '\r', '\t', '\v' */
char isspaceL( char i ){
	if ( i == ' ' || i == '\f' || i == '\r' || i == '\t' || i == '\v'){ return T; } else{ return F; }
}
/* Gets next/word */
int getWord( char *word, int lim ){
	int c;
	int getch(void);
	void ungetch(int);
	char *wrd = word;
	while(isspaceL( c = getch()))
        ;
		if(c != EOF){ *wrd++ = c;}
		if(c == '\n'){ ++cLine;}
		if(!isalpha(c)){ *wrd = '\0'; return c; }
	for(; --lim > Z; wrd++) {
		if(!isalnum(*wrd = getch())){ ungetch(*wrd); break; }
	} *wrd = '\0';
	return word[Z];
}
/* Gets data from buffer */
int getch( void ){ return (bufferp > Z) ? buffer[--bufferp] : getchar(); }
/* Puts data into buffer */
void ungetch( int c ){
	if(bufferp >= BUFSIZE){ 
		printf("ERROR: cant get, size to big \n");
	}else{	buffer[bufferp++] = c; }
}
/* Verifies we have have a datatype */
int dataType( char *wrd ){
	char *dTypes[] = { "char", "double", "float", "int", "long", "short", };
	int loc    = T;
	int stop   = Z;
	int low    = Z;
	int diff   = Z;
	int high   = sizeof dTypes / sizeof dTypes[Z] - O;
	int where  = ( high / 2 );	
	if(wrd != N){
		while(loc && !stop){
			diff = strcmp(dTypes[where], wrd);
			if( Z == diff) { loc    = F; } 
			if( Z < diff ) { high   = where - O;
			}else{ low = where + O; }
			if( high <= ( low - O )) { stop   = O;
			}else{ where  = (( high + low ) / 2); }
		}
	}
	return loc;
}
/* Makes sure that there is a valid Identifier */
int validIdentifier( char *str ){
    	if(isdigit(str[Z])){    return T; }
	if(!(isdigit(str[Z]))){ return F; }
}
/* Manages/Makes memory for tree node */
struct tnode *talloc( void ){ return(struct tnode *)malloc(sizeof(struct tnode)); }
/* Adds a tree node */   
struct tnode *addtree( struct tnode *rt, char *wrd ){
	int cdt;
	if( rt == N ){
		rt = talloc();                        
		rt -> word = strdup(wrd);
		rt -> line = cLine;
		rt -> left = rt -> right = N;
	}else if(( cdt = strcmp(wrd,  rt -> word )) < Z ){
		rt -> left  = addtree(rt -> left, wrd);
	}else{  rt -> right = addtree(rt -> right, wrd); }
	return rt;
}
/* Prints tree in order */
void printTree( struct tnode *rt ){
	if(rt != N){
		printTree( rt -> left  );
		printf("  %4d     %s\n", rt -> line, rt -> word);
		printTree( rt -> right );
	}
}
/* Prints Data */
void prtData( struct tnode *rt ){
	printf("    XREF Utility\n");
	printf("-- Ascending Order --\n");
	printf("   Line | Identifier\n");
	printTree(rt);
}
int main( void ) {                      
	struct tnode *root;
	char word[MXWORD];
	root = N;	
	while( getWord(word, MXWORD) != EOF ){
		if( dataType(word) == F ){
			if( getWord(word, MXWORD) != EOF ) {
				if( isalpha(word[Z])){ root = addtree( root, word ); }
			}
		}
	}
	prtData(root);
	exit(Z);
}
