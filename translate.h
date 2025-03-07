
//prototypes
void translateTextInput();
void translateTextFile();
void addEntry();
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
		/*
		switch(input)
		{
			case 1: translateTextInput();
				break;
			case 2: translateTextFile();
				break;
			case 3: state = 0;
				break;
		}
		*/
	}
}

void 
manageData()
{	
	int state = 1;
	int input;

	while(state)
	{
		displayTranslateMenu();
		scanf("%d", &input);
		/*
		switch(input)
		{
			case 1: addEntry();
				break;
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
			case 0: state = 0; 
				break;
		}
		*/
	}
}

void 
addEntry()
{
}
