
//prototypes
void translateTextInput();
void translateTextFile();

void addEntry(struct entryTag *pair, int currEntries);
void addTranslation();
void deleteEntry();
void deleteTranslation();
void displayAllEntries();
void searchWord();
void searchTranslation();
void exportFile();
void importFile();

//handles menu for translate menu
void
translateMenu()
{
	int state = 1;
	int input;

	while(state)
	{
		displayTranslateMenu();
		scanf("%d", &input);
		switch(input)
		{
/*
			case 1: translateTextInput();
				break;
			case 2: translateTextFile();
				break;
			case 3: state = 0;
				break;
*/
		}
	}
}

void 
manageData()
{
	struct entryTag pair[MAX_ENTRIES];
	int state = 1;
	int currEntries = 0;
	int input;

	while(state)
	{
		displayManageData();
		scanf("%d", &input);
		switch(input)
		{
			case 1: addEntry(pair, currEntries);
				break;
/*
			case 2: addTranslation();
				break;
			case 3: deleteEntry();
				break;
			case 4: deleteTranslation();
				break;
			case 5: displayAllEntries();
				break;
			case 6: searchWord();
				break;
			case 7: searchTranslation();
				break;
			case 8: exportFile();
				break;
			case 9: importFile();
				break;
				*/
			case 0: state = 0; 
				break;
		}
	}
}

//ask for a language pair (tagalog and mahal)
//check existing entries with input pair
//	yes: show all information about existing info
//is this a new entry?
//	yes: new entry created 
//	no: program goes to manage data menu
//new lang-trans pair?
//	Press Enter... (menu)
//	yes: loop back
//
// at least one character
void 
addEntry(struct entryTag *pair, int currEntries)
{
	char temp;
	char uInput = 'Y';
	int i = currEntries;
	
	getchar();
	do
	{
		printf("%s", LINE);
		printf("Enter Language-Translation Pair (Format: Language Translation)!\n");
		scanf("%20s", pair->language[i]);
		scanf("%20s%c", pair->translation[i], &temp);
		pair->nPairs = i;
		i++;

		printf("\nImplement Shows Entries w/ Similar Pairs\n\n");
		
		printf("Do you want to enter another pair (Y/N)? ");
		scanf("%c%c", &uInput, &temp);
		printf("%s\n", LINE);
		
	} while (i < MAX_PAIRS && uInput == 'Y');	
}


















