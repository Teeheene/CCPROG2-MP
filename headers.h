#define LINE "+---------------------------+\n"

#define MAX_PAIRS 10
#define MAX_ENTRIES 150
typedef char String20 [20+1];

struct entryTag 
{
	String20 language[MAX_PAIRS];
	String20 translation[MAX_PAIRS];
	int nPairs; 
};

