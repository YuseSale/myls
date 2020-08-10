#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include "myls.h"
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

// Citation: https://stackoverflow.com/questions/3554120/open-directory-using-c
bool flags[3] = {false}; // -i, -l, -R



int main (int argc, char *argv[]) {


	processArgs(argc, argv);

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

void processArgs(int argc, char *argv[]) {
	bool noEntry = true;			//determines if the user provided an entity to list.
									//if no entity is provided, list out the current directory.

	int entityQueueMax = 10;
	char** entityQueue = malloc(entityQueueMax*8);
	int entityQueueCount = 0;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {	//if an argument begins with '-'
			if (!noEntry){			//an option was passed after an entity. treat it as an entity
				printf("DEBUG: %s treated as a file\n",argv[i]);
				if (entityQueueCount == entityQueueMax) {
				entityQueueMax = entityQueueMax * 2;
				entityQueue = realloc(entityQueue, entityQueueMax*8);
				}
				if (argv[i][0] != '.') {

					entityQueue[entityQueueCount] = argv[i];
					entityQueueCount++;
				}
			}else{					//treat the argument as an option.
				parseOption(argv[i]);
			}

		} else {
			noEntry = false;		//a non-option argument was provided. Treat it as an entity
			// if (flags[2]) {
			// 	printf("%s:\n", argv[i]);
			// }

			//add that entity to an entity queue.
			if (entityQueueCount == entityQueueMax) {
				entityQueueMax = entityQueueMax * 2;
				entityQueue = realloc(entityQueue, entityQueueMax*8);
			}
			if (argv[i][0] != '.') {
					entityQueue[entityQueueCount] = argv[i];
					entityQueueCount++;
				}
		}
	}

	if (noEntry) {					//no entities were provided. This may have because the used simply called "myls", or passed only options. "call myls on current directory"
		printf("%s: \n", ".");
		readDirectory(".");
		return;
	}else{
		for (int i = 0; i<entityQueueCount;i++){
		}
		LexiSort(entityQueue,entityQueueCount);
		for (int i = 0; i<entityQueueCount;i++){
		}
		for (int i = 0; i < entityQueueCount; i++) {

			readEntity(entityQueue[i],entityQueueCount);
		}
	}

}

void parseOption(char* option) {

	for (int i = 0; i <strlen(option); i++){

		switch (option[i]){
			case 'i':{
				flags[0] = true;
				//printf("DEBUG: Changed Flag -i to true. \n");
				break;
			}
			case 'l':{
				flags[1] = true;
				//printf("DEBUG :Changed Flag -l to true. \n");
				break;
			}
			case 'R':{
				flags[2] = true;
				//printf("DEBUG: Changed Flag -R to true. \n");
				break;
			}
		}
	}
}

//checks if an entity is a file or a directory.
//does the appropriate action.
//returns false if readEntity attempts to read a file/directory that doesnt exist.
void readEntity (char* entityPath, int entityQueueCount) {

	DIR *pDir;

	// Check if dir itself is an accessable directory
	pDir = opendir(entityPath);
	if (pDir == NULL) {
		readFile(entityPath);
	} else{
		if ((entityQueueCount != 1) && (!flags[2])){			//prints the name of the directory, unless only one directory is going to be listed.
			printf("%s: \n", entityPath);
		}
		readDirectory(entityPath);
	}

}

