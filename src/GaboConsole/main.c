/*
*	main.c
*
*	Created: 29/01/2018 10:09:16 PM
*	Author: Ferdinand Lukasak
*/


#include <stdio.h>
#include "UnitTests.h"


int main()
{
	UnitTestsRun();

	printf("\nDone...");
	getchar();
	getchar();

	return 0;
}

#pragma region GaboCommand.h implementation

/*
	NOTE: Contains platform specific implementation only. 
*/

void GaboCommandCopy(char * srcData, char * destCommand)
{
	if (strlen(srcData) <= 0)
	{
		return;
	}

	// Copy the contents of data_in into command_in
	memcpy(destCommand, srcData, 8);

	// Now clear data_in, the USART can reuse it now
	memset(srcData, 0, 8);
}

#pragma endregion