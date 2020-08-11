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
// Some Code Adapted from: https://stackoverflow.com/questions/3554120/open-directory-using-c
bool flags[3] = {false}; // -i, -l, -R

int main(int argc, char *argv[])
{
	processArgs(argc, argv);
	return 0;
}

void processArgs(int argc, char *argv[])
{
	bool noEntry = true; //determines if the user provided an entity to list.
						 //if no entity is provided, list out the current directory.

	int entityQueueMax = 10;
	char **entityQueue = malloc(entityQueueMax * 8);
	int entityQueueCount = 0;

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{ //if an argument begins with '-', check if should be treated as an option of as a list target

			if ((!noEntry) || (strlen(argv[i]) == 1))
			{ //an option was passed after an entity, or the option is just '-'. treat it as an list target

				noEntry = false;
				printf("DEBUG: %s treated as a file\n", argv[i]);
				if (entityQueueCount == entityQueueMax)
				{
					entityQueueMax = entityQueueMax * 2;
					entityQueue = realloc(entityQueue, entityQueueMax * 8);
				}
				if (argv[i][0] != '.')
				{

					entityQueue[entityQueueCount] = argv[i];
					entityQueueCount++;
				}
			}
			else
			{ //treat the argument as an option.

				if (!parseOption(argv[i]))
				{
					free(entityQueue);
					return; //if an invalid option was provided, stop the program.
				}
			}
		}
		else
		{

			noEntry = false; //a non-option argument was provided before this. Treat it as an list target

			//add that entity to an entity queue.
			if (entityQueueCount == entityQueueMax)
			{
				entityQueueMax = entityQueueMax * 2;
				entityQueue = realloc(entityQueue, entityQueueMax * 8);
			}
			entityQueue[entityQueueCount] = argv[i];
			entityQueueCount++;
		}
	}
	//no search targets were provided.
	//call myls on current directory
	if (noEntry)
	{
		free(entityQueue);
		readDirectory(".");
		return;
	}
	else
	{ //Lexicographically sort all elements, then read them.

		LexiSort(entityQueue, entityQueueCount);

		//for the initial Parse args, the files should all be processed before the directories.

		//only read an entity if its a file.
		DIR *pDir;
		for (int i = 0; i < entityQueueCount; i++)
		{
			pDir = opendir(entityQueue[i]);
			if (pDir == NULL)
			{
				readFile(entityQueue[i]);
			}
		}

		//only read a file if its a directory.
		for (int i = 0; i < entityQueueCount; i++)
		{

			pDir = opendir(entityQueue[i]);
			if (pDir != NULL)
			{
				printf("\n");
				if ((entityQueueCount != 1) || (flags[2]))
				{
					printf("%s: \n", entityQueue[i]); //prints the name of the starting directory, unless only one directory is going to be listed.
				}
				readDirectory(entityQueue[i]);
			}
		}

		closedir(pDir);
		free(entityQueue);
	}
}

bool parseOption(char *option)
{

	for (int i = 1; i < strlen(option); i++)
	{

		switch (option[i])
		{
		case 'i':
		{
			flags[0] = true;
			//printf("DEBUG: Changed Flag -i to true. \n");
			break;
		}
		case 'l':
		{
			flags[1] = true;
			//printf("DEBUG :Changed Flag -l to true. \n");
			break;
		}
		case 'R':
		{
			flags[2] = true;
			//printf("DEBUG: Changed Flag -R to true. \n");
			break;
		}
		default:
		{
			printf("myls: invalid option -- '%c'\n", option[i]);
			return false;
		}
		}
	}
	return true;
}

//checks if an entity is a file or a directory.
//does the appropriate action.
//returns false if readEntity attempts to read a file/directory that doesnt exist.
void readEntity(char *entityPath, int entityQueueCount)
{
	DIR *pDir;

	// Check if the provided entity is an accessable directory
	pDir = opendir(entityPath);
	if (pDir == NULL)
	{
		readFile(entityPath);
	}
	else
	{
		if ((entityQueueCount != 1) || (flags[2]))
		{ //prints the name of the starting directory, unless only one directory is going to be listed.
			printf("%s: \n", entityPath);
		}
		readDirectory(entityPath);
	}
	closedir(pDir);
}

