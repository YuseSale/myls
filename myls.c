#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include "myls.h"
// Citation: https://stackoverflow.com/questions/3554120/open-directory-using-c
bool flags[3] = {false}; // -i, -l, -R
// test3


int main (int argc, char *argv[]) {
	processArgs(argc, argv);
}



void processArgs(int argc, char *argv[]) {
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
	// struct dirent *pDirent;
	// DIR *pDir;

	// // Ensure we can open directory.
    // pDir = opendir (fileList[i]);
    // if (pDir == NULL) {
    //     printf ("Cannot open directory '%s'\n", argv[1]);
    //         return 1;
    //     }
	// }

	// // print file index (iNode number)
	// printf("%ld ", pDirent->d_ino);

	// // Print file name
	// printf ("%s", pDirent->d_name);

	// closedir (pDir);
}
