#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include "myls.h"
// Citation: https://stackoverflow.com/questions/3554120/open-directory-using-c
bool flags[3] = {false}; // -i, -l, -R


<<<<<<< HEAD
	processArgs(argc, argv);

=======

int main (int argc, char *argv[]) {
	flags[0],flags[1],flags[2] = false; // -i, -l, -R
	char* test = "kappa";
	printf("TestText2\n");
	parseOption(test);
>>>>>>> cadc98c6e4b129417330f9238c8a3623877e669b
}



void processArgs(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		// Check if argv[i] is an option
		if (argv[i][0] == '-') {
			parseOption(argv[i]);
		} else {
			// argv[i] is a directory/file
			printFiles(argv[i]);
		}

	}
}

void parseOption(char* option) {
<<<<<<< HEAD
	printf("Received option: %s\n",option)
}

void printFiles(char* dir) {

	printf("Received dir: %s\n", dir);


=======
	printf("TestText\n");
	for (int i = 0; i <sizeof(option); i++){
		printf("%s\n", option[i]);
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
>>>>>>> cadc98c6e4b129417330f9238c8a3623877e669b
}
