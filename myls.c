#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include "myls.h"
#include <ctype.h>
// Citation: https://stackoverflow.com/questions/3554120/open-directory-using-c
bool flags[3] = {false}; // -i, -l, -R



int main (int argc, char *argv[]) {
	flags[0],flags[1],flags[2] = false; // -i, -l, -R

	// testIsLower();
	testLexiSort(); 
	// // testParseOption();
	// // testFlags();
	// char* testArray[] = {"apple","banana","candy","Text","colin","table"};
	// // processArgs(argc, argv);


	return 0;
}
void testIsLower(){
	char test1[MAX_WORD_LENGTH] = "";
	printf("Enter a word: ");

    scanf("%s", test1);  
	char test2[MAX_WORD_LENGTH] = "";
	printf("Enter a word: ");

    scanf("%s", test2);
	if (isLower(test1,test2)) {
		printf("[%s < %s\n]",test1,test2);
	} else{
		printf("[%s < %s]\n",test2,test1);
	}
}
void testParseOption(){
	char test[MAX_WORD_LENGTH] = "";
	printf("Enter a word: ");

    scanf("%s", test);  
	parseOption(&test[0]);
	
}
void testFlags(){
	printf("-i flag: %d\n",flags[0]);
	printf("-l flag: %d\n",flags[1]);
	printf("-R flag: %d\n",flags[2]);
}

// void processArgs(int argc, char *argv[]) {

// 	// Just ./myls
// 	if (argc == 1) {
// 		printFiles(".");
// 		return;
// 	}

// 	for (int i = 1; i < argc; i++) {
// 		if (argv[i][0] == '-') {
// 			parseOption(argv[i]);
// 		} else {
// 			printFiles(argv[i]);
// 		}
// 	}
// }

void parseOption(char* option) {

	for (int i = 0; i <strlen(option); i++){

		switch (option[i]){
			case 'i':{
				flags[0] = true;
				printf("DEBUG: Changed Flag -i to true. \n");
				break;
			} 
			case 'l':{
				flags[1] = true;
				printf("DEBUG :Changed Flag -l to true. \n");
				break;
			} 
			case 'R':{
				flags[2] = true;
				printf("DEBUG: Changed Flag -R to true. \n");
				break;
			} 
		}
		
	}
}

// void printFiles(char* dir) {
// 	// Given a directory path, print all files & folders in the directory

// 	struct dirent *pDirent;
// 	DIR *pDir;

// 	// Ensure we can open directory.
// 	// If can't, it's a file, so just print it
// 	pDir = opendir(dir);
// 	if (pDir == NULL) {
// 		printf("%s", dir);
// 		return;
// 	}

// 	// Print all files in the directory
// 	// If subdirectories found, recursively print em
// 	while((pDirent=readdir(pDir))!=NULL) {
// 		printf("%s  ", pDirent->d_name);
// 	}
// 	printf("\n");
// 	// print file index (iNode number)
// 	//printf("%ld ", pDirent->d_ino);

// 	closedir (pDir);
// }

void readDirectory (char* dir) {
	struct dirent* entityQueue[10];
	struct dirent* pDirent;
	DIR *pDir;
}
void testLexiSort(){
	char table[8][MAX_WORD_LENGTH] = {"word", "that", "is","safe","for","kids","to","read"};


	for (int i = 0; i <8; i++){
		printf("%i: %s\n", i, table[i]);
	}
	printf("Sorting....\n");
	LexiSort(table,8);

}


void LexiSort(char table[][MAX_WORD_LENGTH],int numOfEntries){	

	char lowest[40] = "";
	int lowestIndex;
	for (int i = 0; i<numOfEntries;i++){
		strcpy(lowest,table[i]);


		lowestIndex=i;

		for (int j = i; j<numOfEntries; j++){
			if (isLower(table[j],lowest)){
				
				strcpy(lowest, table[j]);
				lowestIndex=j;
			}
		}


		strcpy(table[lowestIndex],table[i]);
		
		strcpy(table[i], lowest);
		
	}

	for (int i = 0; i <numOfEntries; i++){
		printf("%i: %s\n", i, table[i]);
	}
}
//tests if 'first' is lexicographically smaller than 'second'
bool isLower(char* first, char* second){
	for (int i = 0; i < strlen(first) || i <strlen(second); i++){
		if (tolower(first[i])<tolower(second[i])){
			return true;
		}
		else if (tolower(first[i])>tolower(second[i])){
			return false;
		}
		else if (i = strlen(second)){
			return false;
		}
		else if (i = strlen(first)){
			return true;
		}
		
	}


	
}			


void sortEntityQueue(struct dirent* entityQueue) {

}
