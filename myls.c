#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include "myls.h"
// Citation: https://stackoverflow.com/questions/3554120/open-directory-using-c
bool flags[3]; // -i, -l, -R



int main (int argc, char *argv[]) {
	flags[0],flags[1],flags[2] = false; // -i, -l, -R
	char* test = "kappa";
	printf("TestText2\n");
	parseOption(test);
}



void processArgs(int argc, char *argv[]) {
	// poop
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
