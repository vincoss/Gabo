
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
	int a = GABOIO_SPI_DATA;
	
	if(a > 0)
	{
		
		
	}
	
	AdcInitialize();
	UsartInitialize();
	GaboUsartInterruptInitialize();
	GaboCommandRead();

	/*char* a = "asd";
	char b[9];
*/
	//GaboCommandCopy(a, b);
	//GaboCommandCopy(a, b);
/*
	int8_t result = GaboCommandParse("A=255", 0);
	UsartWriteChar(result);*/
	/*
	while (1)
	{
		UsartWriteChar(powerCommand);
		UsartWriteChar(powertrainCommand);

		GaboCommandRead();

		UsartWriteChar(powerCommand);
		UsartWriteChar(powertrainCommand);

		_delay_ms(2000);
	}*/

	return 0;
}

// cardno
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

#pragma endregion GaboCommand implementation