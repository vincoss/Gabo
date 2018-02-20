/*
 * main.c
 *
 * Created: 08/02/2018
 * Author : Ferdinand Lukasak
 
	 Copy main.hex into Arduino board use this command
	 1. Open command prompt
	 2. cd {SolutionDir}\debug
	 3. avrdude -p atmega328p -c arduino -P COM3 -b 115200 -D -U flash:w:main.hex
 */ 

#include <string.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "Usart.h"
#include "Adc.h"
#include "GaboIo.h"
#include "GaboUsart.h"
#include "GaboCommand.h"


int main(int argc, char *argv[])
{
	UsartInitialize();
	GaboUsartInterruptInitialize();
	
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
	if (message == NULL || strlen(message) <= 0)
	{
		return 0; // Nothing
	}
	
	char buffer[strlen(message) + 1];
	itoa(message, buffer, 10);
	UsartWriteCharString(message);
	UsartWriteChar('\r\n');
}

#pragma endregion GaboCommand implementation
