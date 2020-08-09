#ifndef HEADER_FILE
#define HEADER_FILE
#define MAX_WORD_LENGTH 40
void processArgs(int argc, char *argv[]) ;

void parseOption(char* option) ;

void printFiles(char* dir);

void testParseOption();

void testFlags();
// void testLexoSort(char** stringQueue);
void testLexiSort();
void sortEntityQueue(struct dirent* entityQueue);
void testIsLower();
bool isLower(char* first, char* second);
void LexiSort(char table[][MAX_WORD_LENGTH],int numOfEntries);

#endif