void readDirectory(char *entityPath)
{

	int entityQueueMax = 10;
	//struct dirent* entityQueue[entityQueueMax];
	struct dirent **entityQueue = malloc(entityQueueMax * 8);
	int entityQueueCount = 0;
	struct dirent *pDirent;
	DIR *pDir;
	DIR *pDir2;

	char dirQueue[entityQueueMax][MAX_WORD_LENGTH];

	int dirQueueCount = 0;

	pDir = opendir(entityPath);
	// printf("DEBUG: EntityPath: %s\n",entityPath);

	while ((pDirent = readdir(pDir)) != NULL)
	{
		// Check if entityQueue is full
		if (entityQueueCount == entityQueueMax)
		{
			entityQueueMax = entityQueueMax * 2;
			entityQueue = realloc(entityQueue, entityQueueMax * 8);
		}
		if (pDirent->d_name[0] != '.')
		{
			entityQueue[entityQueueCount] = pDirent;
			entityQueueCount++;
		}
	}

	sortEntityQueue(entityQueue, entityQueueCount);

	int max_size_array[] = {0, 0, 0, 0};

	if (flags[1])
	{
		max_size_length(&max_size_array[0], entityQueue, entityQueueCount, entityPath);
	}

	for (int i = 0; i < entityQueueCount; i++)
	{
		// Create string for full file path
		char fullDir[MAX_WORD_LENGTH] = "";

		strcpy(fullDir, entityPath);
		strcat(fullDir, "/");
		strcat(fullDir, entityQueue[i]->d_name);
		// print the entity
		//TODO: Call print function (entityQueue[i], fullDir);

		printEntity(entityQueue[i], fullDir, &max_size_array[0]);

		if (flags[2])
		{
			// Check if the entity was an accessible directory
			pDir2 = opendir(fullDir);
			if (pDir2 != NULL)
			{

				// This is an accessable directory, enqueue it
				char *dirName = malloc(255);
				strcpy(dirName, fullDir);
				strcpy(dirQueue[dirQueueCount], dirName);
				dirQueueCount++;
				free(dirName);
			}
			else
			{
				// free(fullDir);
			}

			closedir(pDir2);
		}
	}

	if (flags[2])
	{ //read the dirQueue, call readDirectory on all directories in dirQueue
		for (int i = 0; i < dirQueueCount; i++)
		{
			printf("\n%s:\n", dirQueue[i]);
			readDirectory(dirQueue[i]);
		}
	}
	// Free all malloced memory
	closedir(pDir);
	free(entityQueue);


	return;
}
//given an entityQueue, return the max size of each long formatted section in characters
void max_size_length(int *fillerarray, struct dirent **entityQueue, int entityQueueCount, char *rootDir)
{

	// fillerarray will contain the length of the longest: {# of HardLinks, fileowner, group name, fileSize}

	for (int i = 0; i < entityQueueCount; i++)
	{

		char fullDir[2 * MAX_WORD_LENGTH];
		strcpy(fullDir, rootDir);
		strcat(fullDir, "/");
		strcat(fullDir, entityQueue[i]->d_name);

		struct stat entityStat;
		stat(fullDir, &entityStat);

		// Find length of longest # of HardLinks
		char nLinks[50];
		sprintf(nLinks, "%ld", entityStat.st_nlink);
		int lenNlinks = strlen(nLinks);
		if (lenNlinks > fillerarray[0])
		{
			fillerarray[0] = lenNlinks;
		}

		// Find length of longest file owner username

		struct passwd *pw = getpwuid(entityStat.st_uid);
		char Username[100];
		sprintf(Username, "%s", pw->pw_name);
		int lenUsername = strlen(Username);
		if (lenUsername > fillerarray[1])
		{
			fillerarray[1] = lenUsername;
		}

		// Find length of longest file owner group name
		pw = getpwuid(entityStat.st_gid);
		char Groupname[100];
		sprintf(Groupname, "%s", pw->pw_name);
		int lenGroupname = strlen(Groupname);
		if (lenGroupname > fillerarray[2])
		{
			fillerarray[2] = lenGroupname;
		}

		// Find length of largest file size.
		char FileSize[100];
		sprintf(FileSize, "%ld", entityStat.st_size);
		int lenFileSize = strlen(FileSize);
		if (lenFileSize > fillerarray[3])
		{
			fillerarray[3] = lenFileSize;
		}
	}

	return;
}
// Given an entity, and its full path,
// checks flags and prints accordingly
void printEntity(struct dirent *entity, char *fullDir, int *max_size_array)
{
	struct stat entityStat;

	if (flags[0])
	{
		printf("%ld ", entity->d_ino);
	}

	if (flags[1])
	{

		stat(fullDir, &entityStat);
		if (S_ISDIR(entityStat.st_mode))
		{
			printf("d");
		}
		else
		{
			printf("-");
		}
		if (entityStat.st_mode && S_IRUSR)
		{
			printf("r");
		}
		else
		{
			printf("-");
		}
		if (entityStat.st_mode && S_IWUSR)
		{
			printf("w");
		}
		else
		{
			printf("-");
		}
		if (entityStat.st_mode && S_IXUSR)
		{
			printf("x");
		}
		else
		{
			printf("-");
		}
		if (entityStat.st_mode && S_IRGRP)
		{
			printf("r");
		}
		else
		{
			printf("-");
		}
		if (entityStat.st_mode && S_IWGRP)
		{
			printf("w");
		}
		else
		{
			printf("-");
		}
		if (entityStat.st_mode && S_IXGRP)
		{
			printf("x");
		}
		else
		{
			printf("-");
		}
		if (entityStat.st_mode && S_IROTH)
		{
			printf("r");
		}
		else
		{
			printf("-");
		}
		if (entityStat.st_mode && S_IWOTH)
		{
			printf("w");
		}
		else
		{
			printf("-");
		}
		if (entityStat.st_mode && S_IXOTH)
		{
			printf("x");
		}
		else
		{
			printf("-");
		}
		printf(" ");

		// Print the number of hard links

		char hardLinkString[40] = "%";
		char hardLinkNum[40];
		sprintf(hardLinkNum, "%i", max_size_array[0]);
		strcat(hardLinkString, hardLinkNum);
		strcat(hardLinkString, "ld ");
		printf(hardLinkString, entityStat.st_nlink);

		// Print user-name of file owner
		struct passwd *pw = getpwuid(entityStat.st_uid);

		char usernameString[40] = "%";
		char usernameNum[40];
		sprintf(usernameNum, "%i", max_size_array[1]);
		strcat(usernameString, usernameNum);
		strcat(usernameString, "s ");
		printf(usernameString, pw->pw_name);

		// Print group name of the file owner
		pw = getpwuid(entityStat.st_gid);

		char groupnameString[40] = "%";
		char groupnameNum[40];
		sprintf(groupnameNum, "%i", max_size_array[2]);
		strcat(groupnameString, groupnameNum);
		strcat(groupnameString, "s ");
		printf(groupnameString, pw->pw_name);

		//Print the size of the file (bytes)
		char byteSizeString[40] = "%";
		char byteSizeNum[40];
		sprintf(byteSizeNum, "%i", max_size_array[3]);
		strcat(byteSizeString, byteSizeNum);
		strcat(byteSizeString, "li ");
		printf(byteSizeString, entityStat.st_size);

		// Print the date & time file was last modified
		time_t rawtime = entityStat.st_mtime;
		struct tm *timeinfo;
		timeinfo = localtime(&rawtime);
		char *str = asctime(timeinfo);
		str[strlen(str) - 1] = 0;
		char *newDate = parseDate(str);
		printf("%s ", newDate);

		//printf("%ld ", entityStat.st_mtime);
		free(newDate);
	}
	bool hasSpecialChar = false;
	char specialChars[] = " !$^&,";
	for (int i = 0; i < 6; i++)
	{
		if (strchr(entity->d_name, specialChars[i]) != NULL)
		{
			hasSpecialChar = true;
			break;
		}
	}
	if (hasSpecialChar)
	{
		printf("'%s'\n", entity->d_name);
	}
	else
	{
		printf("%s\n", entity->d_name);
	}
}

