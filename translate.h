///////////* HANDLE MENU *////////////
void
translateMenu()
{
	struct entryTag entry[MAX_ENTRIES];
	int currEntries = 0;
	int state;
	String30 filename;
	
	state = 1;

	//get the filename
	displayFilenameInstructions();
	getFilename(filename);
	
	//confirm if filename is loadable
	if(!loadDictionary(entry, &currEntries, filename))
	{
		handleError(FILE_NOT_FOUND);
		state = 0;
	}
	printf("\n");	
	
	//enter menu
	while(state)
	{
		displayTranslateMenu();
		switch(getInput(1,3))
		{
			case 1: translateTextInput(entry, currEntries);
				break;
			case 2: translateTextFile(entry, currEntries);
				break;
			case 3: state = 0;
				break;
		}
	}
}
///////////* HANDLE MENU *////////////

/////////* HANDLE FEATURES *//////////
void 
translateTextInput(struct entryTag * entry, int nEntry)
{
	String150 temp, txt[MAX_TXT];
	String20 languageIN, languageOUT;
	int wordCount;
	int i, j, currWord;
	int flagIdxI, flagWord;
	char ch;
	
	displayTranslateInstructions();
	getLanguageToTranslate(languageIN, languageOUT);
	
	do
	{
		//for style points B-)
		line(30);
		printf("%s ---> %s\n", languageIN, languageOUT);
		printf("\n");
		
		//get raw text
		printf("TEXT: ");
		fgets(temp, sizeof(temp), stdin);
		temp[strlen(temp)-1] = '\0';
		//process raw text
		tokenizeSentence(temp, txt, &wordCount);
		
		//translate text
		printf("TRANSLATION: ");
		currWord = 0;
		while(currWord < wordCount)
		{
			//check if languageIN + text exists 
			flagIdxI = -1;
			for(i = 0; i < nEntry && flagIdxI == -1; i++)
			{
				for(j = 0; j < entry[i].nPairs; j++)
				{
					if(strcmp(languageIN, entry[i].language[j]) == 0 && strcmp(txt[currWord], entry[i].translation[j]) == 0)
					{
						flagIdxI = i;
					}
				}
			}
			
			//if they exist check if languageOUT exists
			flagWord = 0;
			if(flagIdxI != -1)
			{
				for(j = 0; j < entry[flagIdxI].nPairs && !flagWord; j++)
				{
					if(strcmp(languageOUT, entry[flagIdxI].language[j]) == 0)
					{
						printf("%s ", entry[flagIdxI].translation[j]);
						flagWord = 1;
					}
				}
			}
			
			//if the word doesnt have a translation, print as is
			if(!flagWord)
			{
				printf("%s ", txt[currWord]);
			}
			
			currWord++;
		}
		printf("\n\n");
		
		//ask for new text
		printf("Translate new text?\n");
		printf("[This will use the same source and output language]\n\n");
		printf("Y/N : ");
		scanf("%c", &ch);
		getchar();
		
		wordCount = 0;
		
	} while(ch == 'Y');
	
	line(30);
	printf("\n");
}

void 
translateTextFile(struct entryTag * entry, int nEntry)
{
	FILE *fpInput, *fpOutput; 
	String30 filename;
	String150 txt;
	String150 token[MAX_TXT];
	
	String20 languageIN, languageOUT; 
	
	char ch;
	int i, j, flag, flagIdxI, flagWord;
	int wordCount, currWord;

	flag = 0;
	
	//get the from and to language pair
	displayTranslateInstructions();
	getLanguageToTranslate(languageIN, languageOUT);
	
	//get the filename
	displayFilenameInstructions();
	getFilename(filename);
	
	//error handling
	fpInput = fopen(filename, "r");
	if(fpInput == NULL)
	{
		handleError(FILE_NOT_FOUND);
		flag = 1;
	}
	
	//this only runs if it succeeds the first error handling! 
	//did this because there were some errors otherwise :P
	if(!flag)
	{
		displayFilenameInstructions();
		getFilename(filename);
		fpOutput = fopen(filename, "w");
		
		do
		{
			//get the sentence (while not terminating value set txt the buffer char)
			readFileIntoSentence(fpInput, txt);
			if(txt[0] != '\0')
			{
				//once sentence is determined, tokenize it into an array
				tokenizeSentence(txt, token, &wordCount);
				
				//translate text
				currWord = 0;
				while(currWord < wordCount)
				{
					//check if languageIN + text exists 
					flagIdxI = -1;
					for(i = 0; i < nEntry && flagIdxI == -1; i++)
					{
						for(j = 0; j < entry[i].nPairs; j++)
						{
							if(strcmp(languageIN, entry[i].language[j]) == 0 && strcmp(token[currWord], entry[i].translation[j]) == 0)
							{
								flagIdxI = i;
							}
						}
					}
					
					//if they exist check if languageOUT exists
					flagWord = 0;
					if(flagIdxI != -1)
					{
						for(j = 0; j < entry[flagIdxI].nPairs && !flagWord; j++)
						{
							if(strcmp(languageOUT, entry[flagIdxI].language[j]) == 0)
							{
								fprintf(fpOutput, "%s ", entry[flagIdxI].translation[j]);
								flagWord = 1;
							}
						}
					}
					
					if(!flagWord)
					{
						fprintf(fpOutput, "%s ", token[currWord]);
					}
					
					currWord++;
				}
				fprintf(fpOutput, "\n");	
				
				//clear out tokens
				for(i = 0; i < wordCount; i++)
				{
					strcpy(token[i], "");
				}
				strcpy(txt, "\0");
				wordCount = 0;
			}
		} while (fscanf(fpInput, "%c", &ch) != EOF);
		
		
		line(30);	
		printf("Successfully saved.\n");
		line(30);
		
		fclose(fpInput);
		fclose(fpOutput);
	}
	
	printf("\n");
}
/////////* HANDLE FEATURES *//////////