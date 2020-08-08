#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>

// Citation: https://stackoverflow.com/questions/3554120/open-directory-using-c
bool flags[3] = {false}; // -i, -l, -R

int main (int argc, char *argv[]) {

	processArgs(argc, argv);

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
	printf("Received option: %s\n",option)
}

void printFiles(char* dir) {

	printf("Received dir: %s\n", dir);


}
