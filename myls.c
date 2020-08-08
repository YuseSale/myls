#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
// Citation: https://stackoverflow.com/questions/3554120/open-directory-using-c

int main (int argc, char *argv[]) {
	struct dirent *pDirent;
	DIR *pDir;
	bool iNode = false; // -i
	bool longList = false; // -l
	bool recursive = false; // -R
	char * options [] = { "-i", "-l", "-R", "-il", "-iR", "-li", "-lR", "-Ri", "-Rl", "-ilR", "-iRl", "-liR", "-lRi", "-Ril", "-Rli"};
	char ** fileList = NULL;
	/*printf("Your arguments: ");
	for (int i = 1; i < argc; i++) {
		printf(" %s,", argv[i]);
	}
	printf("\n");*/
	//printf("argc: %d\n", argc);
	// Get options argument
	int opCount = 0;
	for (int i = 1; i < argc; i++) {
		// Process every argument
		if (argv[i][0] == '-') {
			// This is an option
			opCount++;
			for (int j = 0; j < 15; j++) {
				if (strcmp(argv[i], options[j])==0) {
					//argv[i] is a valid option
					if (strstr(argv[i],"i") != NULL) {
						iNode = true;
					}
					if (strstr(argv[i],"l") != NULL) {
						longList = true;
					}
 					if (strstr(argv[i],"R") != NULL) {
 						recursive = true;
					}
				}
			}
		} else {
			// This is a file/directory

			// At this point, we know how many [options] & how many [file list]
			// Malloc space for queue of dirs to list
			if (fileList == NULL) {
				fileList = malloc((argc-1-opCount)*8);
			}

			// Append argv[i] to queue of dirs to list
			fileList[i-(opCount+1)] = argv[i];
		}
	}
	/*
	printf("Options: \n");
	printf("   -i : %d\n", iNode);
	printf("   -l : %d\n", longList);
	printf("   -R : %d\n", recursive);

	printf("\nDirectories to list: \n");
	for (int i = 0; i < (argc-1-opCount); i++) {
		printf("   %s\n", fileList[i]);
	}

	*/

	// In case Just ./myls was called
	if (argc == 1) {

		// Ensure we can open directory.
		pDir = opendir (".");
		if (pDir == NULL) {
			printf ("Cannot open directory '%s'\n", ".");
			return 1;
		}

		// Process each entry.

		while ((pDirent = readdir(pDir)) != NULL) {

			//printf("id: %d\n",pDirent->d_ino->st_ino);
			printf ("%s  ", pDirent->d_name);
		}
		printf("\n");
		// Close directory and exit.

		closedir (pDir);
		printf("\n");
	} else {

		for (int i = 0; i < (argc-1-opCount); i++) {

			printf("Listing directory: [%s]\n\n", fileList[i]);

			// Ensure we can open directory.
			pDir = opendir (fileList[i]);
			if (pDir == NULL) {
				printf ("Cannot open directory '%s'\n", argv[1]);
				return 1;
			}

			// Process each entry.

			while ((pDirent = readdir(pDir)) != NULL) {

				//printf("id: %d\n",pDirent->d_ino->st_ino);
				printf ("%s  ", pDirent->d_name);
			}
			printf("\n");
			// Close directory and exit.

			closedir (pDir);
			printf("\n");

		}

	}

	return 0;

}

void lexSort(char ** dirs, int n) {

	// Sorts array of strings of size n lexicographically
	char* myDirs[n];

	return;

}
