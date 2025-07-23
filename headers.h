//for graphics
#define SHORT_LINE 25
#define LONG_LINE 30

//for program limits
#define MAX_ENTRIES 150
#define MAX_PAIRS 10
#define MAX_FILENAME_COUNT 30
#define MAX_TXT 150

//for settings and sortings
#define LANGUAGE_TO_SORT "English"

//for error handling
#define FILE_NOT_FOUND 1
#define INVALID_INPUT 2
#define OUT_OF_RANGE 3
#define MISSING_CHAR 4
#define NOT_ENOUGH_ENTRIES 5
#define FIRST_ENTRY 6
#define LAST_ENTRY 7

typedef char String20 [20+1];
typedef char String30 [30+1];
typedef char String150 [150+1];

struct entryTag 
{
	String20 language[MAX_PAIRS];
	String20 translation[MAX_PAIRS];
	int nPairs; 
};
	
//prototypes (REQUIRED)
void translateTextInput(struct entryTag * entry, int nEntry);
void translateTextFile(struct entryTag * entry, int nEntry);
void addEntry(struct entryTag * entry, int * currEntries);
void addTranslation(struct entryTag * entry, int currEntries);
void deleteEntry(struct entryTag * entry, int * nEntry);
void deleteTranslation(struct entryTag * entry, int * nEntry);
void displayAllEntries(struct entryTag * entry, int nEntry);
void searchWord(struct entryTag * entry, int nEntry);
void searchTranslation(struct entryTag * entry, int nEntry);
void exportFile(struct entryTag * entry, int nEntry);
void importFile(struct entryTag * entry, int * nEntry);

//prototypes (HELPER FUCNTIONS)
void handleError(int errorCode);
int getInput(int lowerRange, int upperRange);
void getPairs(String20 resultLang, String20 resultTransl);
void getFilename(String30 filename);
void getLanguageToTranslate(String20 in, String20 out);
void getLanguageToTranslate(String20 in, String20 out);
void readFileIntoSentence(FILE * file, String150 txt);
void sortWords(struct entryTag * entry, int nEntry, String20 language);
void sortLanguage(struct entryTag * entry);
void sortEntry(struct entryTag * entry, int nEntry, String20 language);
void shiftStructArray(struct entryTag * entry, int nEntry, int key);
void shiftStringArray(String20 str[], int n, int key);
void swapStr(String20 a, String20 b);
void tokenizeTxt(String150 arrWords[], int * nWords);
int loadDictionary(struct entryTag * entry, int * nEntry, String30 filename);
int checkEarlyTermination();
void displayEntry(struct entryTag entry);