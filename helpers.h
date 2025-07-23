void
handleError(int errorCode)
{
	line(30);
	switch(errorCode)
	{
		case FILE_NOT_FOUND:
			printf("Error: File not found\n");
			break;
		case INVALID_INPUT:
			printf("Error: Invalid input\n");
			break;
		case OUT_OF_RANGE:
			printf("Error: Out of range\n");
			break;
		case MISSING_CHAR:
			printf("Error: Not enough characters\n");
			break;
		case NOT_ENOUGH_ENTRIES:
			printf("Error: Not enough entries\n");
			break;
		case FIRST_ENTRY:
			printf("Error: Already at first entry\n");
			break;
		case LAST_ENTRY:
			printf("Error: Already at last entry\n");
			break;
		default:
			printf("Error: Unknown Error\n");
			break;
	}
	line(30);
}

int
getInput(int lowerRange, int upperRange)
{
	int input;
	int valid = 0;

	do
	{
		//get valid integer input
		do
		{	
			if(scanf("%d", &input) != 1)
			{
				while(getchar() != '\n');
				handleError(INVALID_INPUT);
			}
			else
				valid = 1;
		} while(!valid);
		
		//check if its in range
		if(input < lowerRange || input > upperRange)
			handleError(INVALID_INPUT);
	} while (input < lowerRange || input > upperRange);
	
	//clear out the '\n'
	getchar();
	
	//return the valid integer input within the range
	return input;
}

void 
getPairs(String20 resultLang, String20 resultTransl)
{
	String20 tempLang, tempTransl;
	
	line(30);
	do
	{
		printf("Enter Lang-Transl Pair!\n");
		printf("Language: ");
		fgets(tempLang, sizeof(tempLang), stdin);
		printf("Translation: ");
		fgets(tempTransl, sizeof(tempTransl), stdin);
		
		tempLang[strlen(tempLang) - 1] = '\0';
		tempTransl[strlen(tempTransl) - 1] = '\0';
		
		if(strlen(tempLang) == 0 || strlen(tempTransl) == 0)
			handleError(MISSING_CHAR);
		
	} while((strlen(tempLang) == 0 || strlen(tempTransl) == 0));
	
	strcpy(resultLang, tempLang);
	strcpy(resultTransl, tempTransl);
	line(30);
}

void
getFilename(String30 filename)
{
	char ch;
	printf("Filename: ");
	scanf("%26s%c", filename, &ch);
	strcat(filename, ".txt\0");
}

void
getLanguageToTranslate(String20 in, String20 out)
{
	char ch;
	
	printf("TO: ");
	scanf("%20s%c", in, &ch);
	printf("FROM: ");
	scanf("%20s%c", out, &ch);
}

void
readFileIntoSentence(FILE * file, String150 txt)
{
	int i;
	
	i = 0;
	do
	{
		fscanf(file, "%c", &txt[i]);
		i++;
	} while(txt[i-1] != '.' && txt[i-1] != '!' /*&& txt[i-1] != '?'*/);
	txt[i-1] = '\0';
}

void
swapStr(String20 a, String20 b)
{
	String20 temp;
	
	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
}
	
void
sortWords(struct entryTag * entry, int nEntry, String20 language)
{
	struct entryTag temp;
	int i, j;
	int min;
	int languageCnt;
	
	//move up that language string to the very first index inside the entry
	for(i = 0; i < nEntry; i++)
	{	
		for(j = 0; j < entry[i].nPairs; j++)
		{
			if(strcmp(entry[i].language[j], language) == 0)
			{
				swapStr(entry[i].language[j], entry[i].language[0]);					
				swapStr(entry[i].translation[j], entry[i].translation[0]);
			}
		}
	}
	
	//move up all language strings 
	languageCnt = 0;
	for(i = 0; i < nEntry; i++)
	{
		if(strcmp(entry[i].language[0], language) == 0)
		{			
			temp = entry[languageCnt];
			entry[languageCnt] = entry[i];
			entry[i] = temp;
			
			languageCnt++;
		}
	}
	
	//sort the language strings
	for(i = 0; i < languageCnt - 1; i++)
	{
		min = i;
		for(j = i+1; j < languageCnt; j++)
		{
			if(strcmp(entry[min].translation[0], entry[j].translation[0]) > 0)
			{
					min = j;
			}
		}
		temp = entry[i];
		entry[i] = entry[min];
		entry[min] = temp;
	}
}


