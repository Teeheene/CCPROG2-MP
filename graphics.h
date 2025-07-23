
void
line(int length)
{
	int i;
	
	for(i = 0; i < length; i++)
	{
		printf("-");
	}
	printf("\n");
}

void
displayMenu()
{
	printf("==========Translator==========\n");
	printf("[1] Translate Menu\n");
	printf("[2] Manage Data\n"); 
	printf("[3] Exit\n");
	printf("==============================\n");
}

void
displayTranslateMenu()
{
	printf("========Translate Menu========\n");
	printf("[1] Translate Text Input\n");
	printf("[2] Translate Text File\n");
	printf("[3] Exit\n");
	printf("==============================\n");
}

void
displayManageData()
{
	printf("==========Manage Data=========\n");
	printf("[1] Add Entry\n");
	printf("[2] Add Translations\n");
	printf("[3] Delete Entry\n");
	printf("[4] Delete Translations\n");
	printf("[5] Display All Entries\n");
	printf("[6] Search Word\n");
	printf("[7] Search Translation\n");
	printf("[8] Export\n");
	printf("[9] Import\n");
	printf("[0] Exit\n");
	printf("==============================\n");
}

void
displayFilenameInstructions()
{
	line(30);
	printf("Enter the filename of the file\n");
	printf("you wish to load! The limit is\n");
	printf("only 30 characters,  including\n");
	printf("the .txt extension. If it goes\n");
	printf("over, the filename will be cut\n");
	printf("				   					  \n");
	printf("Filename: meow_translations   \n");
	line(30);
}

void
displayTranslateInstructions()
{
	line(30);
	printf("Enter the language you wish to\n");
	printf("translate TO and FROM!		  \n");
	line(30);
}

void 
displayEntry(struct entryTag entry)
{
	int i;
	
	for(i = 0; i < entry.nPairs; i++)
	{
		printf("%s: %s\n", entry.language[i], entry.translation[i]);
	}
}
