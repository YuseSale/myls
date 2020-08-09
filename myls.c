#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include "myls.h"
// Citation: https://stackoverflow.com/questions/3554120/open-directory-using-c
bool flags[3] = {false}; // -i, -l, -R



int main (int argc, char *argv[]) {

	processArgs(argc, argv);

	return 0;
}

void testParseOption(){
	char test[20] = "";
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

	// Just ./myls
	if (argc == 1) {
		readDirectory(".");
		return;
	}

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			parseOption(argv[i]);
		} else {
			readDirectory(argv[i]);
		}
	}
}

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

void readDirectory (char* dir) {


	int entityQueueMax = 10;
	//struct dirent* entityQueue[entityQueueMax];
	struct dirent** entityQueue = malloc(entityQueueMax*8);
	int entityQueueCount = 0;
	struct dirent* pDirent;
	DIR *pDir;

	char* dirQueue[entityQueueMax];
	int dirQueueCount = 0;

	// Check if dir itself is an accessable directory
	pDir = opendir(dir);
	if (pDir == NULL) {
		printf("%s", dir);
		return;
	}

	// Read all the entities in dir
	while ((pDirent = readdir(pDir)) != NULL) {

		// Check if entityQueue is full
		if (entityQueueCount == entityQueueMax) {
			//TODO: remalloc bigger array
			entityQueueMax = entityQueueMax * 2;
			entityQueue = realloc(entityQueue, entityQueueMax*8);
		}

		entityQueue[entityQueueCount] = pDirent;
		entityQueueCount++;
	}
	closedir(pDir);

	//sortEntityQueue(entityQueue);

	for (int i = 0; i < entityQueueCount; i++) {

		if (entityQueue[i]->d_name[0] == '.') {
			continue;
		}

		// print the entity
		printf("%s  ", entityQueue[i]->d_name);
		// Create a directory string for it
		char* goDir = malloc(255);

		strcpy(goDir, dir);
		strcat(goDir, "/");
		strcat(goDir, entityQueue[i]->d_name);

		// Check if the entity was an accessible directory
		pDir = opendir(goDir);

		if (pDir != NULL) {
			// This is an accessable directory, enqueue it
			dirQueue[dirQueueCount] = goDir;
			dirQueueCount++;
		}
		closedir(pDir);

	}

	printf("\n\n");

	for (int i = 0; i < dirQueueCount; i++) {
		printf("%s: \n", dirQueue[i]);
		readDirectory(dirQueue[i]);
	}

	// Free all malloced memory
	free(entityQueue);
	for (int i = 0; i < dirQueueCount; i++) {
		free(dirQueue[i]);
	}

	return;
}
