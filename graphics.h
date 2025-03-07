
void
line()
{
	printf("+------------------------+\n");
}

void
displayMenu()
{
	line();
	printf("Translator\n");
	line();
	printf("[1] Translate Menu\n");
	printf("[2] Manage Data\n"); 
	printf("[3] Exit\n");
	line();
}

void
displayTranslateMenu()
{
	line();
	printf("Translate Menu\n");
	line();
	printf("[1] Translate Text Input\n");
	printf("[2] Translate Text File\n");
	printf("[3] Exit\n");
	line();
}

void
displayManageData()
{
	line();
	printf("Manage Data\n");
	line();
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
	line();
}
