#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void readOutput(char* filename1){
		FILE *fp;
		char buff[10000];

		if((fp = fopen(filename1, "r"))){
			//printf("file found");
			fscanf(fp, "%s", buff);
			printf("%s\n", buff );
		}else{
			printf("File does not exist");
		}
		
	
		
		fclose(fp);
}
void readWrite(char* filename1, char* filename2){
   FILE *fp1, *fp2;
   char ch;
 
   fp1 = fopen(filename1, "r");
   fp2 = fopen(filename2, "w");
 
   while (1) {
		ch = fgetc(fp1);
		if (ch == EOF){
			break;
		}else{
			putc(ch, fp2);
		}
   }
   fclose(fp1);
   fclose(fp2);
}
void copy() {
	//it should copy
    }


int main( int argc, char *argv[] ){
		int n = 0;
		if(argc <= 1){
			printf("read and paste\n");
			copy();
		} else if( argc <= 2 ){
			printf("read and output\n");
			readOutput(argv[1]);
			//printf("%s\n",argv[1]);
		} else if( argc <= 3 ){
			printf("read and write\n");	
			readWrite(argv[1], argv[2]);
		}
		else if(argc > 3){
			printf("Way to many args \n");
		}
		
		return 0;
}

//while(n <= 1){
			//	if(argv[n]){
					/*
					if(strcmp(argv[n], "-i") == 0){
						printf("found dash i: ");
					}
					if(strcmp(argv[n], "-o") == 0){
						printf("found dash o: ");
					}*/

