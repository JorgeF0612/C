#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define MAXWORD 100
#define BUFSIZE 100
#define TRUE 0
#define FALSE 1


/* Structure for tree nodes
*/
struct tnode {
/* Pointer for the text */	
	char *word;  
/* Frequency of occurence */	
	int line; 
/* Descendant (left) */
	struct tnode *left; 
/* Descendant (right) */
	struct tnode *right;
};

static int fileLine = 1;
/* Buffer used for ungetch */
char buf[BUFSIZE];
/* Position in the buffer */
int bufp = 0;                         

char isnewlinespace(unsigned char c) {
	if ( c == ' ' || c == '\f' || c == '\r' || c == '\t' || c == '\v') 
		return 1;
	else
		return 0;
}

/* Gets the next word or character from input
** @param word Pointer to the word being gotten
** @param lim Limits the size of the word
** @return The word's first character for sorting
*/
int getword(char *word, int lim) {
	int c, getch(void);
	void ungetch(int);
	char *w = word;

    while (isnewlinespace(c = getch()))
        ;
		if(c != EOF)
			*w++ = c;
			/* Line character, increment line */
		if (c == '\n') {
			++fileLine;
		}
		if(!isalpha(c)) {
			*w = '\0';
			return c;
		}
	for(; --lim > 0; w++) {
		if(!isalnum(*w = getch())) {
		ungetch(*w);
		break;
		}
	}
	*w = '\0';
	return word[0];
}
/* Get data from the buffer
** @return The next data from the buffer
*/
int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Puts data back onto the buffer
** @param c Data put back onto the buffer
*/
void ungetch(int c) {
	if(bufp >= BUFSIZE)
		printf("ERROR: Too much data to ungetch\n");
	else
		buf[bufp++] = c;
}

/* Checks if this word is a data type word
** @param s Pointer to the word being checked
** @return TRUE if is data type word, else FALSE
*/
int datatypeWord(char *s) {
	int found = FALSE;
	int giveup = 0;

	char *list[] = {"char", "double",
					"float", "int",
					"long", "short",};
					
	int top = sizeof list / sizeof list[0] - 1;
	int bottom = 0;
	int guess = top / 2;
	int diff = 0;

	if(s != NULL) {
		while(found && !giveup) {
			diff = strcmp(list[guess], s);
			if(0 == diff) {
				found = TRUE;
			} else if(0 < diff) {
				top = guess - 1;
			} else {
				bottom = guess + 1;
			}
			if(top < bottom) {
				giveup = 1;
			} else {
				guess = (top + bottom) / 2;
			}
		}
	}
	return found;
}

int validIdentifier(char *str) {
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' || 
        str[0] == '6' || str[0] == '7' || str[0] == '8' || 
        str[0] == '9') {
        return FALSE;
	} else {
		return TRUE;
	}
}
/* Creates and allocates the memory for a new tree node
** @return The created tree node
*/
struct tnode *talloc(void) {
	return(struct tnode *)malloc(sizeof(struct tnode));
}

/* Create or add a tree node in relation to the given tree node
** @param p Pointer to the current tree node being calculated from
** @param w Pointer t the word being added into the tree node
*/									   
struct tnode *addtree(struct tnode *p, char *w) {
	int cond;
	/* New word found */
	if(p == NULL) {
		p = talloc();                        
		p ->word = strdup(w);
		p ->line = fileLine;
		p -> left = p->right = NULL;
	/* Sorted left */
	} else if((cond = strcmp(w, p -> word)) < 0) {                     
		p -> left = addtree(p -> left, w);
	/* Sorted right */
	} else {
		p -> right = addtree(p -> right, w);
	}
	return p;
}

/* Prints the tree using inorder traversal
** @param p Pointer to the root tree node being traversed from
*/									   
void treeprint(struct tnode *p) {
	if(p != NULL) {
		treeprint( p -> left);
		printf("%4d %s\n", p -> line, p -> word);
		treeprint(p -> right);
	}
}

int main(void) {                      
	struct tnode *root;
	char word[MAXWORD];
	root = NULL;
	
	while(getword(word, MAXWORD) != EOF) {
		if (datatypeWord(word) == TRUE) {
			if (getword(word, MAXWORD) != EOF) {
				if(isalpha(word[0])) {
					root = addtree(root, word);
				}
			}
		}
	}
	treeprint(root);
	exit(0);
}