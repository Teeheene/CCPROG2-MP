#include <stdio.h>
#include <string.h>

#include "headers.h"
#include "graphics.h"
#include "translate.h"
int
main()
{
	int input;
	int menuState = 1; //game states
	
	while(menuState)
	{
		
		displayMenu();
		scanf("%d", &input);
			
		switch(input)
		{
			case 1: displayTranslateMenu();
				scanf("%d", &input);
				break;
			case 2: manageData();
				scanf("%d", &input);
				break;
			case 3: menuState = 0;
				 break;
		}
	}
}
