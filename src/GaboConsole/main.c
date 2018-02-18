/*
*	main.c
*
*	Created: 29/01/2018 10:09:16 PM
*	Author: Ferdinand Lukasak
*/


#include <stdio.h>
#include <stdlib.h>
#include "GaboIo.h"
#include "GaboCommand.h"
#include "UnitTests.h"

int main()
{
	UnitTestsRun();

	//while (1)
	//{
	//	// Each loop attempt to read the input commands.
	//	GaboCommandRead();
	//	_sleep(1000);
	//}

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
	memcpy(destCommand, srcData, RX_BUFFER_SIZE);

	// Now clear data_in, the USART can reuse it now
	memset(srcData, 0, RX_BUFFER_SIZE);
}

void GaboCommandWriteLog(char * message)
{
	if (strlen(message) <= 0)
	{
		return 0;
	}
	printf("%s", message);
	printf("\r\n");
}

#pragma endregion