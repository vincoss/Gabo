
#include <string.h>
#include <util/atomic.h>
#include "Usart.h"
#include "Adc.h"
#include "GaboIo.h"
#include "GaboUsart.h"
#include "GaboCommand.h"




//Severity	Code	Description	Project	File	Line
//Warning		ignoring #pragma region GaboCommand [-Wunknown-pragmas]	GaboAvr	C:\_Data\GitHub\Gabo\src\GaboAvr\Src\main.c	56
// cardno


int main(int argc, char *argv[])
{
	UsartInitialize();
	GaboUsartInterruptInitialize();

	while (1)
	{
		// Each loop attempt to read the input commands.
		GaboCommandRead();

		_delay_ms(2000);
	}

	return 0;
}


#pragma region GaboCommand implementation

void GaboCommandCopy(char * srcData, char * destCommand)
{
	if (strlen(srcData) <= 0)
	{
		return;
	}

	// The USART might interrupt this - don't let that happen!
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		// Copy the contents of data_in into command_in
		memcpy(destCommand, srcData, 8);

		//// Now clear data_in, the USART can reuse it now
		memset(srcData, 0, 8);
	}
}

void GaboCommandWriteLog(char * message)
{
	if (strlen(message) <= 0)
	{
		return 0;
	}
	
	char buffer[strlen(message) + 1];
	itoa(message, buffer, 10);
	UsartWriteCharString(message);
}

#pragma endregion GaboCommand implementation