void 
sortLanguage(struct entryTag *entry)
{
	int i, j; 
	int n = entry->nPairs;
	int min;
	
	for(i = 0; i < n - 1; i++)
	{
		min = i;
		for(j = i + 1; j < n; j++)
		{
			if(strcmp(entry->language[min], entry->language[j]) >= 1)
			{
				min = j;
			}
		}
		swapStr(entry->language[i], entry->language[min]);
		swapStr(entry->translation[i], entry->translation[min]);
	}
}


void 
sortEntries(struct entryTag * entry, int nEntry, String20 language)
{
	int i, j;
	
	sortWords(entry, nEntry, language);
	for(i = 0; i < nEntry; i++)
	{
		for(j = 0; j < entry[i].nPairs; j++)
			sortLanguage(&entry[j]);
	}
}

void
shiftStructArray(struct entryTag * entry, int nEntry, int key)
{
	int i;
	
	for(i = key; i < nEntry - 1; i++)
	{
		entry[i] = entry[i+1];
	}
}

void
shiftStringArray(String20 str[], int n, int key)
{
	int i;
	
	for(i = key; i < n - 1; i++)
	{
		strcpy(str[i], str[i+1]);
	}
}

int
loadDictionary(struct entryTag * entry, int * nEntry, String30 filename)
{
	struct entryTag temp;
	
	FILE *fpLoad;
	
	char ch;
	int pairCount;
	int i;
	int flag = 0;
	
	fpLoad = fopen(filename, "r");
	
	if(fpLoad == NULL)
	{
		flag = 1;
	}

	pairCount = 0;
	while(fscanf(fpLoad, "%c", &ch) == 1 && !flag)
	{	
		if(ch != '\n')
		{
			temp.language[pairCount][0] = ch;
			i = 1;	
			do
			{
				fscanf(fpLoad, "%c", &temp.language[pairCount][i]);
				i++;
			} while(temp.language[pairCount][i-1] != ':');
			strcpy(temp.language[pairCount] + (i-1), "" );
			fscanf(fpLoad, "%c", &ch);
			
			i = 0;
			do
			{
				fscanf(fpLoad, "%c", &temp.translation[pairCount][i]);
				i++;
			} while(temp.translation[pairCount][i-1] != '\n');
			strcpy(temp.translation[pairCount] + (i-1), "" );			
			
			pairCount++;
		}
		else
		{	
			temp.nPairs = pairCount;
			pairCount = 0;

			entry[*nEntry] = temp;
			*nEntry += 1;
		}
	}
	
	fclose(fpLoad);
	
	if(flag)
		return 0;
	else return 1;
}

void
tokenizeSentence(String150 txt, String150 token[], int * nWords)
{
	int i,j;
	int flag;
	char ch;
	
	i = j = flag = *nWords = 0;
	do
	{
		ch = txt[j];
		j++;	
		if(ch != ',' && ch != '.' && ch != '!' && ch != '?')
		{
			if(ch == ' ')
			{
				token[*nWords][i] = '\0';
				*nWords += 1;
				i = 0;
			}
				else
			{		
				token[*nWords][i] = ch;
				i++;
			}		
		}
	} while(j != strlen(txt));
	token[*nWords][i] = '\0';
	*nWords += 1;
}

int
checkEarlyTermination()
{
	int input;
	int valid;
	
	if((valid = scanf("%d", &input)) != 1)
	{
		while(getchar() != '\n');
		handleError(INVALID_INPUT);
		printf("Returning to Manage Data Menu.\n");	
		printf("\n");
		printf("Press ENTER to continue... ");
	}
	getchar();
	
	if(valid != 1)
		return -1;
	else return input;
}