void readDirectory(char* entityPath){

	int entityQueueMax = 10;
	//struct dirent* entityQueue[entityQueueMax];
	struct dirent** entityQueue = malloc(entityQueueMax*8);
	int entityQueueCount = 0;
	struct dirent* pDirent;
	DIR *pDir;


	char* dirQueue[entityQueueMax];
	int dirQueueCount = 0;

	pDir = opendir(entityPath);
	while ((pDirent = readdir(pDir)) != NULL) {
		// Check if entityQueue is full
		if (entityQueueCount == entityQueueMax) {
			entityQueueMax = entityQueueMax * 2;
			entityQueue = realloc(entityQueue, entityQueueMax*8);
		}
		if (pDirent->d_name[0] != '.') {
			entityQueue[entityQueueCount] = pDirent;
			entityQueueCount++;
		}
	}

	sortEntityQueue(entityQueue,entityQueueCount);

	for (int i = 0; i < entityQueueCount; i++) {

		// Create string for full file path
		char* fullDir = malloc(255);

		strcpy(fullDir, entityPath);
		strcat(fullDir, "/");
		strcat(fullDir, entityQueue[i]->d_name);

		// print the entity
		//TODO: Call print function (entityQueue[i], fullDir);
		printEntity(entityQueue[i], fullDir);

		if (flags[2]){



			// Check if the entity was an accessible directory
			pDir = opendir(fullDir);

			if (pDir != NULL) {
				// This is an accessable directory, enqueue it
				dirQueue[dirQueueCount] = fullDir;
				dirQueueCount++;
			}
		}

	}
	if (entityQueueCount != 0){
		printf("\n"); //newline after everything is done printing.
	}

	if (flags[2]) {	//read the dirQueue, call readDirectory on all directories in dirQueue
		for (int i = 0; i < dirQueueCount; i++) {
			printf("\n%s:\n", dirQueue[i]);
			readDirectory(dirQueue[i]);
		}
	}

	// Free all malloced memory
	free(entityQueue);
	for (int i = 0; i < dirQueueCount; i++) {
		free(dirQueue[i]);
	}

	return;
}
// Given an entity, and its full path,
//   checks flags and prints accordingly
void printEntity(struct dirent* entity, char* fullDir) {
	struct stat entityStat;

	if (flags[0]) {
		printf("%ld ", entity->d_ino);
	}

	if (flags[1]) {

		stat(fullDir, &entityStat);
		if (S_ISDIR(entityStat.st_mode)) {
			printf("d");
		} else {
			printf("-");
		}
		if (entityStat.st_mode && S_IRUSR) {
			printf("r");
		} else {
			printf("-");
		}
		if (entityStat.st_mode && S_IWUSR) {
			printf("w");
		} else {
			printf("-");
		}
		if (entityStat.st_mode && S_IXUSR) {
			printf("x");
		} else {
			printf("-");
		}
		if (entityStat.st_mode && S_IRGRP) {
			printf("r");
		} else {
			printf("-");
		}
		if (entityStat.st_mode && S_IWGRP) {
			printf("w");
		} else {
			printf("-");
		}
		if (entityStat.st_mode && S_IXGRP) {
			printf("x");
		} else {
			printf("-");
		}
		if (entityStat.st_mode && S_IROTH) {
			printf("r");
		} else {
			printf("-");
		}
		if (entityStat.st_mode && S_IWOTH) {
			printf("w");
		} else {
			printf("-");
		}
		if (entityStat.st_mode && S_IXOTH) {
			printf("x");
		} else {
			printf("-");
		}
        printf(" ");
		// Print the number of hard links
		printf("%ld ", entityStat.st_nlink);

		// Print user-name of file owner
		struct passwd *pw = getpwuid(entityStat.st_uid);
		printf("%s ", pw->pw_name);

		// Print group name of the file owner
		pw = getpwuid(entityStat.st_gid);
		printf("%s ", pw->pw_name);

		//Print the size of the file (bytes)
		printf("%ld ", entityStat.st_size);

		// Print the date & time file was last modified
		time_t rawtime = entityStat.st_mtime;
		struct tm* timeinfo;
		timeinfo = localtime(&rawtime);
        char* str = asctime(timeinfo);
        str[strlen(str)-1] = 0;
		printf("%s ", str);

		//printf("%ld ", entityStat.st_mtime);
	}

	printf("%s\n", entity->d_name);


}

//given the path to a File, check if that file actually exists
//if the file exists: print that file's name;
void readFile(char* entityPath){

	if (access(entityPath, F_OK) == -1){
		//Error Code Stuff
		printf("myls: cannot access file '%s': no such file or directory\n", entityPath);

		return;
	} else {
		printf("%s\n", entityPath);
		return;
	}

}

void testLexiSort(){
	char* table[8]= {"word", "that", "is","safe","for","kids","to","read"};
	for (int i = 0; i <8; i++){
		printf("%i: %s\n", i, table[i]);
	}
	printf("Sorting....\n");
	LexiSort(table,8);
}

void LexiSort(char* table[],int numOfEntries){
// void LexiSort(char table[][MAX_WORD_LENGTH],int numOfEntries){

	char lowest[MAX_WORD_LENGTH] = "";
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
		if (i == strlen(second)){
			return false;
		}
		else if (i == strlen(first)){
			return true;
		}
	}
}


void sortEntityQueue(struct dirent** entityQueue,int numOfEntries) {
	char lowest[MAX_WORD_LENGTH] = "";
	int lowestIndex;
	for (int i = 0; i<numOfEntries;i++){
		strcpy(lowest,entityQueue[i]->d_name);
		lowestIndex=i;

		for (int j = i; j<numOfEntries; j++){
			if (isLower(entityQueue[j]->d_name ,lowest)){

				strcpy(lowest, entityQueue[j]->d_name );
				lowestIndex=j;
			}
		}

		struct dirent* lowestEntity = entityQueue[lowestIndex];


		entityQueue[lowestIndex] = entityQueue[i];
		entityQueue[i] = lowestEntity;
	}


}
