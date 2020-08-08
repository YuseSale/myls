#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>

// Citation: https://stackoverflow.com/questions/3554120/open-directory-using-c
bool flags[3]; // -i, -l, -R

int main (int argc, char *argv[]) {

	flags[] = {false, false, false}; // -i, -l, -R
	
}

void processArgs(int argc, char *argv[]) {
	
}

void parseOption(char* option) {
	
}

void printFiles(char* dir) {
	struct dirent *pDirent;
	DIR *pDir;
	
	// Ensure we can open directory.
    pDir = opendir (fileList[i]);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", argv[1]);
            return 1;
        }
	}
	
	// print file index (iNode number)
	printf("%ld ", pDirent->d_ino);
	
	// Print file name
	printf ("%s", pDirent->d_name);
	
	closedir (pDir);
}
