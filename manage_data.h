///////////* HANDLE MENU *////////////

/* manageData handles the functions for all the features that involves managing the data 
*/ 
void
manageData()
{
	/*********************************
	 * RESTARTS ENTRIES
	 * declared the entry array inside
	 * the manageData() so it restarts
	 * automatically :)
	**********************************/
	struct entryTag entry[MAX_ENTRIES];
	int currEntries = 0;	
	int state = 1;
	
	while(state)
	{
		displayManageData();
		switch(getInput(0,9))
		{
			case 1: addEntry(entry, &currEntries);
				break;
			case 2: addTranslation(entry, currEntries);
				break;
			case 3: deleteEntry(entry, &currEntries);
				break;
			case 4: deleteTranslation(entry, &currEntries);
				break;
			case 5: displayAllEntries(entry, currEntries);
				break;
			case 6: searchWord(entry, currEntries);
				break;
			case 7: searchTranslation(entry, currEntries);
				break;
			case 8: exportFile(entry, currEntries);
				break;
			case 9: importFile(entry, &currEntries);
				break;
			case 0: state = 0;
				break;
		}
	}
}

/////////* HANDLE FEATURES *//////////

/* addEntry adds an entry to an index of the entry struct
   @param entry	- the address where the entries are stored
   @param nEntry	- the address where the number of entries are stored
*/
void 
addEntry(struct entryTag * entry, int * nEntry)
{
	String20 language, translation;	
	char uInput, temp;
	int i, j;
	
	getPairs(language, translation);
	
	if(*nEntry == 0)
		printf("No entries as of now...\n\n");
	
	for(i = 0; i < *nEntry && *nEntry < MAX_ENTRIES; i++)
	{
		for(j = 0; j < entry[i].nPairs; j++)
		{
			if(strcmp(entry[i].language[j], language) == 0
				&& strcmp(entry[i].translation[j], translation) == 0)
				{					
					printf("Entry #%d\n", i+1);
					displayEntry(entry[i]);
					printf("\n");
					//ends the loop early
					j = entry[i].nPairs; 	
				}
		}
	}
	
	//ask if new entry
	printf("Is this a new entry (Y/N)? ");
	scanf("%c%c", &uInput, &temp);
	printf("\n");
	
	if(uInput == 'Y')
	{	
		printf("Encoding new entry pair...\n");

		//Assigning to a new entry
		i = 0;
		strcpy(entry[*nEntry].language[i], language);
		strcpy(entry[*nEntry].translation[i], translation);
		i++;	
		
		//get new set of pairs
		do
		{
			getPairs(language, translation);
			strcpy(entry[*nEntry].language[i], language);
			strcpy(entry[*nEntry].translation[i], translation);
		
			printf("Enter another pair (Y/N)? ");
			scanf("%c%c", &uInput, &temp);
			
			i++;
		} while (i < MAX_PAIRS && uInput == 'Y');	
		
		entry[*nEntry].nPairs = i;
		
		//if max pairs, warn & exit
		if(i == MAX_PAIRS)
		{
			printf("\n");
			printf("Max Pairs Reached! Press ENTER to continue... ");
			getchar();
		}
		printf("\n");
		
		//add to the entry count
		*nEntry += 1;
	}
}

