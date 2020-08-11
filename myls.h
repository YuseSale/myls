#ifndef HEADER_FILE
#define HEADER_FILE
#define MAX_WORD_LENGTH 256
void processArgs(int argc, char *argv[]) ;
bool parseOption(char* option) ;
void readDirectory(char* entityPath);
void sortEntityQueue(struct dirent** entityQueue,int numOfEntries);
bool isLower(char* first, char* second);
void LexiSort(char* table[],int numOfEntries);
void printEntity(struct dirent* entity, char* fullDir, int* max_size_array);
char* parseDate(char* date);
void readEntity (char* entityPath, int entityQueueCount);
void readFile(char* entityPath);
void max_size_length(int* fillerarray, struct dirent** entityQueue, int entityQueueCount, char* rootDir);
#endif