//given the path to a File, check if that file actually exists
//if the file exists: print that file's name;
void readFile(char *entityPath)
{

	if (access(entityPath, F_OK) == -1)
	{
		//Error Code Stuff
		printf("myls: cannot access file '%s': no such file or directory\n", entityPath);

		return;
	}
	else
	{
		printf("%s\n", entityPath);
		return;
	}
}

void testLexiSort()
{
	char *table[8] = {"word", "that", "is", "safe", "for", "kids", "to", "read"};
	for (int i = 0; i < 8; i++)
	{
		printf("%i: %s\n", i, table[i]);
	}
	printf("Sorting....\n");
	LexiSort(table, 8);
}

void LexiSort(char *table[], int numOfEntries)
{
	// void LexiSort(char table[][MAX_WORD_LENGTH],int numOfEntries){

	char *lowest = malloc(MAX_WORD_LENGTH);
	int lowestIndex;
	for (int i = 0; i < numOfEntries; i++)
	{

		lowest = table[i];
		lowestIndex = i;
		for (int j = i; j < numOfEntries; j++)
		{
			if (isLower(table[j], lowest))
			{
				lowest = table[j];
				lowestIndex = j;
			}
		}

		table[lowestIndex] = table[i];
		table[i] = lowest;
	}

	// free(lowest);
}
//tests if 'first' is lexicographically smaller than 'second'

