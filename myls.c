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


	testParseOption();
	testFlags();
	
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
	// poop777
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