/* addTranslation adds a translation to an index of the entry struct entered by the user
   @param entry	- the address where the entries are stored
   @param nEntry	- the number of entries stored
   Pre-condition: entry contents contain at least 1 letter and number according to nEntry
*/
void 
addTranslation(struct entryTag entry[], int nEntry)
{
	String20 language, translation;
	char uInput, temp;
	int i, j, k, flag;
	int nFoundEntries = 0;
	int idxFoundEntry;
	
	getPairs(language, translation);
	
	//count all found MATCHING entries
	k = 0;
	for(i = 0; i < nEntry; i++)
	{
		for(j = 0; j < entry[i].nPairs; j++)
		{
			if(strcmp(entry[i].language[j], language) == 0
				&& strcmp(entry[i].translation[j], translation) == 0)
				{					
					printf("Entry #%d\n", ++k);
					displayEntry(entry[i]);
					if(i+1 != nEntry)
						printf("\n");
					else
						line(30);
					nFoundEntries++;
					//take note of the first found entry
					if(nFoundEntries == 1)	
						idxFoundEntry = i;
					//display only once
					j = entry[i].nPairs; 	
				}
		}
	}
	
	//entry doesnt exist
	if(nFoundEntries == 0)
	{
		printf("This entry doesn't exist, \n");
		printf("please make one in [Add Entry].\n\n");
		printf("Press ENTER to continue... ");
		getchar();
		printf("\n");
	}
	
	//entry exists
	else if(nFoundEntries > 0)
	{
		//entry is more than one
		//choose the entry
		flag = 0;
		if(nFoundEntries > 1)
		{
			printf("Which Entry would you like to\n");
			printf("add the translation to? Please\n");
			printf("type %d to exit.\n", nFoundEntries + 1);
			line(30);
			idxFoundEntry = getInput(1, nFoundEntries + 1);
			idxFoundEntry -= 1;
			if(idxFoundEntry == nFoundEntries)	
			{
				flag = 1;
				printf("\n");
			}
		}
		
		//if pairs is already max count
		if(entry[idxFoundEntry].nPairs == 10)
		{
			printf("\n");
			printf("This entry already has a count\n");
			printf("of %d. No additional pairs can\n", MAX_PAIRS);
			printf("be added!\n\n");
			printf("Press ENTER to continue... ");
			getchar();
			printf("\n");
		}
		//otherwise ask what to add
		else if(!flag)
		{
			i = entry[idxFoundEntry].nPairs;
			do
			{	
				getPairs(language, translation);
				strcpy(entry[idxFoundEntry].language[i], language);
				strcpy(entry[idxFoundEntry].translation[i], translation);
				
				i++;
				
				printf("Enter another pair (Y/N)? ");
				scanf("%c%c", &uInput, &temp);
			} while (i < MAX_PAIRS && uInput == 'Y');	
			printf("\n");
			
			//check if max pairs again
			if(i == MAX_PAIRS)
			{				
				printf("Max Pairs Reached! Press ENTER to continue... ");
				getchar();
				printf("\n");
			}	
			
			entry[idxFoundEntry].nPairs = i;
		}
	}
}

/* deleteEntry deletes an entry given the index taken from the user
   @param entry	- the address where the entries are stored
   @param nEntry	- the address where the number of entries are stored
   Pre-condition: entry contents contain at least 1 letter and number according to nEntry
*/
void 
deleteEntry(struct entryTag * entry, int * nEntry)
{
	int input;
	int state;

	state = 1;

	//no entries exist
	if(*nEntry == 0)
	{
		handleError(NOT_ENOUGH_ENTRIES);
		printf("\n");
		printf("Press ENTER to continue... ");
		getchar();
	}
	//entries exist!
	else
	{
		line(30);
		printf("Please exit out of viewing to\n");
		printf("choose which entry to delete\n");
		printf("\n");
		displayAllEntries(entry, *nEntry);
		
		printf("Enter the number of the  entry\n");
		printf("that you would  like to delete\n");
		line(30);
		
		input = checkEarlyTermination();
		if(input == -1)
			state = 0;	
		
		if(state == 1 && input >= 1 && input <= *nEntry)
		{
			shiftStructArray(entry, *nEntry, input - 1);
			*nEntry -= 1;
			printf("\n");
			printf("Entry deleted!\n");
			getchar();
		}
		printf("\n");
	}
}

/* deleteTranslation deletes a translation inside an entry
   @param entry	- the address where the entries are stored
   @param nEntry	- the address where the number of entries are stored
   Pre-condition: entry contents contain at least 1 letter and number according to nEntry.
						nEntry is greater than zero in order to use
*/
void
deleteTranslation(struct entryTag * entry, int * nEntry)
{
	String20 language, translation;
	int intUser;
	char chUser, temp;
	int flag;
	int i;
	int state;
	
	if(*nEntry == 0)
	{
		handleError(NOT_ENOUGH_ENTRIES);
		printf("\n");
		printf("Press ENTER to continue... ");
		getchar();
		printf("\n");
	}
	else
	{
		//display entries
		line(30);
		printf("Please exit out of viewing to\n");
		printf("choose which entry to delete\n");
		printf("\n");
		displayAllEntries(entry, *nEntry);
		
		printf("Enter the number of the  entry\n");
		printf("that you would  like to delete\n");
		printf("from.\n");
		line(30);
		
		state = 1;
	
		intUser = checkEarlyTermination();
		if(intUser == -1)
		{
			state = 0;
		}
		
		//the user input is 0-indexxed
		intUser -= 1;
		while(state == 1 && intUser >= 0 && intUser < *nEntry)
		{
			getPairs(language, translation);
		
			//checks if the pair exists in the entry chosen by the user
			flag = 0;
			for(i = 0; i < entry[intUser].nPairs && !flag; i++)
			{
				if(strcmp(language, entry[intUser].language[i]) == 0)
				{
					if(strcmp(translation, entry[intUser].translation[i]) == 0)
					{
						//this is for special cases of single translations
						//therefore the whole entry will be erased instead
						if(entry[intUser].nPairs == 1)
						{
							shiftStructArray(entry, *nEntry, intUser);
							printf("No more entries left to delete!\n");
							*nEntry -= 1;
							flag = 1;
							state = 0;
						}
						//otherwise it does the normal translation delete
						//by shifting the array to a certain key 
						else
						{
							shiftStringArray(entry[intUser].language, entry[intUser].nPairs, i);
							shiftStringArray(entry[intUser].translation, entry[intUser].nPairs, i);
							entry[intUser].nPairs -= 1;
							flag = 1;
						}
					}
				}
			}
			
			//message to user 
			if(!flag)
				printf("This pair doesn't exist!\n");
			else if(flag)
			{
				printf("Pair has been deleted!\n");
				printf("\n");
			}
			
			if(state)
			{
				printf("Would you still like to delete\n");
				printf("a pair (Y/N)?\n");
				line(30);
				scanf("%c%c", &chUser, &temp);
				
				if(chUser != 'Y')
					state = 0;
			} 
			else
			{
				printf("Press ENTER to continue... ");
				getchar();
			}
		}
		
		printf("\n");
	}
}