char *stringToLower(char *lowerString, char *string)
{

	for (int i = 0; i < strlen(string); i++)
	{
		lowerString[i] = tolower(string[i]);
	}
}

bool isLower(char *first, char *second)
{

	char lowerFirst[MAX_WORD_LENGTH] = "";
	char lowerSecond[MAX_WORD_LENGTH] = "";

	// printf("DEBUG: First: %s    Lower First%s\n",first,lowerFirst);

	stringToLower(lowerFirst, first);
	stringToLower(lowerSecond, second);

	if (strcmp(lowerFirst, lowerSecond) < 0)
	{
		// printf("%s < %s\n",lowerFirst,lowerSecond);
		return true;
	}
	else
	{
		// printf("%s >= %s\n",lowerFirst,lowerSecond);
		return false;
	}

	// for (int i = 0; (i < strlen(first) || i <strlen(second)); i++){
	// 	if (tolower(first[i])<tolower(second[i])){
	// 		return true;
	// 	}
	// 	if (tolower(first[i])>tolower(second[i])){
	// 		return false;
	// 	}
	// 	if (i == strlen(second)){
	// 		return false;
	// 	}
	// 	if (i == strlen(first)){
	// 		return true;
	// 	}

	// }
}

void sortEntityQueue(struct dirent **entityQueue, int numOfEntries)
{
	char *lowestP;
	int lowestIndex;
	for (int i = 0; i < numOfEntries; i++)
	{
		lowestP = entityQueue[i]->d_name;
		lowestIndex = i;

		for (int j = i; j < numOfEntries; j++)
		{

			if (isLower(entityQueue[j]->d_name, lowestP))
			{

				lowestP = entityQueue[j]->d_name;
				lowestIndex = j;
			}
		}

		struct dirent *lowestEntity = entityQueue[lowestIndex];

		entityQueue[lowestIndex] = entityQueue[i];
		entityQueue[i] = lowestEntity;
	}
}

char *parseDate(char *date)
{
	char *newDate = malloc(18);

	// Copy month
	memcpy(&newDate[0], &date[4], 3);
	newDate[3] = ' ';
	// Copy date
	memcpy(&newDate[4], &date[8], 2);
	newDate[6] = ' ';
	// Copy year
	memcpy(&newDate[7], &date[20], 4);
	newDate[11] = ' ';
	// Copy time
	memcpy(&newDate[12], &date[11], 5);
	newDate[17] = '\0';
	return newDate;
}
