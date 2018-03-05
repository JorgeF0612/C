/*
	@author		Jorge Felix
	@course		Sys. Prog.
	@assignment	Lab6_prt2
	@lab		Write xref3 to accept optinal keyword command line args for input & output file names.
			Test with:  xref3 [Done]
			            xref3 -i in.txt [Done]
				    xref3 -o out.txt [Done]
				    xref3 -i in.txt -o out.txt [Done]
				    xref3 -o out.txt -i in.txt [Done]
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
	@filename1 is the file that will be read.
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
	Reads & Write 
	@filename1 is the file that will be read
	sfilename2 is the file that will be written on
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
		printf("The file %s does not exist\n", filename1);
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
	Write from cli to a file 
	@filename1 is that file that will be written on
*/ 
void writeIn(char* filename1){
	fp = fopen(filename1, "w");
	char ch[BUF];
	scanf("%s", ch);
	fputs(ch, fp);
	fclose(fp);
}
int main( int argc, char *argv[] ){
	if(argc <= 1){
		printf("copy\n");
		copy();
	}else if( argc <= 2 ){
		if(strcmp(argv[1], "-i")== 0 ){
			printf("Bad Input: -i needs file name");
		}else if(strcmp(argv[1], "-o") == 0){
			printf("Bad Input: -o needs a file name");
		}else{
			printf("Bad Input: incorrect input\n");
		}
	}else if( argc <= 3 ){
		if(strcmp(argv[1], "-i") == 0){
			readOutput(argv[2]);
		}else if(strcmp(argv[1], "-o") == 0){
			writeIn(argv[2]);
		}
	}else if(argc <= 4){
		printf("Missing an extra argument\n");
	}else if(argc <= 5){
		if(strcmp(argv[1], "-i") == 0){
			if(strcmp(argv[3], "-o") == 0){
				readWrite(argv[2], argv[4]);
			}
		}else if(strcmp(argv[1], "-o") ==0){
			if(strcmp(argv[3], "-i") == 0){
				readWrite(argv[4], argv[2]);
			}
		}
	}else if(argc > 5){
		printf("Way to many args \n");
	}
		return 0;
}