/* displayAllEntries displays the current entries given the passed entryTag struct and entry count
   @param entry	- the address where the entries are stored
   @param nEntry	- the number of entries are stored
   Pre-condition: entry contents contain at least 1 letter and number according to nEntry
*/
void
displayAllEntries(struct entryTag * entry, int nEntry)
{
	String20 input;
	int valid;
	int i;
	
	//sorts the entries before display
	//sort also has a key language, default
	//is "English"
	sortEntries(entry, nEntry, LANGUAGE_TO_SORT);
	
	if(nEntry == 0)
	{
		line(30);
		printf("No entries to display! Please\n");
		printf("add entries using [Add Entry].\n");
		printf("\n");
		printf("Press ENTER to continue... ");
		getchar();
		printf("\n");
	}
	
	//the display
	for(i = 0; i < nEntry; i++)                                             
	{
		printf("=========  Entry #%-3d=========\n", i+1);		
		displayEntry(entry[i]);
		printf("\n");
		printf("[N]ext  [P]rev  [X]\n");
		printf("\n");
		
		valid = 0;
		do
		{
			//gets input
			printf("> ");
			fgets(input, sizeof(input), stdin);
		
			//handles errors for this function
			switch(input[0])
			{
				case 'N': 
					if(i+1 < nEntry)
						valid = 1;
					else
						handleError(LAST_ENTRY);
					break;
				case 'P': if(i != 0)
					{
						i -= 2;
						valid = 1;
					}
					else
						handleError(FIRST_ENTRY);
					 break;
				case 'X': 
					i = nEntry;
					valid = 1;
							 break;
				default:  handleError(INVALID_INPUT);
							break;
			}
			
		} while(!valid);
	}
	printf("\n");
}

/* searchWord searches the word given a valid word input and displays all valid entries
   @param entry	- the address where the entries are stored
   @param nEntry	- the number of entries are stored
   Pre-condition: entry contents contain at least 1 letter and number according to nEntry
*/
void
searchWord(struct entryTag * entry, int nEntry)
{	
	String20 word;
	//temporary struct to store all the entries
	//where it found matching words
	struct entryTag bFound[MAX_ENTRIES];
	int bCount = 0;
	int i, j;
	
	//handles input
	do
	{
		line(30);
		printf("Enter a Search Word!\n");
		printf("Word: ");
		fgets(word, sizeof(word), stdin);
		
		word[strlen(word) - 1] = '\0';
		
		if(strlen(word) == 0)
			printf("Error! Please enter more than one character.\n");
		
	} while(strlen(word) == 0);
	printf("\n");
	
	//checks through all entries + translations
	for(i = 0; i < nEntry; i++)
	{
		for(j = 0; j < entry[i].nPairs; j++)
		{
			if(strcmp(entry[i].translation[j], word) == 0)
			{
				bFound[bCount] = entry[i];
				bCount++;
				
				j = entry[i].nPairs;
			}
		}
	}
	
	//if none exists no matches found
	if(bCount == 0)
	{
		printf("No matches found.\n");
		printf("\n");
		printf("Press ENTER to continue...");
		getchar();
		printf("\n");
	}
	//else display the entries
	else
	{
		displayAllEntries(bFound, bCount);
	}
}

