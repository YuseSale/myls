#ifndef HEADER_FILE
#define HEADER_FILE
#define MAX_WORD_LENGTH 40
void processArgs(int argc, char *argv[]) ;

bool parseOption(char* option) ;

void readDirectory(char* entityPath);

void testParseOption();

void testFlags();
// void testLexoSort(char** stringQueue);
void testLexiSort();
void sortEntityQueue(struct dirent** entityQueue,int numOfEntries);
void testIsLower();
bool isLower(char* first, char* second);
void LexiSort(char* table[],int numOfEntries);
void printEntity(struct dirent* entity, char* fullDir, int* max_size_array);
// void LexiSort(char table[][MAX_WORD_LENGTH],int numOfEntries);
char* parseDate(char* date);

void readEntity (char* entityPath, int entityQueueCount);
void readFile(char* entityPath);
void max_size_length(int* fillerarray, struct dirent** entityQueue, int entityQueueCount, char* rootDir);
#endif


