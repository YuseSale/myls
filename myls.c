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



void processArgs(int argc, char *argv[]) {

	// Just ./myls
	if (argc == 1) {
		printFiles(".");
		return;
	}

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			parseOption(argv[i]);
		} else {
			printFiles(argv[i]);
		}
	}
}

void parseOption(char* option) {
	printf("TestText\n");
	printf("%s\n",option);
	for (int i = 0; i <strlen(option); i++){
		printf("%c\n", option[i]);
	}
}

void printFiles(char* dir) {
	// Given a directory path, print all files & folders in the directory

	struct dirent *pDirent;
	DIR *pDir;

	// Ensure we can open directory.
	// If can't, it's a file, so just print it
	pDir = opendir(dir);
	if (pDir == NULL) {
		printf("%s", dir);
		return;
	}

	// Print all files in the directory
	// If subdirectories found, recursively print em
	while((pDirent=readdir(pDir))!=NULL) {
		printf("%s  ", pDirent->d_name);
	}
	printf("\n");
	// print file index (iNode number)
	//printf("%ld ", pDirent->d_ino);

	closedir (pDir);
}
