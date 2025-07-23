/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying 
the concepts learned.  I have constructed the functions and their respective algorithms and  corresponding 
code by myself. The program was run, tested, and debugged by my own efforts. I further certify that I have 
not copied in part or whole or otherwise plagiarized the work of other students and/or persons.  
  
Diane Benedict S. Panganiban, DLSU ID# 12411914
*********************************************************************************************************/ 

#include <stdio.h>
#include <string.h>

//compilation of prototypes, structs, typedefs and defs
#include "headers.h"
//easy access & editability
#include "graphics.h"
#include "helpers.h"
//main features that were implemented
#include "translate.h"
#include "manage_data.h"

int
main()
{
	int menuState = 1; //game states
	
	while(menuState)
	{	
		displayMenu();
		switch(getInput(1,3))
		{
			case 1: translateMenu();
				break;
			case 2: manageData();
				break;
			case 3: menuState = 0;
				 break;
		}
	}
}