/* searchTranslation searches the translation given a valid pair input and displays all valid entries
   @param entry	- the address where the entries are stored
   @param nEntry	- the number of entries are stored
   Pre-condition: entry contents contain at least 1 letter and number according to nEntry
*/
void
searchTranslation(struct entryTag * entry, int nEntry)
{
	String20 language, translation;
	//temporary struct to store all the entries
	//where it found matching words
	struct entryTag bFound[MAX_ENTRIES];
	int bCount = 0;
	int i, j;
	
	//handles input
	getPairs(language, translation);
	
	//checks language and translations
	for(i = 0; i < nEntry; i++)
	{
		for(j = 0; j < entry[i].nPairs; j++)
		{
			if((strcmp(entry[i].language[j], language) == 0) &&
				(strcmp(entry[i].translation[j], translation) == 0))
			{
				bFound[bCount] = entry[i];
				bCount++;
				
				j = entry[i].nPairs;
			}
		}
	}
	
	//check for matches
	if(bCount == 0)
	{
		printf("No matches found.\n");
		printf("\n");
		printf("Press ENTER to continue...");
		getchar();
		printf("\n");
	}
	//if found display them 
	else
	{
		displayAllEntries(bFound, bCount);
	}
}


/* exportFile exports the array into a txt file, whose filename is inputted by the user
   @param entry	- the address where the entries are stored
   @param nEntry	- the number of entries are stored
   Pre-condition: entry contents contain at least 1 letter and number according to nEntry
*/
void
exportFile(struct entryTag * entry, int nEntry)
{
	FILE *fpSave;
	String30 filename;
	int i, j;
	
	//sorts before exporting
	sortEntries(entry, nEntry, "English");
	
	//display and handle input
	displayFilenameInstructions();
	getFilename(filename);
	
	fpSave = fopen(filename, "w");
	
	//handle error
	if(fpSave == NULL)
	{
		handleError(FILE_NOT_FOUND);
		printf("\n");
		printf("Press ENTER to continue... ");
		getchar();
	}
	else
	{
		line(30);
		printf("successfully exported.\n");
	}
	printf("\n");
	
	//save to txt files
	for(i = 0; i < nEntry; i++)
	{
		for(j = 0; j < entry[i].nPairs; j++)
		{
			fprintf(fpSave, "%s: %s\n", entry[i].language[j], entry[i].translation[j]);
		}
		fprintf(fpSave, "\n");
	}
	
	fclose(fpSave);
	
	printf("Press ENTER to continue... ");
	getchar();
	
	printf("\n");
}	

/* importFile imports a text file into the program array or to the address of entry.
	The filename to import from is taken through user input.
   @param entry	- the address where the entries are stored
   @param nEntry	- the address where the  number of entries are stored
   Pre-condition: entry contents contain at least 1 letter and number according to nEntry
						the txt file the user is importing from has the VALID format
*/
void
importFile(struct entryTag * entry, int * nEntry)
{
	struct entryTag temp;
	
	FILE *fpLoad;
	String30 filename;
	char ch;
	int pairCount;
	int i, j;
	
	displayFilenameInstructions();
	getFilename(filename);
	
	fpLoad = fopen(filename, "r");
	
	//file failed to load
	if(fpLoad == NULL)
	{
		handleError(FILE_NOT_FOUND);
		printf("\n");
		printf("Press ENTER to continue... ");
		getchar();
	}
	//file loaded
	else
	{
		j = 0;
		pairCount = 0;
		//checks if EOF 
		while(fscanf(fpLoad, "%c", &ch) == 1)
		{	
			//\n will be the terminating character here (for each entry)
			if(ch != '\n')
			{
				//for each language:
				temp.language[pairCount][0] = ch;
				i = 1;	
				do
				{
					fscanf(fpLoad, "%c", &temp.language[pairCount][i]);
					i++;
				} while(temp.language[pairCount][i-1] != ':');
				strcpy(temp.language[pairCount] + (i-1), "" );
				fscanf(fpLoad, "%c", &ch);
				
				//for each translation'\n'
				i = 0;
				do
				{
					fscanf(fpLoad, "%c", &temp.translation[pairCount][i]);
					i++;
				} while(temp.translation[pairCount][i-1] != '\n');
				strcpy(temp.translation[pairCount] + (i-1), "" );			
				
				//add to pair count
				pairCount++;
			}
			//once stored in temp ask if it should be stored in the program
			else
			{	
				temp.nPairs = pairCount;
				pairCount = 0;

				//display the entry
				printf("Entry #%d\n", j+1);
				displayEntry(temp);
				printf("\n");
				j++;
			
				//asks if it should be added
				printf("Add this entry (Y/N)? ");
				scanf("%c", &ch);
				getchar();
				line(30);
				
				//adjust entry like so
				if(ch == 'Y')
				{
					entry[*nEntry] = temp;
					*nEntry += 1;
				}
			}
		}
		
		fclose(fpLoad);
		printf("End of File Reached!\n");
		printf("Press ENTER to continue... ");
		getchar();
	}
	
	printf("\n");
}
/////////* HANDLE FEATURES *//////////