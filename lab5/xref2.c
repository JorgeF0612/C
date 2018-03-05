/*
	@author		Jorge Felix
	@course		Sys. Prog.
	@assignment	Lab6_prt2
	@lab		Write xref2 to accept optional positional command line:
			If not files are provided read from stdin and write to stdout [Done]
			If one file is provided, read from it and write to stdout     [Done]
			If two files are provided, read from the first file and write to the second [Done]
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF 100000
FILE *fp;
FILE *fp2;
char ch;

/*
	Read & Output 
	@filename1 is the file that will be read 
*/
void readOutput(char* filename1){
	if(fp = fopen(filename1, "r")){			
		while(1){
			ch = fgetc(fp);
			if(feof(fp)){
				break;
			}else{
				fprintf(stdout, "%c" , ch);
			}
		}
	fclose(fp);	
	}else if(!(fp)){
		printf("File does not exist\n");		
	}
}
/* 
	Reads & Writes
	@filename1 is the filename that will be read
	@filename2 is the filename that will be written on
*/
void readWrite(char* filename1, char* filename2){ 
   	if(fp = fopen(filename1, "r")){
   		fp2 = fopen(filename2, "w");		
		while (1) {
			ch = fgetc(fp);
			if (feof(fp)){
				break;
			}else{
				fputc(ch, fp2);
			}
		} 
   		fclose(fp);
   		fclose(fp2);
	}else if(!(fp)){
		printf("The file %c does not exist");
	}
}
/* Copy input from cli and output it */
void copy(){
	int size = BUF;
	char words[size];
	fgets(words, size, stdin);
	fprintf(stdout, "%s" , words);
}
/* 
	@argc counts & handles the arguments 
	@argv handles the actually word
*/
int main( int argc, char *argv[] ){
	if(argc <= 1){ 				/* If one arguments go to copy */
		copy(); 
	}else if( argc <= 2 ){ 			/* If two arguments go to readOutput */
		readOutput(argv[1]);
	}else if( argc <= 3 ){			/* If three arguments go to readwrite */
		readWrite(argv[1], argv[2]);
	}else if(argc > 3){			/* If more than three arguments, print it out */
		printf("Way to many args \n");
	}
		return 0;
}
